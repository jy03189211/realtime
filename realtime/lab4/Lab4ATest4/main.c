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
    int fd,file_flags,error_flag;
    char buff;
//    fd=open("/dev/tty",O_RDWR);
    fd=open("/dev/tty",O_RDONLY);
    file_flags = fcntl(fd, F_GETFL, 0);
    file_flags=file_flags|~O_NONBLOCK|O_APPEND;
    fcntl(fd,F_SETFL,file_flags);
    print_flags(fd);
    error_flag=read(fd,&buff,1);
    if(error_flag==1||error_flag==0)
        printf("Read succeeded. Chararcter was %c\n",buff);
    else
        perror("\nRead failed");
    buff='A';
    error_flag=write(fd,&buff,1);
    if(error_flag==1||error_flag==0)
        printf("\nWrite succeeded\n");
    else
        perror("\nWrite failed");
    //    close(fd);
    return 0;
}

void print_flags(int fd){
    
    int access_mode,file_flags;
    file_flags=fcntl(fd, F_GETFL,0);
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