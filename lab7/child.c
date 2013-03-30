//
//  child.c
//  Lab7
//
//  Created by jy03189211 on 13-3-25.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
int main(int argc, const char * argv[])
{
    
    int i,fd;
    fd=atoi(argv[0]);
    for (i=0; i<5; i++) {
        write(fd, argv[1], 5);
        sleep(1);
    }
    close(fd);
    return 0;
}
