//
//  main.c
//  Lab4B
//
//  Created by jy03189211 on 13-2-6.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
void print_permissions(const char *fname, struct stat *addbuf);

int main(int argc, const char * argv[])
{
    
    int i;
    struct stat buf;
    char *ptr;
    const char *filename=argv[1];
    struct stat statbuf;
    
//    print_permissions(argv[i],&statbuf);
    
    for(i=1;i<argc;i++){
        printf("%s:",argv[i]);
        if(lstat(argv[i],&buf)<0){
            perror("lstat error");
            continue;
        }
        // /etc/passwd
        if (S_ISREG(buf.st_mode))
            ptr = "regular";
        // /etc
        else if (S_ISDIR(buf.st_mode))
            ptr = "directory";
        // /dev/tty
        else if (S_ISCHR(buf.st_mode))
            ptr = "character special";
        // /dev/scsi/host0/bus0/target0/lun0/cd
        else if (S_ISBLK(buf.st_mode))
            ptr = "block special";
        // /dev/initctl
        else if (S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        //  /dev/cdrom
        else if (S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        // /dev/log:
        else if (S_ISSOCK(buf.st_mode))
            ptr = "socket";
        // else
        else
            {
                ptr = "** unknown mode **";
                printf("%s\n", ptr);
            }
        printf("%s",ptr);
        print_permissions(argv[i],&statbuf);
        
    }
    return 0;
}


void print_permissions(const char *fname, struct stat *addbuf){
    if(lstat(fname,addbuf)<0){
        perror("stat");
    }else
        printf("\nFile: %s Permissions: %o\n",fname,addbuf->st_mode&~S_IFMT);
}


