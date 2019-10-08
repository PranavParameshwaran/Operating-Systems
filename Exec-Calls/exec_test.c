#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
int main()
{
/*	pid_t pid;
	pid = fork();
	//char arg[100][100];
	char *arg[]={"ps",NULL}; 
	//strcpy(arg[1],NULL);
	if(pid==0)
	{
		//printf("\n");
		execvp(arg[0],arg);
		printf("CHILD\n");
	}
	else
	{
		printf("Parent\n");
	}
	printf("OVERALL\n");*/
	pid_t pid;
	pid = fork();
	if(pid==0)
	{
		//printf("\n");
		execlp("ls","ls",NULL);
		printf("CHILD\n");
	}
	else
	{
		printf("Parent\n");
	}
	printf("OVERALL\n");

	return 0;
}	