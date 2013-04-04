
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
static void alrm_handler(int);
int main(int argc, const char *argv[])
{
  int i;
  pid_t pid;
  if (signal(SIGALRM,alrm_handler)==SIG_ERR)
    printf("Cannot set signal handler/n");
  alarm(5);
  pid=fork();
  //child
  if(pid==0){
    printf("I am child, I start to pause.\n");
    pause();
    printf("I am child, pause stopped.\n");
    
  }
  //parent

  printf("I am papa, I start to pause\n");
  pause();
  printf("I am papa, paused stopped.\n");
  return 0;
}
static void alrm_handler(int sig_no){
}
