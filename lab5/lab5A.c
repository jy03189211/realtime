//
//  main.c
//  Lab5
//
//  Created by jy03189211 on 13-2-12.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
void func();
int main(int argc, const char * argv[])
{
// messy code if without static, since mem would be released earlier than output,why?how?******************************************************
    
// life cycle is the same as the program, wouldn't be released before
    
   static char buff[5];
   char c='c';
   setvbuf(stdout, buff, _IOFBF, 5);
    
//    unsigned char c='c';
//    int a=sizeof(c);
//    printf("%d!\n",a);
//    result is 1
//    but sizeof('c') result is 4, why?pointer?********because "sizeof" is not a function

   for (c='a'; c<='m'; c++) {
        putchar(c);
        sleep(1);
       //fflush(stdout);
    }
    return(0);
}

