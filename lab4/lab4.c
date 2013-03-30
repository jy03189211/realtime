//
//  main.c
//  lab4
//
//  Created by jy03189211 on 13-2-5.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
void print_flags(int fd);

int main(int argc, const char * argv[])
{
    int fd;
    fd=open("/dev/tty",O_RDWR);
    print_flags(fd);
    
    return 0;
}

void print_flags(int fd){
    
    int access_mode,file_flags;
    file_flags=fcntl(fd, F_GETFL,O_APPEND);
    access_mode=file_flags&O_ACCMODE;
    switch (access_mode) {
        case O_RDWR:
            printf("Read/Write");
            break;
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        default:
            printf("unknown access mode");
            break;
    }
//    if (access_mode == O_WRONLY)
//		printf("\nAccess mode is Write Only");
//    
//    else
//        printf("\nAccess mode is not Write Only");
//    
//    if(access_mode==O_RDWR)
//        printf("\nAccess mode is Read/Write Only");
//    else
//        printf("\nAccess mode is not Read/Write Only");
//    if(access_mode == O_RDONLY)
//        printf("\nAccess mode is Read Only");
//    else
//        printf("\nAccess mode is not Read Only");
//    
	if (file_flags & O_NONBLOCK) {
		printf("\nWas in non-blocking mode");
    }else
		printf("\nWas in blocking mode");
    
    if(file_flags & O_APPEND)
        printf("\nWas in append mode\n");
    else
        printf("\nWas not in append mode\n");

}