#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main (void) {
	pid_t pid;
	char buf[20];
	printf("Enter input (n = next, other input terminates):");
	fgets(buf, 20, stdin);
	while(buf[0] == 'n') {
		pid = fork();
		if (pid < 0) {
			perror("Fork:");
			exit(1);
		}
		//double fork
		if (pid == 0) {
			if ((pid=fork())<0)
			{
				printf("fork error\n");
			}
			else if (pid>0)
				exit(0);
			
			sleep(2); // This is actually something real work
	      	exit(0);
	      
	  	}
	  	while(wait(NULL)>0);
  		printf("Enter input (n = next, other input terminates):");
	    fgets(buf, 20, stdin);
  		
	}
}