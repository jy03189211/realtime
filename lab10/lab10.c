#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/select.h>
#define MAXLINE 80

int OpenChatFellow();
void counter(int i);
int main(int argc, const char * argv[])
{
    char chr_fellow,chr_own;
    int fellow_desc,fd_kb,n,r;
    fd_set fdset;

    FD_ZERO(&fdset);
    FD_SET(fd_kb, &fdset);
    FD_SET(fellow_desc, &fdset);
    
    fellow_desc=OpenChatFellow();
    n=select(fellow_desc+1,&fdset,NULL,NULL,NULL);
    //parent
    while((r=read(fellow_desc, &chr_fellow, 1))>0||chr_own!='q'&&chr_own!='Q'){
        if(n>0){
            if (FD_ISSET(fd_kb,&fdset))
            {
                read(0,&chr_own,1);
                write(1,&chr_own,1);
            }
            if (FD_ISSET(fellow_desc,&fdset))
            {
                write(1,&chr_fellow,1);
            }
        }    
    }
    return 0;
}
