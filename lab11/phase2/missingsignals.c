/* This program illustrates how signals are missed because there is no 
   signal queue. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <aio.h>
#define N 10
#define KEYBOARD 0
#define FELLOW 1

int OpenChatFellow();
void sig_handler(int ,siginfo_t *,void *);

char chr_fellow,chr_own=' ';
struct aiocb aio_fellow,aio_keyboard;
int ret;

int main(void) {
    int fellow_desc;
    
    pid_t child;
    int result, i, j;
    int keyboard=0;
    
    //set up the AIO request
    aio_keyboard.aio_fildes = STDIN_FILENO;
    aio_keyboard.aio_buf = &chr_own;
    aio_keyboard.aio_nbytes = 1;
    aio_keyboard.aio_offset = 0;
    aio_keyboard.aio_reqprio = 0;

    /* Link the AIO request with the Signal Handler */
    aio_keyboard.aio_sigevent.sigev_notify = SIGEV_SIGNAL ;
    aio_keyboard.aio_sigevent.sigev_signo = SIGRTMAX ;
    aio_keyboard.aio_sigevent.sigev_value.sival_int = KEYBOARD;
    aio_keyboard.aio_lio_opcode = 0;

    fellow_desc=OpenChatFellow();
    aio_fellow.aio_fildes = fellow_desc;
    aio_fellow.aio_buf = &chr_fellow;
    aio_fellow.aio_nbytes = 1;
    aio_fellow.aio_offset = 0;
    aio_fellow.aio_reqprio = 0;

    aio_fellow.aio_sigevent.sigev_notify = SIGEV_SIGNAL ;
    aio_fellow.aio_sigevent.sigev_signo = SIGRTMAX ;
    aio_fellow.aio_sigevent.sigev_value.sival_int = FELLOW;
    aio_fellow.aio_lio_opcode = 0;


    struct sigaction sigact,oldact;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_sigaction=sig_handler;
    sigact.sa_flags=SA_SIGINFO;


    if (sigaction(SIGRTMAX,&sigact,&oldact)<0)    
    {   
        fprintf(stderr, "\nCannot set signal handler");
        exit(0);
    }
    //initiate io
   aio_read(&aio_keyboard);
   while ( chr_own != 'q' && chr_own != 'Q' ) {
        
        aio_read(&aio_fellow);

        //wait for io completion
        while ( aio_error(&aio_fellow) == EINPROGRESS);
        //end of file
        ret=aio_return(&aio_fellow);
        if (ret==0){
            printf("\n");
            break;
        } 
            

    }

   sigaction(SIGRTMAX, &oldact, NULL);
   return 0;
}

void sig_handler(int sig_no,siginfo_t *info,void *dummy) {
    if (info->si_value.sival_int==KEYBOARD)
    {   
        aio_read(&aio_keyboard);

        write(1,&chr_own,1);
    }
    if (info->si_value.sival_int==FELLOW)
    {   

        if(ret>0){
            //there would be an unexpected 'z' appearing randomly?????????????
            write(1,&chr_fellow,1);
        }
        
    }
}
