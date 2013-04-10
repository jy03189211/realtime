#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
int OpenChatFellow();
int main(int argc, const char * argv[])
{
    char chr_fellow,chr_own;
    int fellow_desc,n,r;
    fd_set rd_set,wrt_set;
    fellow_desc=OpenChatFellow();
    
    do{
            FD_ZERO(&rd_set);
            //FD_ZERO(&wrt_set);
            //FD_SET(1, &wrt_set);
            FD_SET(0, &rd_set);
            FD_SET(fellow_desc, &rd_set);
            //(1)if  FD_SET(1, &wrt_set);
            //and set &wrt_set as the 3rd parameter of select()
            //why it doesn't work???????????????????????????????????
            n=select(fellow_desc+1,&rd_set,NULL,NULL,NULL);
            //(2)printf("%d!!!\n",n); why it always prints one ????????

            //read kb
            if (FD_ISSET(fellow_desc,&rd_set))
            {   
                r=read(fellow_desc,&chr_fellow,1);
                write(1,&chr_fellow,1);
            }
           //read fellow 
            if((chr_own!='q'&&chr_own!='Q')){
                if (FD_ISSET(0,&rd_set))
                {   
                    read(0,&chr_own,1);
                    write(1,&chr_own,1);
                }
            }
        }while(r>0);
    return 0;
}
