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
	int fd2[2];
	pipe(fd1);
	pipe(fd2);
	pid_t p;
	p = fork();
	if(p==0)
	{
		close(fd1[0]);
		close(fd2[1]);
		char buf[100];
		printf("Enter Message for Parent (u are inside Child)\n");
		scanf(" %[^\n]",buf);
		
		char inp[100];
		write(fd1[1],buf,strlen(buf)+1);
		read(fd2[0],inp,100);
		printf("Parent Message for You (You = child) - %s\n",inp );
		close(fd1[1]);
		close(fd2[0]);
	}

	else
	{
		//sleep(2);
		printf("Message for Child(u are inside Parent)\n");
		char buf2[100];
		scanf(" %[^\n]",buf2);
		close(fd1[1]);
		close(fd2[0]);
		
		char inp2[100];
		read(fd1[0],inp2,100);
		write(fd2[1],buf2,strlen(buf2)+1);
		printf("Child Message for You (You = Parent) - %s\n", inp2);
		close(fd1[0]);
		close(fd2[1]);
		
	}
}