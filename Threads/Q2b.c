#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

float Q1,Q2,Q3,IQR;
float Min,Max;

void *median(void *Arr);
void *LQuartile(void *Arr);
void *UQuartile(void *Arr);
void *MinOutlier(void *Arr);
void *MaxOutlier(void *Arr);

int size;
int main(int argc, char *argv[])
{
	pthread_t tid[5];
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	size = argc-1;
	int arr[size];
	for(int i=0;i<size;i++)
		arr[i] = atoi(argv[i+1]);
	int temp;
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

	pthread_create(&tid[0],&attr,median,arr);
	pthread_create(&tid[1],&attr,LQuartile,arr);  
	pthread_create(&tid[2],&attr,UQuartile,arr);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	IQR = Q3 - Q1;
	pthread_create(&tid[3],&attr,MinOutlier,arr);
	pthread_create(&tid[4],&attr,MaxOutlier,arr);

	pthread_join(tid[3],NULL);
	pthread_join(tid[4],NULL);
	printf("_____________________________________________________________________________________________________________________________________________\n");
	//printf("|| ");
	int f0=0,f1=0,f2=0,f3=0,f4=0;
	for(int i=0;i<size;i++)
	{
		if(arr[i] < Min)
			printf("%d ",arr[i]);
		
		if(arr[i] >= Min && arr[i]<=Q1)
		{
			if(f0==0)
			{
				printf(" < Outlier <--|Min => %0.1f||",Min);
				f0=1;
			}
			printf("%d ",arr[i]);
		}

		else if(arr[i]>Q1 && arr[i]<=Q2)
		{
			if(f1==0)
			{
				printf("||Q1 => %0.1f|| ",Q1);
				f1=1;
			}	
			printf("%d ",arr[i]);
		}

		else if(arr[i]>Q2 && arr[i]<=Q3)
		{
			if(f2==0)
			{
				printf("||Q2 => %0.1f|| ",Q2);
				f2=1;
			}	
			printf("%d ",arr[i]);
		}

		else if(arr[i]>=Q3 && arr[i]<Max)
		{
			if(f3==0)
			{
				printf("||Q3 => %0.1f|| ",Q3);
				f3=1;
			}	
			printf("%d ",arr[i]);
		}
		else if(arr[i]>=Max)
		{
			if(f4==0)
			{
				printf("|Max => %0.1f|--> Outlier > ",Max);
				f4=1;
			}
			printf("%d ",arr[i]);
		}

	}
	printf("\n");
	printf("______________________________________________________________________________________________________________________________________________\n");
	return 0;
}

void *median(void *Arr)
{
	int *A = Arr;
	int val=size/2;
	//float median;
	if(size%2==0)
		Q2 = (float)(A[val-1]+A[val])/2;
	else
		Q2 = A[val];

	pthread_exit(0);
}

void *LQuartile(void *Arr)
{
	int *A = Arr;
	int val=size/2;
	int val1 = val/2;
	//float median;
	if(val%2==0)
		Q1 = (float)(A[val1-1]+A[val1])/2;
	else
		Q1 = A[val1];

	pthread_exit(0);
}

void *UQuartile(void *Arr)
{
	int *A = Arr;
	int val=size/2;
	int val1 = val/2;
	//float median;
	if(val%2==0)
		Q3 = (float)(A[val+val1-1]+A[val+val1])/2;
	else
		Q3 = A[val+val1];

	pthread_exit(0);
}

void *MinOutlier(void *Arr)
{
	int *A = Arr;
	Min = Q1 - (1.5 * IQR);
	pthread_exit(0);
}

void *MaxOutlier(void *Arr)
{
	int *A = Arr;
	Max = Q3 + (1.5 * IQR);
	pthread_exit(0);
}