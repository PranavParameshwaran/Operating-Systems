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
		char name[100];
		printf("Enter the File Name\n");
		scanf("%s",name);
		write(fd1[1],name,strlen(name)+1);
		close(fd1[1]);
	}
	else
	{
		close(fd1[1]);
		char name[100];
		read(fd1[0],name,100);
		FILE *fp;
		fp  = fopen(name,"r");
		close(fd1[0]);
		int characters, words, lines;
		char ch;
		characters = words = lines = 0;
	    while((ch = fgetc(fp)) != EOF)
	    {
	        characters++;

	        if (ch == '\n' || ch == '\0')
	            lines++;

	        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
	            words++;
	    }

	    /* Increment words and lines for last word */
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
		    	case 4: fclose(fp);
		    			exit(1);
		    	default: printf("Enter proper Number\n" );
		    			break;
		    }
		}
	    fclose(fp);
	}
	return 0;
}