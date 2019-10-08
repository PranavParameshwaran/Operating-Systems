#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	//int a[20];
	int n;
	pid_t pid;
	printf("Enter the number of els to print(Half goes for child and other for Parent)\n");
	scanf("%d",&n);
	/*printf("Enter the els in A\n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);*/

	pid = fork();

	if(pid==0)
	{
		printf("EVEN NUMBERS(child):  ");
		for(int i=0;i<n;i++)
		{
			if(i%2==0)
				printf("%d ",i);
		}
		//exit(1);
	}	
	else
	{	
		wait(NULL);
		printf("\nODD NUMBERS(parent):  ");
		for(int i=0;i<n;i++)
		{
			if(i%2==1)
				printf("%d ",i);
		}
		printf("\n");
	}

	return 0;


}