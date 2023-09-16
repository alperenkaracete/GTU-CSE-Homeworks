#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/stat.h>

#define stringSize 512

// Structure to hold file information
typedef struct {
    int sourceFd; // Source file file descriptor
    int destFd; // Destination file file descriptor
    char filename[stringSize]; // File name
    int type; // 0 for Regular Files 1 for FIFO's
    char destinationPath[stringSize]; // hide info about where to copy FIFO and for calculating size of file
    int fileSize;
} FileInformation;

// Global variables
pthread_mutex_t bufferMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bufferEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t bufferFull = PTHREAD_COND_INITIALIZER;
pthread_mutex_t outputLock = PTHREAD_MUTEX_INITIALIZER;
FileInformation* buffer;
int *globalBufferSize,
    doneFlag = 0,
    folderCount=0,
    fifoCount=0,   
    bufferCount = 0, 
    regularFileCount=0;
off_t totalByteSize = 0;

void copyDirs(const char* sourceDir, const char* destinationDir) {
    DIR* dir;
    struct dirent* entry;

    dir = opendir(sourceDir);
    if (dir == NULL) {
        printf("Error opening source directory\n");
        return;
    }

    // Create destination directory if it doesn't exist
    struct stat st = {0};
    if (stat(destinationDir, &st) == -1) {
        
        if(mkdir(destinationDir, 0777)==-1){

            printf("Error creating destination directory.\n");
        }
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char sourcePath[stringSize];
        char destinationPath[stringSize];

        snprintf(sourcePath, sizeof(sourcePath), "%s/%s", sourceDir, entry->d_name);
        snprintf(destinationPath, sizeof(destinationPath), "%s/%s", destinationDir, entry->d_name);

        struct stat statbuf;
        if (stat(sourcePath, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                printf("Directory %s has coppied succesfully!\n",entry->d_name);
                copyDirs(sourcePath, destinationPath);
                folderCount++;
            } 
            else if (S_ISREG(statbuf.st_mode)) {
                int sourceFd = open(sourcePath, O_RDONLY);
                if (sourceFd == -1) {
                    printf("Error opening source file %s\n", sourcePath);
                    continue;
                }

                int destFd = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (destFd == -1) {
                    printf("Error opening destination file %s\n", destinationPath);
                    close(sourceFd);
                    continue;
                }

                FileInformation fileInfo;
                fileInfo.sourceFd = sourceFd;
                fileInfo.destFd = destFd;
                fileInfo.type = 0;           
                strncpy(fileInfo.filename, entry->d_name, stringSize);

                pthread_mutex_lock(&bufferMutex);
                while (bufferCount == *globalBufferSize) {
                    pthread_cond_wait(&bufferFull, &bufferMutex);
                }

                buffer[bufferCount] = fileInfo;
                bufferCount++;
                pthread_cond_signal(&bufferEmpty);
                pthread_mutex_unlock(&bufferMutex);
            }
            else if (S_ISFIFO(statbuf.st_mode)){

                FileInformation fileInfo;
                fileInfo.sourceFd = -1;
                fileInfo.destFd = -1;
                fileInfo.type = 1;
                strncpy(fileInfo.filename, entry->d_name, stringSize);
                snprintf(fileInfo.destinationPath, sizeof(fileInfo.destinationPath), "%s/%s", destinationDir, entry->d_name);

                pthread_mutex_lock(&bufferMutex);
                while (bufferCount == *globalBufferSize) {
                    pthread_cond_wait(&bufferFull, &bufferMutex);
                }

                buffer[bufferCount] = fileInfo;
                bufferCount++;
                pthread_cond_signal(&bufferEmpty);
                pthread_mutex_unlock(&bufferMutex);
            } 
        }
    }

    closedir(dir);
}

// Producer thread function
void* producerThreadFunc(void* directories) {
    char* sourceDir = ((char**)directories)[0];
    char* destinationDir = ((char**)directories)[1];
    DIR* dir;
    struct dirent* entry;

    dir = opendir(sourceDir);
    if (dir == NULL) {
        printf("Error opening source directory\n");
        pthread_exit(NULL);
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char sourcePath[stringSize],
        destinationPath[stringSize];
        snprintf(sourcePath, sizeof(sourcePath), "%s/%s", sourceDir, entry->d_name);
        snprintf(destinationPath, sizeof(destinationPath), "%s/%s", destinationDir, entry->d_name);
        struct stat statbuf;
        if (stat(sourcePath, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                mkdir(destinationPath, 0777);
                printf("Directory %s has coppied succesfully!\n",entry->d_name);
                folderCount++;
                copyDirs(sourcePath, destinationPath);
            } 
            else if (S_ISREG(statbuf.st_mode)) {
                int sourceFd = open(sourcePath, O_RDONLY);
                if (sourceFd == -1) {
                    printf("Error opening source file %s\n", sourcePath);
                    continue;
                }
                int destFd = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (destFd == -1) {
                    printf("Error opening destination file %s\n", destinationPath);
                    close(sourceFd);
                    continue;
                }
                FileInformation fileInfo;
                fileInfo.sourceFd = sourceFd;
                fileInfo.destFd = destFd;
                fileInfo.type = 0;
                strncpy(fileInfo.filename, entry->d_name, stringSize);
                pthread_mutex_lock(&bufferMutex);
                while (bufferCount == *globalBufferSize) {
                    pthread_cond_wait(&bufferFull, &bufferMutex);
                }
                buffer[bufferCount] = fileInfo;
                bufferCount++;
                pthread_cond_signal(&bufferEmpty);
                pthread_mutex_unlock(&bufferMutex);
            }
            else if (S_ISFIFO(statbuf.st_mode)){

                FileInformation fileInfo;
                fileInfo.sourceFd = -1;
                fileInfo.destFd = -1;
                fileInfo.type = 1;
                strncpy(fileInfo.filename, entry->d_name, stringSize);
                snprintf(fileInfo.destinationPath, sizeof(fileInfo.destinationPath), "%s/%s", destinationDir, entry->d_name);

                pthread_mutex_lock(&bufferMutex);
                while (bufferCount == *globalBufferSize) {
                    pthread_cond_wait(&bufferFull, &bufferMutex);
                }

                buffer[bufferCount] = fileInfo;
                bufferCount++;
                pthread_cond_signal(&bufferEmpty);
                pthread_mutex_unlock(&bufferMutex);
            }
        }
    }

    closedir(dir);

    pthread_mutex_lock(&bufferMutex);
    doneFlag = 1;
    pthread_cond_broadcast(&bufferEmpty);
    pthread_mutex_unlock(&bufferMutex);

    pthread_exit(NULL);
}

