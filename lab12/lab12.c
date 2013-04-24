#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#define MAX 20
int main(void)  {
	int n,i;
	int fd[2];
	pid_t pid;
	char chr='0';
	char line[MAX];

	pipe(fd);
	pid=fork();
	//child
	if (pid == 0) {
		close(fd[0]);
		for ( i = 0; i < 10; i++)
		{
			write(fd[1],&chr,1);
			chr++;
			sleep(1);	
		}
		close(fd[1]);
		exit(0);
	}
	//parent
	close(fd[1]);
	while(read(fd[0],&chr,1)>0){
		
		write(1,&chr,1);
		sleep(1);
	}
	printf("\n");
	close(fd[0]);

	return 0;
}