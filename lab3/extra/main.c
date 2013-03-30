//
//  main.c
//  Lab3extra
//
//  Created by jy03189211 on 13-1-25.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>  
int main(int argc, const char * argv[])
{
    
    printf("POSIX version: %ldL\nClockTicks per/sec:%ld",
           sysconf(_SC_VERSION),
           sysconf(_SC_CLK_TCK));
    
    if (sysconf(_SC_THREADS)<0) {
        printf("\nPOSIX threads:not supported");
    }else
        printf("\nPOSIX threads: supported");

    if ( sysconf(_SC_REALTIME_SIGNALS)<0) {
        printf("\nRealtime Signals:not supported");
    }else
        printf("\nRealtime Signals:supported \n");
    
    return 0;
}

