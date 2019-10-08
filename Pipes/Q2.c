#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int main()
{

	// COPY STRING FROM PARENT TO CHILD
	int fd[2];
	pid_t pid;
	pipe(fd);
	pid = fork();
	char buf[100];
	char buf2[100];
	if(pid > 0)
	{
		close(fd[0]);
		//char buf[100];
		printf("Enter Some String (Parent)\n");
		scanf(" %[^\n]", buf); // Command for reading Space separated string using scanf
		int n=strlen(buf);
		printf("%d\n",n);
		buf[n]='\0';
		write(fd[1],buf,strlen(buf));
		//write(fd[1],"\n",1);
		close(fd[1]);
	}
	else if(pid==0)
	{
		close(fd[1]);
		int No;
		printf("Cpoied String is : ");
		read(fd[0],buf2,100);
		printf("%s",buf2);

		printf("\n");
		close(fd[0]);
	}

	/*
	// CONCATENATE STRING
	int fd1[2];
	int fd2[2];
	pid_t pid;
	pipe(fd1);
	pipe(fd2);
	pid = fork();
	char buf[100];
	char buf2[100];

	if(pid > 0)
	{
		char  concat[100];
		char space[1] = " ";
		close(fd1[0]);

		printf("Enter String 1\n");
		scanf(" %[^\n]", buf);
		write(fd1[1],buf,strlen(buf));
		write(fd1[1],space,1);
		close(fd1[1]);
		wait(NULL);
		close(fd2[1]);
		read(fd2[0],concat,100);
		printf("Concatenated String %s\n",concat);
		close(fd2[0]);
	}
	else
	{
		close(fd1[1]);
		char concat[100];
		read(fd1[0], concat,100);
		int k = strlen(concat);
		printf("Enter String(Child)\n");
		scanf(" %[^\n]", buf2);
		for(int i=0;i<strlen(buf2);i++)
			concat[k++] = buf2[i];
		concat[k] = '\0';

		close(fd1[0]);
		close(fd2[0]);
		write(fd2[1],concat,strlen(concat));
		close(fd2[1]);
		exit(0);
	}*/


	/*// COMPARISON
	int fd1[2];
	pid_t pid;
	pipe(fd1);
	pid = fork();
	char buf[100];

	if(pid == 0)
	{
		close(fd1[0]);

		printf("Enter String 1\n");
		scanf(" %[^\n]", buf);
		write(fd1[1],buf,strlen(buf));
		close(fd1[1]);

	}
	else
	{
		wait(NULL);
		close(fd1[1]);
		char cmp[100];
		char buf2[100];
		int flag=0;
		printf("Enter String(parent)\n");
		scanf(" %[^\n]", buf2);
		read(fd1[0], cmp,100);

		//fflush(stdin);

		int k = strlen(cmp);
		if(k != strlen(buf2))
		{
			printf("Strings Dont Match size dosent match\n");
			exit(0);
		}

		else
		{
			for(int i=0;i<strlen(buf2);i++)
			{
				if(cmp[i]!=buf2[i])
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
				printf("Strings Dont Match\n");
			else
				printf("Strings Match\n");
		}


		close(fd1[0]);
	}*/

	/*// CASE CONVERSION
	int fd1[2];
	pid_t pid;
	pipe(fd1);
	pid = fork();
	char buf[100];
	
	if(pid == 0)
	{
		close(fd1[0]);
	
		printf("Enter String Small Case(CHILD)\n");
		scanf(" %[^\n]", buf);
		write(fd1[1],buf,strlen(buf));
		close(fd1[1]);
	
	}
	else
	{
		wait(NULL);
		close(fd1[1]);
		//char cmp[100];
		char buf2[100];
		int flag=0;
		// printf("Enter String(parent)\n");
		// scanf(" %[^\n]", buf2);
		read(fd1[0], buf2,100);
	
		//fflush(stdin);
		for(int i=0;i<strlen(buf2);i++)
		{
			buf2[i] = toupper(buf2[i]);
		}
		printf("Parent - %s\n",buf2 );
	
		close(fd1[0]);
	}*/

	return 0;
}
