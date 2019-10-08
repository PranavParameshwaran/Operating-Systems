#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

/*void Msort(int beg, int end);
void Merge(int beg,int end);*/

int a[100];

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
			if(a[i]<a[j]) 
			{
				b[k]=a[i];
				i++;
			}
			else
			{
				b[k]=a[j];
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
				{	b[k]=a[ma]; 
					k++;
				}
			}
		else if(j>end)
			{
				for(int ma=i;ma<=mid;ma++)
				{	b[k]=a[ma];
					k++;
				}
			}
	}
	
	int z=0;
	for(int ma=beg;ma<=end;ma++)
	{
		a[ma]=b[z];
		z++;
	}
}

void Msort(int beg, int end)
{
	if(beg<end)
	{
		int mid=(beg+end)/2;
		pid_t pid;
		pid = vfork();
		if(pid==0)
		{
			Msort(beg, mid);
			exit(0);
		}
		else
		{
			Msort(mid+1,end);
			wait(NULL);
			Merge(beg,end);
		}
	}	
}


int main()
{
	int n;
	
	printf("Enter the number of els in A\n");
	scanf("%d",&n);
	printf("Enter the els in A\n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	Msort(0,n-1);
	printf("AFTER SORTING THE ANSWER IS : ");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}

