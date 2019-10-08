#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int main()
{
	int fd[2];
	pipe(fd);
	pid_t p;
	p = fork();

	if(p==0)
	{
		close(fd[0]);
		char name[100];
		//char buf[100];
		printf("Enter the File Name\n");
		scanf("%s",name);
		FILE *fp;
		fp  = fopen(name,"r");

		fseek(fp, 0, SEEK_END);
		long fsize = ftell(fp);
		fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */

		char *buf = malloc(fsize + 1);
		fread(buf, 1, fsize, fp);
		fclose(fp);
		//printf("%s\n",buf );
		write(fd[1],buf,fsize);
		free(buf);
		//write(fd1[1],name,strlen(name)+1);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		char buf[100];
		/*read(fd1[0],name,100);
		FILE *fp;*/
		//fp  = fopen(name,"r");
		int NO;
		int characters, words, lines, count;
		characters = words = lines = 0;
		char ch;
		
		while((NO = read(fd[0],buf,100)) > 0)
		{

			char ch;
			count = 0;
		    while(count != NO)
		    {
		        ch = buf[count];
		        characters++;

		        if (ch == '\n' || ch == '\0')
		            lines++;

		        if (ch == ' ' || ch == '\n' || ch == '\0')
		            words++;
		        count++;
		    }

		    /* Increment words and lines for last word */
		}
		if (characters > 0)
		{
		    words++;
		    lines++;
		}
	    int op;
	    while(1)
	   	{
		    printf("Enter Choice\n1. Number of characters\n2. Number of Words\n3. Number of Lines\n4. Exit\n");
		    scanf("%d",&op);
		    switch(op)
		    {
		    	case 1: printf("characters - %d\n",characters );
		    			break;
		    	case 2: printf("Words - %d\n",words );
		    			break;
		    	case 3: printf("Lines - %d\n",lines );
		    			break;
		    	case 4: //fclose(fp);
		    			exit(1);
		    	default: printf("Enter proper Number\n" );
		    			break;
		    }
		}

		close(fd[0]);
	    //fclose(fp);
	}
	return 0;
}