#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ftw.h>

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int rv = remove(fpath);

    if (rv)
        perror(fpath);

    return rv;
}

int rmrf(char *path)
{
    return nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}

#define BUFFER_SIZE 1024
#define PATHS 128

struct FileInfo {
    char name[PATHS];
    char parentName[PATHS];
    time_t modifyTime;
    off_t size;
    int isDirectory;
    int flag;
};

void scanDirectory(const char* folder, struct FileInfo** files, int* fileCount, off_t fileSizeLimit) {
    DIR* dir = opendir(folder);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char file_path[BUFFER_SIZE];
        snprintf(file_path, sizeof(file_path), "%s/%s", folder, entry->d_name);

        struct stat file_stat;
        if (stat(file_path, &file_stat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        struct FileInfo* fileInfo = realloc(*files, (*fileCount + 1) * sizeof(struct FileInfo));
        if (fileInfo == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }

        *files = fileInfo;

        struct FileInfo* currentFile = &(*files)[*fileCount];
        strncpy(currentFile->name, entry->d_name, sizeof(currentFile->name));
        currentFile->modifyTime = file_stat.st_mtime;
        currentFile->size = file_stat.st_size;
        currentFile->isDirectory = S_ISDIR(file_stat.st_mode);
        strcpy(currentFile->parentName,folder);
        currentFile->flag=0;

        (*fileCount)++;

        if (S_ISDIR(file_stat.st_mode)) {
            // Recursive call to scan subdirectories
            scanDirectory(file_path, files, fileCount, fileSizeLimit);
        } else {
            if (file_stat.st_size > fileSizeLimit) {
                // Skip files larger than the size threshold
                continue;
            }
        }
    }
    closedir(dir);
}

void writeFile(int sockfd, struct FileInfo fileInfo) {
    int n;
    FILE* fp;
    char* filename = fileInfo.name;
    char buffer[BUFFER_SIZE];
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("fopen");
        return;
    }

    // Receive the file size from the client
    long fileSize;
    if (recv(sockfd, &fileSize, sizeof(long), 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    // Receive and write the file data in chunks
    size_t totalBytesReceived = 0;
    while (totalBytesReceived < fileSize) {
        n = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (n <= 0) {
            break;
        }
        fwrite(buffer, sizeof(char), n, fp);
        totalBytesReceived += n;
        memset(buffer, 0, BUFFER_SIZE);
    }

    fclose(fp);
}



void sendFile(int sockfd, struct FileInfo fileInfo) {
    int n;
    int fd;
    char *filename = fileInfo.name;
    char buffer[BUFFER_SIZE];

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    while ((n = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (send(sockfd, buffer, n, 0) == -1) {
            perror("send");
            break;
        }
    }

    close(fd);
}

int main(int argc,char* argv[]) {

    if (argc==3){
        int serverSocket = 0, 
        port,
        countOfServerFiles=0,
        countOfClientFiles=0,
        countOfDifferentFiles=0,
        countOfSameFiles=0,
        folderCount=0;

        struct FileInfo* clientFiles = NULL;
        struct sockaddr_in serverAddress;

        char *directory;

        off_t fileSizeLimit = 1024*1024*1024; 

        directory = (char*) malloc (sizeof(argv[1]));
        strcpy(directory,argv[1]);
        port = atoi(argv[2]);


        if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }
        char path[BUFFER_SIZE];
        if (getcwd(path, sizeof(path)) == NULL) {
            perror("getcwd() error");
            return 1;
        } 

        int countBytesReceived = recv(serverSocket, &countOfServerFiles, sizeof(int), 0);
        if (countBytesReceived == -1) {
            perror("Error receiving countOfServerFiles");
            exit(1);
        }

        // Allocate memory for the array of struct FileInfo
        struct FileInfo* serverFiles = malloc(countOfServerFiles * sizeof(struct FileInfo));
        if (serverFiles == NULL) {
            perror("Memory allocation error");
            exit(1);
        }

        // Receive the array of struct FileInfo
        int filesBytesReceived = recv(serverSocket, serverFiles, countOfServerFiles * sizeof(struct FileInfo), 0);
        if (filesBytesReceived == -1) {
            perror("Error receiving ServerFiles");
            exit(1);
        }

        scanDirectory("clientfol", &clientFiles, &countOfClientFiles, fileSizeLimit);
        int *tempArrayServer = malloc (sizeof(int)*countOfServerFiles);
        int *tempArrayClient = malloc (sizeof(int)*countOfClientFiles);
        
        int lengthOfServerPath = strlen(directory) + 1;
        int lengthOfClientPath = strlen("clientfol") + 1;

        for (int i=0;i<countOfServerFiles;i++){
            //strcpy(serverFiles[i].parentName,&serverFiles[i].parentName[lengthOfServerPath]);
            //printf("Filename %s \n",serverFiles[i].name);
            tempArrayServer[i]=0;
        }

        for (int i=0;i<countOfClientFiles;i++){
            //strcpy(clientFiles[i].parentName,&clientFiles[i].parentName[lengthOfClientPath]);
            //printf("Filename %s Parent Name %s\n",clientFiles[i].parentName,clientFiles[i].name);
            tempArrayClient[i]=0;
        }
        for (int i=0;i<countOfServerFiles;i++){

            for (int j=0;j<countOfClientFiles;j++){

                if (!strcmp(serverFiles[i].name, clientFiles[j].name) && serverFiles[i].size == clientFiles[j].size && clientFiles[j].flag==0){
                    char tempServerPath[PATHS];
                    char tempClientPath[PATHS];
                    strcpy(tempServerPath,&serverFiles[i].parentName[lengthOfServerPath]);
                    strcpy(tempClientPath,&clientFiles[j].parentName[lengthOfClientPath]);

                    if (!strcmp(tempServerPath,tempClientPath)){
                    //printf("Parent %s File %s\n",tempClientPath,clientFiles[j].name);
                    //printf("Parent %s Parent %s\n",tempServerPath,serverFiles[i].name);
                        ++countOfSameFiles;
                        tempArrayServer[i]=1;
                        tempArrayClient[j]=1;
                        clientFiles[j].flag=1; 
                    }
 
                }
            }
            if (!tempArrayServer[i]){
                ++countOfDifferentFiles;
               
            }
        }
        struct FileInfo *filesWillCoppiedFromServer = malloc(countOfDifferentFiles * sizeof(struct FileInfo));

        char previousDir[PATHS];
        if (getcwd(previousDir, sizeof(previousDir)) == NULL) {
            perror("getcwd");
        return 1;
        }

        if (countOfSameFiles != countOfClientFiles){ //Delete different client files.

            for (int i=0;i<countOfClientFiles;i++){

                if(!tempArrayClient[i]){
                    //printf("%s",clientFiles[i].name);
                    chdir(clientFiles[i].parentName);
                    rmrf(clientFiles[i].name);
                    chdir(previousDir);
                }
            }
        }
        int temp=0;
        for (int i=0;i<countOfServerFiles;i++){

            if(!tempArrayServer[i]){
                filesWillCoppiedFromServer[temp] = serverFiles[i];
                //printf("%s",filesWillCoppiedFromServer[temp].name);
                temp++;
            }
        }

        if (send(serverSocket, &countOfDifferentFiles, sizeof(int), 0) == -1) {
            perror("Error sending data");
            exit(EXIT_FAILURE);
        }

        if (send(serverSocket, filesWillCoppiedFromServer, countOfDifferentFiles*sizeof(struct FileInfo), 0) == -1) {
            perror("Error sending data");
            exit(EXIT_FAILURE);
        }

        if (recv(serverSocket, &folderCount, sizeof(size_t), 0) == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        int parentNameLength;
        char succes[8] = "Success";
    getcwd(previousDir, sizeof(previousDir));    
    for (int i = 0; i < countOfDifferentFiles; i++) {
        
        if (filesWillCoppiedFromServer[i].isDirectory) {

            // Receive the parent name
            if (recv(serverSocket, &parentNameLength, sizeof(int), 0) == -1) {
                perror("recv");
                exit(EXIT_FAILURE);
            }

            // Allocate memory to store the parent name
            char* parentName = malloc(parentNameLength + 1);
            if (parentName == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            // Receive the parent name
            if (recv(serverSocket, parentName, sizeof(char) * parentNameLength, 0) == -1) {
                perror("recv");
                exit(EXIT_FAILURE);
            }

            struct stat st = {0};
            char tempPath[PATHS];
            char tempServerPath[PATHS];
            strcpy(tempPath, "clientfol");
            strcpy(tempServerPath, &filesWillCoppiedFromServer[i].parentName[lengthOfServerPath - 1]);
            strcat(tempPath, tempServerPath);
            chdir(tempPath);

            // Create the directory if it doesn't exist
            if (stat(filesWillCoppiedFromServer[i].name, &st) == -1) {
                if (mkdir(filesWillCoppiedFromServer[i].name, 0700) == -1) {
                    perror("mkdir");
                    exit(EXIT_FAILURE);
                }
            }

            chdir(previousDir);
            free(parentName);
            if (send(serverSocket, succes, sizeof(char)*strlen(succes), 0) == -1) {
                perror("recv");
                exit(EXIT_FAILURE);
            }
        }
    }
    for (int i = 0; i < countOfDifferentFiles; i++) {
        
        
        if (!filesWillCoppiedFromServer[i].isDirectory) {

            struct FileInfo tempFile;
            
            if (recv(serverSocket, &tempFile, sizeof(struct FileInfo), 0) == -1) {
                perror("recv");
                exit(EXIT_FAILURE);
            }

            char tempPath[PATHS];
            char tempServerPath[PATHS];
            strcpy(tempPath, "clientfol");
            strcpy(tempServerPath, &tempFile.parentName[lengthOfServerPath - 1]);
            strcat(tempPath, tempServerPath);

            chdir(tempPath);
            writeFile(serverSocket, tempFile);
            chdir(previousDir);

            // Send acknowledgment to the client
            if (send(serverSocket, &succes, sizeof(char)*strlen(succes), 0) == -1) {
                perror("send");
                exit(EXIT_FAILURE);
            }

        }
    }

        free(tempArrayServer);
        free(tempArrayClient);
        free(filesWillCoppiedFromServer);
        free(serverFiles);
        free(directory);
        
    }
    else if (argc==4){
            //I was planning to doing ti with connecting ip adress but could not do it
        //int sock = 0, valread,
        //port;
        //struct sockaddr_in serverAddress;
        //char *hello = "Hello from client",
        //buffer[BUFFER_SIZE] = {0},
        //*directory,
        //*ipAddress;
//
        //directory = (char*) malloc (sizeof(argv[1]));
        //strcpy(directory,argv[1]);
        //port = atoi(argv[2]);
        //ipAddress = (char*) malloc (sizeof(argv[3]));
        //strcpy(ipAddress,argv[3]);
    }
    return 0;
}
