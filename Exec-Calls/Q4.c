#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	int a[20];
	int n;
	pid_t pid;
	printf("Enter the number of els in A\n");
	scanf("%d",&n);
	printf("Enter the els in A\n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);

	pid = fork();

	if(pid==0)
	{
		printf("Ascending(child)\n");
		int temp;
		for(int i=1;i<n;i++)
		{	
			for(int j=0;j<n-i;j++)
				{
					if(a[j]>a[j+1])
					{	
						temp=a[j];
						a[j]=a[j+1];
						a[j+1]=temp;
					}	
				
				}
		}
		for(int i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");
		
	}	
	else
	{	
		wait(NULL);
		printf("Desc(parent)\n");
		int temp;
		for(int i=1;i<n;i++)
		{	
			for(int j=0;j<n-i;j++)
				{
					if(a[j]<a[j+1])
					{	
						temp=a[j];
						a[j]=a[j+1];
						a[j+1]=temp;
					}	
				
				}
		}
		for(int i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");
	}

	return 0;


}ÿ