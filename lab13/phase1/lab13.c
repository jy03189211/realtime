#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>
#include <pthread.h>

static int counter=0;

pthread_t t[11];

static void *threadFunc(void *arg){
	int loops=*((int *)arg);
	int loc,s;
	long i;
	for (i = 0; i < loops; i++)
	{
		 
		 loc=counter;
		 loc++;
		 counter=loc;
		 
	}

	return (void *)i;

}

int main(int argc, const char * argv[])
{	
	int i,loops=100000;
	void *ret;
	for (i = 0; i < 10; i++)
	{	
		pthread_create(&t[i],NULL,threadFunc,&loops);
	}
	for (	i = 0; i < 10; ++i)
	{
		pthread_join(t[i], &ret);
		printf("thread %d :%ld\n",i,(long)ret);
	}
	printf("glob counter:%d\n",counter);
	printf("lost increments:%d\n",loops*10-counter);
	return 0;
}

