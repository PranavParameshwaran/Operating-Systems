#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int main()
{
	int fd1[2];
	//int fd2[2];
	pipe(fd1);
	//pipe(fd2);
	pid_t p;
	p = fork();
	if(p==0)
	{
		close(fd1[0]);
		char buf[] = "Hello";
		write(fd1[1],buf,strlen(buf)+1);
		close(fd1[1]);
		//exit(1);
	}
	else
	{
		wait(NULL);
		char full[100];
		char full1[100];
		read(fd1[0],full,100);		// The read() will completely clear the pipe once it has read from the pipe. To read again something has to be written in the Pipe
		
		char buf2[]="THIS WORKS";
		write(fd1[1],buf2,strlen(buf2)+1);
		read(fd1[0],full1,100);
		
		printf("%s\n",full);
		printf("%s\n",full1);
		/*
		read(fd1[0],full,100);*/
		//printf("%s\n",full);
		close(fd1[1]);
		close(fd1[0]);
		
	}
}