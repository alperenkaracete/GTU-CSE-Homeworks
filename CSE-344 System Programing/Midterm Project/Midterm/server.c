#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "fifo.h"
#include <errno.h>
#include <signal.h>

struct stat st = {0};

typedef struct queue {
    int* items;
    int max_size;
    int head;
    int tail;
    int size;
} queue;

queue *initQueue(int maxSize) {
    queue *q = malloc(sizeof(queue));
    q->items = malloc(maxSize * sizeof(int));
    q->max_size = maxSize;
    q->head = 0;
    q->tail = -1;
    q->size = 0;
    return q;
}

void enqueue(queue *q, int item) {
    if (q->size < q->max_size) {
        q->tail = (q->tail + 1) % q->max_size;
        q->items[q->tail] = item;
        q->size++;
    } else {
        printf("Queue is full\n");
    }
}

int dequeue(queue *q) {
    if (q->size > 0) {
        int item = q->items[q->head];
        q->head = (q->head + 1) % q->max_size;
        q->size--;
        return item;
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}

void freequeue(queue *q) {
    while (q->size!=0) {
        dequeue(q);
    }
    free(q->items);
    free(q);
}


#define BUFF_SIZE 200

int main(int argc,char *argv[]){

    umask(0);
    if ( (mkfifo(SERVER_FIFO, 0666)==-1) && errno!= EEXIST ){

        printf("Error mkfifo %s", SERVER_FIFO);
    }

    queue *myQueue;
    myQueue=initQueue(BUFF_SIZE);
    int serverFd,clientFd,clientCount=0,connected=0,childFlag=0,succes=0,totalChild=0;
    char buf[BUFF_SIZE],quitClientId;

    char *control[2] = {"biboServer","biboClient"}; //Control command if it's server or client.
    __pid_t parentId,clientPID;

    if (argc==4){

        if (!strcmp(argv[1],control[0])){  //If it is server
            

            parentId = getppid();
            printf("Server Started PID %d\n",parentId); //Get parent PID and 
            if (stat(argv[2],&st) == -1) { //Controls if directory exist. If does not exist, creates that directory.
                mkdir(argv[2], 0700);
            }
            if((serverFd= open(SERVER_FIFO, O_RDONLY))==-1){
                printf("Error mkfifo %s", SERVER_FIFO);
                exit(EXIT_FAILURE);
            }
            clientFd = open(CLIENT_FIFO, O_WRONLY);
            if (clientFd == -1) {            
                printf("Error open %s\n", CLIENT_FIFO);
            }      

            for (;;){
                if (read(serverFd, buf, BUFF_SIZE) == -1){
                    fprintf(stderr, "Error reading request; discarding\n"); 
                    continue;
                }
            
                if (strcmp("killServer",buf)==0)
                {
                    printf("Server OFF.\n");
                    char temp[20]; 
                    strcpy(temp,"quit");
                    if(write(clientFd,temp,sizeof(temp))==-1)
                        perror("Write:\n");  
                    break;
                }

                else if (strcmp("",buf)!=0)
                {

                    if ((!strcmp(buf,"connect")) && !connected){ //Connected değiş forkla
                        
                        char temp[20]; 
                        char tempPid[20];
                        sprintf(tempPid, "%d", parentId);
                        if(write(clientFd,tempPid,sizeof(tempPid))==-1)
                            perror("Write:\n");  
                        if(read(serverFd,temp,sizeof(temp))==-1)
                            perror("Read:\n");   
                        if (!strcmp(temp,"Wrong")){
                            strcpy(temp,"break");
                            printf("%s",temp);
                            if(write(clientFd,temp,sizeof(temp))==-1)
                                perror("Write:\n");  
                        }    
                        else if (clientCount < atoi(argv[3])){

                            succes=1;

                        }
                        else {
                            succes=1;
                            enqueue(myQueue, atoi(temp));
                            //Qunun dolu olduğunu gönder.

                        }
                        if (succes){
                            switch (clientPID = fork()) {
                                case -1:
                                    perror("fork\n");
                                    exit(EXIT_FAILURE);
                                    break;

                                case 0:
                                    connected = 1;
                                    ++clientCount;
                                    quitClientId = clientCount + '0';
                                    totalChild++;
                                    if(write(clientFd,&quitClientId,sizeof(quitClientId))==-1)
                                        perror("Write:\n"); 
                                    printf("Client PID %s connected as \"client%d\"\n",temp,clientCount);
                                    break;

                                default:    


                            }
                        }
                    
                    }

                    else if (!strcmp(buf,"quit")){
                        if (myQueue->size==0){
                            if(read(serverFd,&quitClientId,sizeof(quitClientId))==-1)
                                perror("Read:\n");    
                            printf("client%c disconnected\n",quitClientId);
                            if (parentId!=getpid())
                                --clientCount;
                        }
                        else {
                            
                            char temp[20] = "empty"; 
                            if(write(clientFd,temp,sizeof(temp))==-1)
                                perror("Write:\n");  
                            if(read(serverFd,temp,sizeof(temp))==-1)
                                perror("Read:\n");
                            if (!strcmp(buf,"write")){
                                int tempPid = dequeue(myQueue);
                                printf("Client PID %d connected as \"client%d\"\n",tempPid,clientCount);

                            }

                        }
                        
                    }
                    //printf("Sending back...\n");
                    if(write(clientFd,buf,BUFF_SIZE)==-1)
                        perror("Write:\n"); 
                }

                /* clean buf from any data */
                memset(buf, 0, sizeof(buf));

            }

            if (close (serverFd)==-1){
                perror("close");
            }

            if (close (clientFd)==-1){
                perror("close");
            }

        }

        for (int i=0;i<totalChild;i++){

            if (waitpid(clientPID, NULL, 0) == -1) {
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }

    }

    else {

        printf("Wrong arguments!You need at lest 3.\n");

    }

    freequeue(myQueue);
    return 0;
}