//
//  lab3bbb.c
//  lab3_1
//
//  Created by jy03189211 on 13-1-23.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, const char * argv[])
{
    int fd;
    char *buff="BBBB";
    fd=open("exlog.txt",O_WRONLY|O_CREAT|O_APPEND,0700);
    int i=0;
    while (i<10000) {
        write(fd, buff, 4);
        i++;
    }
    close(fd);
    return 0;
}
