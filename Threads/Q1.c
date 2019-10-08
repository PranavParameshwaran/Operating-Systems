#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void *prime(void *p);

int main(int argc, char *argv[])
{
	int ul = atoi(argv[1]);
	pthread_t tid[100];
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	int k=0;
	printf("Answer %d\n",ul);
	for(int i=2;i<ul;i++)
	{
		int par = i;
		
		/*pthread_attr_t attr;
		pthread_attr_init (&attr);*/
		pthread_create(&tid[k],&attr,prime,par);	// argv[1] has upper limit of Prime Limit
		k++;
	}
	for(int z=0;z<k;z++)
		pthread_join(tid[z],NULL);
	printf("\n");


	return 0;
}

void *prime(void *p)
{
	int val = p;
	int flag=0;
	for(int i=2;i<val;i++)
	{
		if(val%i==0)
			flag=1;
	}	
	if(flag==0)
	{
		printf("%d ",val);
		fflush(stdout);
	}
	pthread_exit(0);
}