//
//  main.c
//  lab4
//
//  Created by jy03189211 on 13-2-5.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void print_flags(int fd);

int main(int argc, const char * argv[])
{
    int fd,file_flags;
    char buff;
    //fd=open("/dev/tty",O_RDWR);
    fd=open("/dev/tty",O_RDONLY);
    file_flags = fcntl(fd, F_GETFL, 0);
    //"Resource temporarily unavailable" with O_NONBLOCK
    file_flags=file_flags|O_APPEND;
    fcntl(fd,F_SETFL,file_flags);
    print_flags(fd);
    if(read(fd,&buff,1)!=EOF)
        printf("Read succeeded. Chararcter was %c\n",buff);
    else
        perror("\nRead failed");
    buff='A';
    if(write(fd,&buff,1)!=EOF)
        printf("\nWrite succeede\n");
    else
        //"Bad file descriptor"
        perror("\nWrite failed");
    //    close(fd);
    return 0;
}

void print_flags(int fd){

    int access_mode,file_flags;
    file_flags=fcntl(fd, F_GETFL,O_APPEND);
    access_mode=file_flags&O_ACCMODE;
    switch (access_mode) {
        case O_RDWR:
            printf("Access mode:Read/Write");
            break;
        case O_RDONLY:
            printf("Access mode:read only");
            break;
        case O_WRONLY:
            printf("Access mode:write only");
            break;
        default:
            printf("Access mode:unknown access mode");
            break;
    }
    if (file_flags & O_NONBLOCK) {
        printf("\nO_NONBLOCK: ON");
    }else
        printf("\nO_NONBLOCK: OFF");

    if(file_flags & O_APPEND)
        printf("\nO_APPEND: OFF\n");
    else
        printf("\nO_APPEND: On\n");

}
