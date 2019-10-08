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
	pipe(fd1);
	pid_t p;
	p = fork();
	if(p==0)
	{
		close(fd1[0]);
		dup2(fd1[1],1);
		execlp("ls","ls",NULL);

		//exit(1);
	}
	else
	{
		wait(NULL);
		close(fd1[1]);
		//execlp("wc","wc",NULL);

		// char buf[100];
		// char *arg[1000];
		//https://www.geeksforgeeks.org/implementing-lswc-command/
		// Number of Lines - Number of Files
		// Number of Words - Word Count of All Files
		// Number of Chars - Character Count
		// read(fd1[0],buf,100);
		int op;
		printf("Enter Choice\n1. Number of characters\n2. Number of Words\n3. Number of FILES/Lines(NO SPACE SEPARATED FILES)\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1: printf("Number of Characters\n");
					dup2(fd1[0],0);
					execlp("wc","wc","-m",NULL);
					break;
			case 2: printf("Number of Words\n");
					dup2(fd1[0],0);
					execlp("wc","wc","-w",NULL);
					break;
			case 3: printf("Number of Files\n");
					dup2(fd1[0],0);
					execlp("wc","wc","-l",NULL);
					break;
			default: printf("Wrong Choice\n");
					   break;
		}


	}

	return 0;
}
