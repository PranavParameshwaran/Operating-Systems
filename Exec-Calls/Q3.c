#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
int Primer(int n);
int main()
{
	
	int n;
	int k=0;
	int P[100];
	pid_t pid;
	printf("Enter the number of els to be\n");
	scanf("%d",&n);
	pid = vfork();
	
	// FIBONACCI SERIES
	/*
	int F[100];
	if(pid==0)
	{
		F[0] = 0;
		F[1] = 1;
		for(int i=2;i<=n;i++)
		{
			F[i] = F[i-1] + F[i-2];
		}
		
		exit(1);
	}	
	else
	{	
		printf("Fibonacci(child):  ");
		for (int i = 0;i<=n; i++)
		{
			printf("%d ", F[i]);
		}
		printf("\n");
	}*/

	// PRIME GENERATION

	if(pid==0)
	{
		int flag=0;
		int j=2;
		while(k<n)
		{
			flag=0;
			for(int i=2;i<=j;i++)
			{
				if(j!=i && j%i==0)
					flag=1;
			}
			if(flag==0)
			{	
				P[k]=j;
				k++;
			}
			j++;
		}
		exit(1);

		
	}
	else if(pid>0)
	{
		wait(NULL);
		printf("\nPrime(parent):  ");
		for (int i = 0;i<k; i++)
		{
			printf("%d ", P[i]);
		}
		printf("\n");
		
	}
	return 0;

}

