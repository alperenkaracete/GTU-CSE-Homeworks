#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int dup(int oldFd){

    return fcntl(oldFd,F_DUPFD,0);
}

int dup2(int oldFd,int newFd){

    if (oldFd==newFd){
        if(fcntl(oldFd,F_GETFL)==-1){
            
            errno = EBADF;
            printf("Error description is : %s\n",strerror(errno));
            return -1;
        }
    }

    close(newFd);
    fcntl(oldFd, F_DUPFD, newFd);
    return newFd;
}

int main(){

    __mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

    char word1[5]="elma",
    word2[5]="ayva",
    buffer[5];

    int fd = open("f3",O_CREAT|O_RDWR,mode);
    int fd2 = open("f4",O_CREAT|O_RDWR,mode);

    if (fd == -1 || fd2 == -1){

        perror("File open error:");
    }

    write (fd,&word1,4);
    write (fd2,&word2,4);

    lseek (fd,0,SEEK_SET);
    lseek (fd2,0,SEEK_SET);

    read (fd,buffer,4);
    buffer[4]='\0';

    printf ("***********Before dup***********\n");
    printf("First file content: %s\n",buffer);

    read (fd2,buffer,4);
    buffer[4]='\0';

    printf("Second file content: %s\n",buffer);    
    printf ("\n***********After dup***********\n");

    fd = dup(fd2);
    lseek (fd2,0,SEEK_SET);

    read (fd,buffer,4);
    buffer[4]='\0';

    printf("First file content: %s\n",buffer);

    read (fd2,buffer,4);
    buffer[4]='\0';

    printf("Second file content: %s\n\n\n",buffer);  
   

    close(fd);
    close(fd2);

    fd = open("f3",O_CREAT|O_RDWR,mode);
    fd2 = open("f4",O_CREAT|O_RDWR,mode);

    read (fd,buffer,4);
    buffer[4]='\0';

    printf ("***********Before dup2***********\n");
    printf("First file content: %s\n",buffer);

    read (fd2,buffer,4);
    buffer[4]='\0';

    printf("Second file content: %s\n",buffer);    
    printf ("\n***********After dup2***********\n");

    dup2(fd2,fd);
    lseek (fd2,0,SEEK_SET);

    read (fd,buffer,4);
    buffer[4]='\0';

    printf("First file content: %s\n",buffer);

    read (fd2,buffer,4);
    buffer[4]='\0';

    printf("Second file content: %s\n",buffer);  
   
    close(fd);
    close(fd2);

    return 0;
}