// Consumer thread function
void* consumerThreadFunc(void* arg) { //Regular files and FIFO's coppied here.
    while (1) {
        pthread_mutex_lock(&bufferMutex);
        while (bufferCount == 0) {
            if (doneFlag) {
                pthread_mutex_unlock(&bufferMutex);
                pthread_exit(NULL);
            }
            pthread_cond_wait(&bufferEmpty, &bufferMutex);
        }
        FileInformation fileInfo = buffer[bufferCount - 1];
        bufferCount--;
        pthread_cond_signal(&bufferFull);
        pthread_mutex_unlock(&bufferMutex);

        // Copy file contents
        if (fileInfo.type==0){
            char temp[1024];
            ssize_t bytesRead, bytesWritten;

            while ((bytesRead = read(fileInfo.sourceFd, temp, sizeof(temp))) > 0) {
                bytesWritten = write(fileInfo.destFd, temp, bytesRead);
                if (bytesWritten != bytesRead) {
                    pthread_mutex_lock(&outputLock);
                    printf("Error copying file %s\n", fileInfo.filename);
                    pthread_mutex_unlock(&outputLock);
                    break;
                }
            }

        struct stat statbuf;
        if (fstat(fileInfo.destFd, &statbuf) == 0) {
            fileInfo.fileSize = statbuf.st_size;
        } 
        else {
            pthread_mutex_lock(&outputLock);
            printf("Error retrieving file size for %s\n", fileInfo.filename);
            pthread_mutex_unlock(&outputLock);
        }

        close(fileInfo.sourceFd);
        close(fileInfo.destFd);
        
        pthread_mutex_lock(&outputLock);
        printf("File %s copied successfully\n", fileInfo.filename);
        regularFileCount++;
        totalByteSize += fileInfo.fileSize;
        pthread_mutex_unlock(&outputLock);
        }
        else if (fileInfo.type==1){
            fifoCount++;
            if(mkfifo(fileInfo.destinationPath, 0666)==0){

                pthread_mutex_lock(&outputLock);
                printf("Fifo %s copied successfully\n", fileInfo.filename);
                pthread_mutex_unlock(&outputLock);

            }
            else {
                pthread_mutex_lock(&outputLock);
                printf("Error creating FIFO.May be Fifo exists!\n");
                pthread_mutex_unlock(&outputLock);
            }

        }  
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Wrong arguments!\n");
        return 1;
    }
    else if (strcmp(argv[0],"./pCp")){
        printf("Program's name is pCp\n");
        return 1;
    }
    int bufferSize = atoi(argv[1]);
    buffer = (FileInformation*)malloc(bufferSize * sizeof(FileInformation));
    globalBufferSize = &bufferSize;
    int numberOfConsumers = atoi(argv[2]);

    char* sourceDir = argv[3];
    char* destinationDir = argv[4];

    pthread_t producer;
    pthread_t* consumers = malloc(numberOfConsumers * sizeof(pthread_t));

    char* dirs[2];
    dirs[0] = sourceDir;
    dirs[1] = destinationDir;

    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    pthread_create(&producer, NULL, producerThreadFunc, dirs);

    for (int i = 0; i < numberOfConsumers; i++) {
        pthread_create(&consumers[i], NULL, consumerThreadFunc, NULL);
    }

    pthread_join(producer, NULL);

    for (int i = 0; i < numberOfConsumers; i++) {
        pthread_join(consumers[i], NULL);
    }
    gettimeofday(&endTime, NULL);
    printf("Total second pass for copy operation: %ld microseconds.\n", endTime.tv_usec - startTime.tv_usec);

    free(buffer);
    free(consumers);

    printf("Total Counts:\nFolder Count: %d Regular File Count:%d , Fifo Count: %d\n",folderCount,regularFileCount,fifoCount);
    printf("Total coppied bytes: %ld\n",totalByteSize);

    return 0;
}