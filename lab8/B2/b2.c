#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, const char *argv[])
{
  pid_t pid;
  pid=fork();
  if(pid==0){
    printf("Im am child\n");
    alarm(5);
    execl("child.exe","child.exe",NULL);
    exit(0);
  }
  wait(NULL);
  return 0;
}
