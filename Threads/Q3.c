#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct data
{
	int beg;
	int end;
	
};

int size;
int ArrM[100],ArrQ[100];

void *QuickSort(void *Q);
int partition(int beg,int end);
void *MergeSort(void *M);
void Merge(int beg,int end);


int main(int argc, char *argv[])
{
	pthread_t tid[2];
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	struct data StM,StQ;
	size = argc -1;
	StM.beg = 0;
	StM.end = size-1;
	StQ.beg = 0;
	StQ.end = size-1;
	for(int i=1;i<=size;i++)
	{
		ArrM[i-1] = atoi(argv[i]);
		ArrQ[i-1] = atoi(argv[i]);
	}
	pthread_create(&tid[0],&attr,MergeSort,&StM);
	pthread_create(&tid[1],&attr,QuickSort,&StQ);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	printf("\nQuickSort\n");
	for(int i=0;i<size;i++)
		printf("%d ",ArrQ[i] );
	printf("\nMergeSort\n");
	for(int i=0;i<size;i++)
		printf("%d ",ArrM[i] );
	printf("\n");
	return 0;
}

// QUICK SORT
void *QuickSort(void *Q)
{
	struct data *DQ = Q;
	int begi = DQ->beg;
	int endi = DQ->end;
	if(begi<endi)
	{	
		int j;
		j=partition(begi,endi);
		struct data QLeft,QRight;
		QLeft.beg = begi;
		QLeft.end = j-1;

		QRight.beg = j+1;
		QRight.end = endi;

		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init (&attr);

		pthread_create(&tid[0],&attr,QuickSort,&QLeft);
		pthread_create(&tid[1],&attr,QuickSort,&QRight);

		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);
		/*
		quickSort(beg,j-1);
		quickSort(j+1,end);*/
	}
	pthread_exit(0);
}

int partition(int beg,int end)
{
	int pivot=ArrQ[beg];
	int i=beg;
	int j=end;
	while(i<j)
	{	
		
		while(ArrQ[i]<=pivot && i<end)
		{	i++;
			
		}
		while(ArrQ[j]>pivot && j>beg)
		{	j--;
			
		}

		if(i<j)
		{
			int temp=ArrQ[i];
			ArrQ[i]=ArrQ[j];
			ArrQ[j]=temp;
		}
	}
	
	{
		int temp=ArrQ[beg];
		ArrQ[beg]=ArrQ[j];
		ArrQ[j]=temp;
	}

return(j);
}


// MERGE SORT
void *MergeSort(void *M)
{
	struct data *DM = M;
	int begi = DM->beg;
	int endi = DM->end;
	if(begi<endi)
	{
		int mid=(begi+endi)/2;

		struct data MLeft,MRight;
		MLeft.beg = begi;
		MLeft.end = mid;

		MRight.beg = mid+1;
		MRight.end = endi;

		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init (&attr);

		pthread_create(&tid[0],&attr,MergeSort,&MLeft);
		pthread_create(&tid[1],&attr,MergeSort,&MRight);
		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);
		/*Msort(beg, mid);
		Msort(mid+1,end);*/
		Merge(begi,endi);
	}
	pthread_exit(0);
}

void Merge(int beg,int end)
{	
	int i=beg,k;  
	int mid=(beg+end)/2;
	int j=mid+1;  
	int b[end-beg+1];
	
	for(k=0;k<(end-beg+1);k++)
	{
		if(i<=mid && j<=end)
		{
			if(ArrM[i]<ArrM[j]) // strcmpi(a[i],a[j]<0)
			{
				b[k] = ArrM[i];
				i++;
			}
			else
			{
				b[k] = ArrM[j];
				j++;
			}
		}
		
		else break;
				
	}
	if(i>mid || j>end)
	{
		if(i>mid)
			{
				for(int ma=j;ma<=end;ma++)
				{	b[k] = ArrM[ma];
					k++;
				}
			}
		else if(j>end)
			{
				for(int ma=i;ma<=mid;ma++)
				{	b[k] = ArrM[ma];
					k++;
				}
			}
	}
	
	int z=0;
	for(int ma=beg;ma<=end;ma++)
	{
		ArrM[ma] = b[z];
		z++;
	}
}