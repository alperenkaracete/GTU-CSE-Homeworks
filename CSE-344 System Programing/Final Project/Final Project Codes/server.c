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
#include <signal.h>

int quit = 1;  // Flag to indicate if the program is quit

void sigIntHandler(int signal) {
    if (signal == SIGINT) {
        quit = 0;
    }
}

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
        currentFile->modifyTime = file_stat.st_atime;
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
                // Skip files larger than the size 
                continue;
            }
        }
    }
    closedir(dir);
}

void writeFile(int sockfd, struct FileInfo fileInfo) {
    int n;
    int file_fd;
    char *filename = fileInfo.name;
    char buffer[BUFFER_SIZE];

    file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file_fd == -1) {
        perror("open");
        return;
    }

    while (1) {
        n = read(sockfd, buffer, BUFFER_SIZE);
        if (n <= 0) {
            break;
        }
        write(file_fd, buffer, n);
        bzero(buffer, BUFFER_SIZE);
    }

    close(file_fd);
}

void sendFile(int sockfd, struct FileInfo fileInfo) {
    char data[BUFFER_SIZE];
    char* fileName = fileInfo.name;
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", fileName);
        exit(1);
    }

    fseek(fp, 0, SEEK_END); // Move the file pointer to the end of the file
    long fileSize = ftell(fp); // Get the file size
    fseek(fp, 0, SEEK_SET); // Move the file pointer back to the beginning of the file

    // Send the file size to the client
    if (send(sockfd, &fileSize, sizeof(long), 0) == -1) {
        perror("send");
        exit(1);
    }

    // Send the file data in chunks
    size_t bytesRead;
    while ((bytesRead = fread(data, sizeof(char), BUFFER_SIZE, fp)) > 0) {
        if (send(sockfd, data, bytesRead, 0) == -1) {
            perror("send");
            exit(1);
        }
    }

    fclose(fp);
}

