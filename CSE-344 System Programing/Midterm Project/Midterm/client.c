#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fifo.h"
#include <errno.h>

#define BUFF_SIZE 200

struct stat st = {0};

void displayCommandDetails(const char* commandName) {
    if (strcmp(commandName, "help list") == 0) {
        printf("list\nSends a request to display the list of files in Servers directory\n");
    } else if (strcmp(commandName, "help readF") == 0) {
        printf("readF <file> <line #>\nDisplays the #th line of the <file>. Returns with an error if <file> does not exist\n");
    } else if (strcmp(commandName, "help writeT") == 0) {
        printf("writeT <file> <line #> <string>\nWrites the content of \"string\" to the #th line of <file>. If the line # is not given, it writes to the end of the file. If the file does not exist, it creates and edits the file at the same time\n");
    } else if (strcmp(commandName, "help upload") == 0) {
        printf("upload <file>\nUploads the file from the current working directory of the client to the Servers directory. Beware of cases where there is no file in the client's current working directory or a file with the same name exists on the Servers side\n");
    } else if (strcmp(commandName, "help download") == 0) {
        printf("download <file>\nRequests to receive <file> from Servers directory to client side\n");
    } else if (strcmp(commandName, "help quit") == 0) {
        printf("quit\nSends a write request to Server side log file and quits\n");
    } else if (strcmp(commandName, "help killServer") == 0) {
        printf("killServer\nSends a kill request to the Server\n");
    } else {
        printf("Command not found\n");
    }
}

int main(int argc,char *argv[]){

    int serverFd,clientFd,connected;
    char *control[2] = {"biboServer","biboClient"}; //Control command if it's server or client.
    __pid_t clientId;
    char quitWord[]="quit";
    char clientNo;
    umask(0);
    if ( (mkfifo(CLIENT_FIFO, 0666)==-1) && errno!= EEXIST ){

        printf("Error mkfifo %s", CLIENT_FIFO);
    }

    if((serverFd= open(SERVER_FIFO, O_WRONLY))==-1){
        printf("Error server fifo %s\n", SERVER_FIFO);
        exit(EXIT_FAILURE);
    }
    clientFd = open(CLIENT_FIFO, O_RDONLY);
    if (clientFd == -1) {            
        printf("Error open %s\n", CLIENT_FIFO);
    }

    if (argc==4){

        if (!strcmp(argv[1],control[1])){  //If it is client

            clientId = getppid();

            if (!(strcmp(argv[2],"connect"))){
                char tempWord[20] = "connect";

                if(write(serverFd,tempWord,sizeof(tempWord))==-1)
                    perror("Write:\n"); 

                if(read(clientFd,tempWord,sizeof(tempWord))==-1)
                    perror("Read:\n");    
                if (!strcmp(tempWord,argv[3])){
                    sprintf(tempWord, "%d", clientId);
                    if(write(serverFd,tempWord,sizeof(tempWord))==-1)
                        perror("Write:\n"); 
                    connected = 1;
                    if(read(clientFd,&clientNo,sizeof(clientNo))==-1)
                        perror("Read:\n");
                        
                }
                else if (!strcmp(tempWord,"full")){

                    while (!strcmp(tempWord,"empty")){

                        if(read(clientFd,tempWord,sizeof(tempWord))==-1)
                            perror("Read:\n");

                    }
                    strcpy(tempWord,"write");
                    if(write(serverFd,tempWord,sizeof(tempWord))==-1)
                        perror("Write:\n");    
                    connected=1;

                }
                else {
                    strcpy(tempWord,"Wrong");

                    if(write(serverFd,tempWord,sizeof(tempWord))==-1)
                        perror("Write:\n"); 
                    if(read(clientFd,tempWord,sizeof(tempWord))==-1)
                        perror("Read:\n");
                    if (!strcmp(tempWord,"break")){

                        printf("Wrong PID disconnecting!\n");
                        connected=0;
                    }    
                }

            }
            
            char str[BUFF_SIZE];
            while(connected){
                printf("Enter Comment: \n");
                if (strcmp(str,quitWord)!=0){
                    fgets(str,BUFF_SIZE,stdin);
                    str[strcspn(str, "\n")] = '\0'; //Delete enter char.
                }
                if(strcmp(str,quitWord)==0){

                    if(write(serverFd,quitWord,sizeof(quitWord))==-1)
                        perror("Write:\n"); 
                    sprintf(quitWord, "%d", clientId);
                    if(write(serverFd,quitWord,sizeof(quitWord))==-1)
                        perror("Write:\n"); 
                    if(write(serverFd,&clientNo,sizeof(clientNo))==-1)
                        perror("Write:\n"); 
                    printf("Sending write request to server log file\n waiting for logfile ...\n");
                    break;
                }
                if (!strcmp(str,"help")){

                    printf("Available comments are :\n\nhelp, list, readF, writeT, upload, download, quit, killServer\n");
                }
                else if(strstr(str,"help")){
                    
                    displayCommandDetails(str);
                }

                if(write(serverFd, str, sizeof(str))==-1)
                    perror("Write:\n"); 


                if(read(clientFd,str,sizeof(str))==-1)
                    perror("Read:\n"); 


            }
            close(serverFd);
            close(clientFd);

        }
    }

    else {

        printf("Wrong arguments!You need at lest 3.\n");
        
    }


    return 0;
}