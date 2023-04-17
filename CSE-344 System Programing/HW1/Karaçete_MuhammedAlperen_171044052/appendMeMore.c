#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc,char* argv[]){

    char *path = argv[1];
    int length;
    char randomLetter;
    char controlArgument[15] = "./appendMeMore";
    int controlFlag = strcmp(argv[0],controlArgument);
    int controlFlag2 = 1;
    
    if (argc==4){

        controlFlag2 = strcmp(argv[3],"x"); //Control for If user enters 4th argument x.If it is entered, then APPEND flag omitted.
    }

    __mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; //File modes.


    if (argc==3 && !controlFlag){ //If there is 3 arguments and the first argument is ./appendMeMore than enter.
        int fd = open(path,O_WRONLY|O_CREAT|O_APPEND,mode);
        if (fd==-1){

            perror("open");
            return 1;
        }

        srand(time(NULL));
        length = atoi(argv[2]);

        for (int i=0;i<length;i++){
            randomLetter=(rand()%(90-65))+65; //Creates random alphabethical character.
            write (fd,&randomLetter,1);
        }
        close (fd);

    }
    
    else if (argc==4 && !controlFlag && !controlFlag2){
        int fd = open(path,O_WRONLY|O_CREAT,mode); //Omit APPEND flag.
        if (fd==-1){

            perror("open");
            return 1;
        }

        srand(time(NULL));
        length = atoi(argv[2]);

        for (int i=0;i<length;i++){
            lseek(fd, 0, SEEK_END);
            randomLetter=(rand()%(90-65))+65;
            write (fd,&randomLetter,1);
        }
        close (fd);

    }


    return 0;
}