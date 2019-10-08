#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

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

	pid = vfork();

		
	if(pid>0)
	{	
		printf("Desc .5(parent)\n");   // 8 1 2 7 9 10 4 3 5 6   --> 1 2 3 4 5 | 7 6 8 9 10   val =5;    j<4;
		int temp;
		int val;
		if(n%2==0)
			val=n/2;
		else
			val=(n/2)+1;

		for(int i=1;i<val;i++)
		{	
			for(int j=val;j<n-i;j++)
				{
					if(a[j]<a[j+1])
					{	
						temp=a[j];
						a[j]=a[j+1];
						a[j+1]=temp;
					}	
				
				}
		}
		for(int i=val;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");
	}

	else
	{
		int val;
		if(n%2==0)
			val=n/2;
		else
			val=(n/2)+1;
		printf("Ascending .5(child)\n");
		int temp;
		for(int i=1;i<val;i++)
		{	
			for(int j=0;j<val-i;j++)
				{
					if(a[j]>a[j+1])
					{	
						temp=a[j];
						a[j]=a[j+1];
						a[j+1]=temp;
					}	
				
				}
		}
		for(int i=0;i<val;i++)
			printf("%d ",a[i]);
		printf("\n");
		exit(1);
	}

	return 0;


}