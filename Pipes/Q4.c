#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int main()
{
	/*
	// STRING REVERSAL
	int fd1[2];
	pipe(fd1);
	pid_t p;
	p = fork();
	if(p==0)
	{
		close(fd1[0]);
		char buf[100];
		printf("Enter the String (REVERSED WILL BE O/P\n");
		scanf("%s",buf);
		write(fd1[1],buf,strlen(buf)+1);
		close(fd1[1]);

	}

	else
	{
		wait(NULL);
		close(fd1[1]);
		char buf2[100];
		read(fd1[0], buf2,100);
		char temp;
		int siz = strlen(buf2);
		for(int i=0;i<(siz/2);i++)
		{
			temp = buf2[i];
			buf2[i] = buf2[siz-i-1];
			buf2[siz-i-1] = temp;
		}	
		printf("REVERSED O/P : %s\n", buf2);

		close(fd1[0]);

	}*/

	// PALINDROME CHECk
	int fd1[2];
	pipe(fd1);
	pid_t p;
	p = fork();
	if(p==0)
	{
		close(fd1[0]);
		char buf[100];
		printf("Enter the String(CHILD)\n");
		scanf("%s",buf);
		write(fd1[1],buf,strlen(buf)+1);
		close(fd1[1]);
	}
	else
	{
		wait(NULL);
		close(fd1[1]);
		char buf2[100];
		read(fd1[0], buf2,100);
		int siz = strlen(buf2);
		int flag=0;
		for(int i=0;i<(siz/2);i++)
		{
			if(buf2[i] != buf2[siz-i-1])
				flag=1;
		}
		if(flag==1)
			printf("NOT A PALINDROME\n");
		else
			printf("String is a PALINDROME\n");
	}



}