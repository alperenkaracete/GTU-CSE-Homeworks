#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){

    off_t firstFileOffset;
    off_t secondFileOffset;
    int fd,fd2,control;
    __mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    char word[17] = "This is sentence",
    word2[23] = "This is other sentence",
    buffer[23];

    fd = open ("firstFile",O_RDWR|O_CREAT,mode);
    fd2 = open ("secondFile",O_RDWR|O_CREAT,mode);

    write (fd,&word,16);
    write (fd2,&word2,22);

    printf("*********Before dup:*********\n");

    lseek(fd,0,SEEK_SET);
    control=read (fd,buffer,16);
    buffer[16]='\0';
    if (control==-1){

        perror("read");
    }
    firstFileOffset = lseek(fd,0,SEEK_CUR);
    printf("File1 content: %s/ File1 offset: %ld\n",buffer,firstFileOffset);

    lseek(fd2,0,SEEK_SET);
    control=read (fd2,buffer,22);
    buffer[22]='\0';
    if (control==-1){

        perror("read");
    }
    secondFileOffset = lseek(fd2,0,SEEK_CUR);    
    printf("File2 content: %s/ File2 offset: %ld\n",buffer,secondFileOffset);    


    dup2(fd2,fd);
    printf("*********After dup:*********\n");    
    lseek(fd,7,SEEK_SET); 
    firstFileOffset = lseek(fd,0,SEEK_CUR);  
    secondFileOffset = lseek(fd2,0,SEEK_CUR);           
    control=read (fd,buffer,15);
    buffer[15]='\0';
    if (control==-1){

        perror("read");
    }
    printf("File1 content: %s/ File1 offset: %ld\n",buffer,firstFileOffset);

    control=read (fd2,buffer,15);
    buffer[15]='\0';
    if (control==-1){

        perror("read");
    }
    printf("File2 content: %s/ File2 offset: %ld\n",buffer,secondFileOffset);   

    return 0;
}