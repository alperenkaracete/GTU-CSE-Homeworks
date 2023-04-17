#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#define BUFF_SIZE 200
#define _POSIX_C_SOURCE 200809L
#define MAX_CHILDREN 20

pid_t totalChildren[20];

void sigintHandler(int signal){

    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (totalChildren[i] != 0) {
            kill(totalChildren[i], signal);
        }
    }

    printf("\nReceived SIGINT signal , killing child processes!\n");
}

void sigtermHandler(int signal) {

    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (totalChildren[i] != 0) {
            kill(totalChildren[i], signal);
        }
    }    
    printf("\nReceived SIGTERM signal , killing child processes!\n");
}


int main(){

    __mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    
    // handle SIGTSTP and SIGINT signals
    if (signal(SIGINT, sigintHandler) == SIG_ERR) 
        printf("Error setting up signal handler\n");

    if (signal(SIGTERM, sigtermHandler)== SIG_ERR) 
        printf("Error setting up signal handler\n");
      

    pid_t pid = getppid();
    int result = kill(pid, SIGTERM);
        if (result != 0) {
        perror("kill");
        exit(EXIT_FAILURE);
    }

    char commandLineArg[BUFF_SIZE],
    *totalCommands[20],
    *buffer,
    buf[100];
    int i=0,
    j=0,
    k=0,
    childCount=0,
    childFlag;
    pid_t childPid[20];

    // Get the current timestamp
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20];
    strftime(timestamp, 20, "%H%M%S", tm_info);

    // Create a filename with the current timestamp
    char filename[100];
    sprintf(filename, "%s.log", timestamp);
    int fd = open(filename,O_WRONLY|O_CREAT|O_APPEND,mode); 
    if (fd==-1){
        perror("open");
        return 1;
    }
    

    while(1){
        printf("Please enter command.Command can contain | < >.:\n");
        fgets(commandLineArg,BUFF_SIZE,stdin);

        if (commandLineArg[0]==':' && commandLineArg[1]=='q' && commandLineArg[2]=='\n'){

            printf("Exited with :q\n");
            break;
        }

        buffer = strtok(commandLineArg,"|");  
        do {

            totalCommands[i]= buffer;
            buffer = strtok(NULL,"|");    
            i++;

        }while (buffer!=NULL);

        childCount = i;
        childFlag = i;
        int pfd[childCount-1][2];

        if (childCount!=1){
            for (k=0;k<childCount-1;k++){

                if(pipe(pfd[k])==-1){
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }
            }
        }

        while (childCount != j){

            switch (childPid[j] = fork()) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);

            case 0:

                localtime(&now);
                strftime(timestamp, 20, "%H:%M:%S", tm_info);
                snprintf(buf, sizeof(buf), "Child process id: %d,executing time:%s, executing command: %s\n", getpid(), timestamp,totalCommands[j]);
                if(write(fd, buf, strlen(buf))==-1){

                    perror("write");
                }
                if (j==0 && childCount!=1){ //Close read and write end for other pipes because we dont use any of them in first pipe.

                    for (k=j+1;k<childFlag-1;k++){
                        for (int m=0;m<2;m++){
                            if(close(pfd[k][m])==-1){
                                perror("close others");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }


                    if(close(pfd[j][0])==-1){ //Close read end for first argument because it will not used.
                        perror("close first input");
                        exit(EXIT_FAILURE);
                    }

                    if (pfd[j][1]!= STDOUT_FILENO){

                        if (dup2(pfd[j][1],STDOUT_FILENO)==-1){
                            printf("Error duplicate STDOUT_FILENO for %d child",j+1);
                            exit(EXIT_FAILURE);
                        }

                        if(close(pfd[j][1])==-1){ //Close read end for first argument because it will not used.
                            perror("close first input");
                            exit(EXIT_FAILURE);
                        }
                    }

                }
                else if (j!=0 && childCount!=1){    //Second to last pipe's still need read end.

                    for (k=0;k<j-1;k++){
                        for (int m=0;m<2;m++){
                            if(close(pfd[k][m])==-1){
                                perror("close littles");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }  
                    for (k=j+1;k<childFlag-1;k++){
                        for (int m=0;m<2;m++){
                            if(close(pfd[k][m])==-1){
                                perror("close biggers");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }  

                    if (pfd[j-1][0]!= STDIN_FILENO){

                        if (dup2(pfd[j-1][0],STDIN_FILENO)==-1){
                            printf("Error duplicate STDIN_FILENO for %d child",j+1);
                            exit(EXIT_FAILURE);
                        }

                        if(close(pfd[j-1][0])==-1){ //Close read end for first argument because it will not used.
                            perror("close first input");
                            exit(EXIT_FAILURE);
                        }
                    }
                    if(close(pfd[j-1][1])==-1){ //Close read end for first argument because it will not used.
                        perror("close first input");
                        exit(EXIT_FAILURE);
                    }

                    if (childCount!=j+1){
                        if (pfd[j][1]!= STDOUT_FILENO){

                            if (dup2(pfd[j][1],STDOUT_FILENO)==-1){
                                printf("Error duplicate STDOUT_FILENO for %d child",j+1);
                                exit(EXIT_FAILURE);
                            }

                            if(close(pfd[j][1])==-1){ //Close read end for first argument because it will not used.
                                perror("close first input");
                                exit(EXIT_FAILURE);
                            }
                        }
                        if(close(pfd[j][0])==-1){ //Close read end for first argument because it will not used.
                            perror("close first input");
                            exit(EXIT_FAILURE);
                        }     
                    }                  
                }                  

                execl("/bin/sh", "sh", "-c",totalCommands[j], (char *) NULL);
                perror("execl");
                _exit(127);

            default:
                if (childCount==j+1){

                    for (k=0;k<childFlag-1;k++){
                        for (int m=0;m<2;m++){
                            if(close(pfd[k][m])==-1){
                                perror("close parrent pipes");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
                break;
            }

            j++;
        }

        for (i=0;i<childFlag;i++){
            if(waitpid(childPid[i], NULL, 0)==-1){
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }

        i=0;
        j=0;

    }

    close(fd);
    return 0;
}