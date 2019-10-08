#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>
int main()
{
	if(fork() && fork())
		fork();
	if(fork() || fork())
		fork();
	printf("OS_Fork %d\n",getpid());

	/*double i=0;

	fork();
	//system("ps");

	while(i<1000000000){i++;};
	printf("OS\n");*/
	/*
	// The following code will ensure the order is Child Output followed by Parent. Warning will come.
	//Question 3
	printf("OS\n");
	fork();
	wait(NULL);
	printf("Course\n");
	fork();
	wait(NULL);
	printf("2019\n");
	fork();
	wait(NULL);
	printf("IIITDM\n");	
	//*/

	// Question 2
	/*if(fork())
	{
		wait(NULL);
		if(!fork())
		{
			//wait(NULL);
			fork();
			wait(NULL);
			printf("1\n");
		}
		else
		{
			wait(NULL); 
			printf("2\n");
		}
	}
	else printf("3\n");

	printf("4\n");
	//*/
	//QUESTION BALA
	/*pid_t p=fork();
	if(p==0)
	{
		//sleep(1);
		printf("Hi\n");
		sleep(10);
		abort();
	}
	else if(p>0)
	{
		wait(NULL);
		
		printf("APrent\n");
	}	*/
	/*char te[10];
	printf("ENter hi\n");
	scanf("%s",te);
	printf("TO %s\n",te );
	//printf("%c",215);*/


	return 0;
}