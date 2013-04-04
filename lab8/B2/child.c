#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
static void alarm_handler(int);
int main(int argc, const char *argv[])
{
  if(signal(SIGALRM,alarm_handler)==SIG_ERR)
    printf("Cannot set signal handler\n");
  pause();
  return 0;
}
static void alarm_handler(int sig_no){
  if(sig_no==SIGALRM  ){
    printf("signal received!\n");
  }
}
