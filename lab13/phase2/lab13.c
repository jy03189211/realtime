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
static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_t t[11];

static void *threadFunc(void *arg){
	int loops=*((int *)arg);
	int loc,s;
	long i;
	for (i = 0; i < loops; i++)
	{
		 s = pthread_mutex_lock(&mtx);
		 loc=counter;
		 loc++;
		 counter=loc;
		 s=pthread_mutex_unlock(&mtx);
	}

	return (void *)loc;

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

