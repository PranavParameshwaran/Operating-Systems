#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int size;
struct dat
{
	int val;
	int freq;
};

void *mean(void **parameter);
void *median(void **parameter);
void *mode(void **parameter);

int main(int argc, char *argv[])
{
	size = argc-1;
	pthread_t tid[3];
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	pthread_create(&tid[0],&attr,mean,argv);
	pthread_create(&tid[1],&attr,median,argv);  
	pthread_create(&tid[2],&attr,mode,argv);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	return 0;
}

void *mean(void **parameter)
{
	int sum=0;
	for(int i=0;i<size;i++)
	{
		sum+= atoi(parameter[i+1]);
	}
	float mean = sum/size;
	printf("Mean -> %f\n",mean);

	pthread_exit(0);
	
}

void *median(void **parameter)
{
	int arr[size];
	for(int i=0;i<size;i++)
		arr[i] = atoi(parameter[i+1]);
	int temp;
	//int median;
	for(int i=1;i<size;i++)
	{	
		for(int j=0;j<size-i;j++)
		{
			if(arr[j]>arr[j+1])
			{	
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}	
		
		}
	}
	int val=size/2;
	float median;
	if(size%2==0)
		median = (float)(arr[val-1]+arr[val])/2;
	else
		median = arr[val];
	printf("Median -> %f\n",median );

	pthread_exit(0);

}

void *mode(void **parameter)
{
	int chk=0;
	int endd=-1;
	int beg=-1;
	int temp;
	struct dat n[size];
	int arr[size];

	for(int i=0;i<size;i++)
		arr[i] = atoi(parameter[i+1]);

	for(int i=1;i<size;i++)
	{	
		for(int j=0;j<size-i;j++)
		{
			if(arr[j]<arr[j+1])
			{	
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}	
		}
	}

	for(int i=0;i<size;i++)
	{
		chk=0;
		for(int j=0;j<=endd;j++)
		{
			if(n[j].val==arr[i])
			{
				n[j].freq+=1;
				chk=1;
				break;
			}
		}
		if(beg==-1)
			beg=0;
		if(chk==0)
		{
			endd++;
			n[endd].val=arr[i];
			n[endd].freq=1;			
		}
	}
	/*endd++;
	int temp;
	for(int i=1;i<endd;i++)
	{	
		for(int j=0;j<endd-i;j++)
		{
			if(n[j].freq<n[j+1].freq)
			{	
				temp=n[j].freq;
				n[j].freq=n[j+1].freq;
				n[j+1].freq=temp;
			}	
		}
	}*/
	int max=n[0].freq;
	//printf("%d\n",max );
	printf("MODE ->");
	for(int i=0;i<=endd;i++)
	{
		if(n[i].freq==max)
			printf("%d ",n[i].val);
	}
	
	pthread_exit(0);
}