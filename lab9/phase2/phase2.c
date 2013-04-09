#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include  <errno.h>
#include <signal.h>

void sig_handler(int sig_no);
static volatile sig_atomic_t sigflag;
int main(void) {
  pid_t child ;
  sigset_t newmask, oldmask, zeromask;
  if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
    fprintf(stderr, "Cannot set signal handler\n");
    exit(0);
  }
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGUSR1);
  if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
    printf("SIG_BLOCK error");
  child = fork();
  if (child==0) { 
    while( 1 ) {
      write(1, "1", 1);
      kill(getppid(), SIGUSR1);
      while(sigflag==0){
        if(sigsuspend(&zeromask)!=-1)
          printf("sigsuspend error");
      }
      sigflag=0;
      if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        printf("SIG_SETMASK error");
    }
    exit(0); 
  }
  while( 1 )  {
    write(1, "2" , 1);
    kill(child, SIGUSR1);
    while(sigflag==0){
      if(sigsuspend(&zeromask)!=-1)
        printf("sigsuspend error");
    }
    sigflag=0;
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
      printf("SIG_SETMASK error");
  }
  exit(0);
}
void sig_handler(int sig_no) {
  if (sig_no==SIGUSR1)
  {
    sigflag=1;
  }
}