void printChanges(struct FileInfo* previousFiles, int countOfPreviousFiles, struct FileInfo* currentFiles, int countOfCurrentFiles) {
    // Compare previous and current file states to detect changes

    // Check for newly added files and directories
    for (int i = 0; i < countOfCurrentFiles; i++) {
        struct FileInfo* currentFile = &currentFiles[i];
        int found = 0;

        for (int j = 0; j < countOfPreviousFiles; j++) {
            struct FileInfo* previousFile = &previousFiles[j];

            if (strcmp(previousFile->name, currentFile->name) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (currentFile->isDirectory) {
                printf("New directory added: %s\n", currentFile->name);
            } else {
                printf("New file added: %s\n", currentFile->name);
            }
        }
    }

    // Check for deleted files and directories
    for (int i = 0; i < countOfPreviousFiles; i++) {
        struct FileInfo* previousFile = &previousFiles[i];
        int found = 0;

        for (int j = 0; j < countOfCurrentFiles; j++) {
            struct FileInfo* currentFile = &currentFiles[j];

            if (strcmp(previousFile->name, currentFile->name) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (previousFile->isDirectory) {
                printf("Directory deleted: %s\n", previousFile->name);
            } else {
                printf("File deleted: %s\n", previousFile->name);
            }
        }
    }

    // Check for modified files
    for (int i = 0; i < countOfPreviousFiles; i++) {
        struct FileInfo* previousFile = &previousFiles[i];

        for (int j = 0; j < countOfCurrentFiles; j++) {
            struct FileInfo* currentFile = &currentFiles[j];

            if (strcmp(previousFile->name, currentFile->name) == 0 && previousFile->modifyTime != currentFile->modifyTime && strcmp(previousFile->parentName, currentFile->parentName) == 0) {
                if (currentFile->isDirectory) {
                    printf("Directory modified: %s\n", previousFile->name);
                } else {
                    printf("File modified: %s\n", previousFile->name);
                }
                break;
            }
        }
    }
}


int main(int argc,char *argv[]) {

    if (signal(SIGINT, sigIntHandler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    if (argc==4){

        struct sockaddr_in address;
        int opt = 1,
        addressLen = sizeof(address),
        port,
        serverFd,
        clientSocket; 
        //threadPoolSize;
        char *directory;
        //pthread_t *threads;
        //char *serverIp = "127.0.0.1";
        off_t fileSizeLimit = 1024*1024*1024;  // Set the size threshold in bytes

        struct FileInfo* previousFiles = NULL;
        struct FileInfo* filesForSendingClient = NULL;
        int countOfPreviousFiles = 0;


        directory = (char*) malloc (sizeof(argv[1]));
        strcpy(directory,argv[1]);
        port = atoi(argv[3]);

        //threadPoolSize = atoi(argv[2]);
        //threads = (pthread_t*) malloc (sizeof(pthread_t)*threadPoolSize);

        struct stat st = {0};

        if (stat(directory, &st) == -1) {
            mkdir(directory, 0700);
        }
        scanDirectory(directory, &previousFiles, &countOfPreviousFiles, fileSizeLimit);

        // Creating socket file descriptor
        if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        // Forcefully attaching socket to the port 8080
        if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(serverFd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        if ((clientSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t *)&addressLen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Send the countOfPreviousFiles first
        int countBytesSent = send(clientSocket, &countOfPreviousFiles, sizeof(int), 0);
        if (countBytesSent == -1) {
            perror("Error sending countOfPreviousFiles");
            exit(1);
        }

        // Send the array of struct FileInfo
        int filesBytesSent = send(clientSocket, previousFiles, countOfPreviousFiles * sizeof(struct FileInfo), 0);
        if (filesBytesSent == -1) {
            perror("Error sending previousFiles");
            exit(1);
        }

        int sizeOfSendingList=0;
        int filesBytesReceived = recv(clientSocket, &sizeOfSendingList, sizeof(int), 0);
        if (filesBytesReceived == -1) {
            perror("Error receiving ServerFiles");
            exit(1);
        }

        filesForSendingClient = malloc(sizeOfSendingList * sizeof(struct FileInfo));

        filesBytesReceived = recv(clientSocket, filesForSendingClient, sizeOfSendingList * sizeof(struct FileInfo), 0);
        if (filesBytesReceived == -1) {
            perror("Error receiving ServerFiles");
            exit(1);
        }
        int folderCount=0;
        for (int i=0;i<sizeOfSendingList;i++){

            if (filesForSendingClient[i].isDirectory)
                ++folderCount;
        }

        if (send(clientSocket, &folderCount, sizeof(int), 0) == -1) {
            perror("send");
            exit(EXIT_FAILURE);
        }
        int *parentNameLength = malloc(sizeof(int)*folderCount);
        for (int i=0;i<sizeOfSendingList;i++){

            if (filesForSendingClient[i].isDirectory){
                    
                parentNameLength[i] = strlen(filesForSendingClient[i].parentName)+1;
                
                if (send(clientSocket, &parentNameLength[i], sizeof(int), 0) == -1) {
                    perror("send");
                    exit(EXIT_FAILURE);
                }
                // Send the parent name
                if (send(clientSocket, filesForSendingClient[i].parentName, sizeof(char)*parentNameLength[i], 0) == -1) {
                    perror("send");
                    exit(EXIT_FAILURE);
                }
            }
        }
        char succes[8] = "Success";
        for (int i=0;i<sizeOfSendingList;i++){
            if (filesForSendingClient[i].isDirectory){
                    
                parentNameLength[i] = strlen(filesForSendingClient[i].parentName)+1;
                
                if (send(clientSocket, &parentNameLength[i], sizeof(int), 0) == -1) {
                    perror("send");
                    exit(EXIT_FAILURE);
                }
                // Send the parent name
                if (send(clientSocket, filesForSendingClient[i].parentName, sizeof(char)*parentNameLength[i], 0) == -1) {
                    perror("send");
                    exit(EXIT_FAILURE);
                }
                if (recv(clientSocket, succes, sizeof(char)*strlen(succes), 0) == -1) {
                    perror("recv");
                    exit(EXIT_FAILURE);
                }
            }
        }
        
        for (int i=0;i<sizeOfSendingList;i++){
            
            if (!filesForSendingClient[i].isDirectory){ 
                if (send(clientSocket, &filesForSendingClient[i], sizeof(struct FileInfo), 0) == -1) {
                    perror("send");
                    exit(EXIT_FAILURE);
                }
                sendFile(clientSocket, filesForSendingClient[i]);
                if (recv(clientSocket, &succes, sizeof(char)*strlen(succes), 0) == -1) {
                    perror("recv");
                    exit(EXIT_FAILURE);
                }
                
            }
        }

    scanDirectory(directory, &previousFiles, &countOfPreviousFiles, fileSizeLimit);

    while (quit) {
        sleep(1); 

        struct FileInfo* currentFiles = NULL;
        int countOfCurrentFiles = 0;

        scanDirectory(directory, &currentFiles, &countOfCurrentFiles, fileSizeLimit);

        printChanges(previousFiles, countOfPreviousFiles, currentFiles, countOfCurrentFiles);

        // Free memory for previous files
        free(previousFiles);

        // Update the previous state
        previousFiles = currentFiles;
        countOfPreviousFiles = countOfCurrentFiles;
    }
    free(previousFiles);
        
    }

    else {

        printf("Wrong arguments\n");
    }

    return 0;
}