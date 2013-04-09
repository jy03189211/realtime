/* Process synchronization using signals and pause. This is not perfect solution.
    Learn to understandm, why it blocks sooner or later */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include  <errno.h>
#include <signal.h>

void sig_handler(int sig_no);

int main(void) {
    pid_t child ;

    if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot set signal handler\n");
        exit(0);
    }
    child = fork();
    if (child==0) { //Child
        while( 1 ) {
            write(1, "1", 1);
            kill(getppid(), SIGUSR1);
            pause(); 
        
        }
        exit(0); // Never reached. Use ctrl + c to tsop
   }
   //Parent
    while( 1 )  {
        pause();
        write(1, "2" , 1);
        kill(child, SIGUSR1);        
        
   }
   exit(0);
}
void sig_handler(int sig_no) {
    // Empty but needed.
}
//since race condition, the signal was delivered before  the processes turned to wait
//then the signal would be lost. the process will be set to pause forever