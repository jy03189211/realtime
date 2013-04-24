/* This program illustrates how signals are missed because there is no 
   signal queue. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#define N 10

void sig_handler(int signo,siginfo_t *info,void *);
int n = 0;

int main(void) {

    pid_t child;
    int result, i, j;

    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction=sig_handler;
    act.sa_flags=SA_SIGINFO;

    union sigval value;
    if (sigaction(SIGRTMAX,&act,NULL)==-1)    
    {   
        fprintf(stderr, "\nCannot set signal handler");
        exit(0);
    }

    // if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
    //     fprintf(stderr, "\nCannot set signal handler");
    //     exit(0);
    // }
    int k=0;
    for (i = 0 ; i < N ; i++) {
		child = fork();
        if (child==0) { //Child  
            for (j = 0 ; j < 2 ; j++) {

                value.sival_int=n;
     //real-time signals, numbered from 32 (SIGRTMIN) to 63 (SIGRT-
     //  MAX)
     //Here's the thicky part:
     //given SIGUSR1 : SIGUSR1   number is 30,10,16 
     //so use SIGRTMAX instead
                sigqueue(getppid(), SIGRTMAX,value);
            }
            exit(0);
        }
    }	
    while ((result = wait(NULL)) > 0 || (result < 0 && errno == EINTR)) {
        if ( result < 0)
            printf("Wait was interrupted\n");
    }
    printf("Signal has been received %d times\n", n); 
    return 0;
}

void sig_handler(int sig_no,siginfo_t *info,void *dummy) {
    if (sig_no == SIGRTMAX) {
        printf("%d\n",info->si_value.sival_int );
        n++;
    }
    return;
}
