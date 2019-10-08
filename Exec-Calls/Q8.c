#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
void red()
{
	printf("\033[1;31m");
	fflush(stdout);
}
void cyan()
{
	printf("\033[1;36m");
	fflush(stdout);
}
void reset()
{
	printf("\033[0m");
	fflush(stdout);
}
int main()
{
	// Q: What is the issue with using system command.
	//Different bw system and exec.
	//Can we execute bash commands, | in exec()
	FILE *fp;
	fp = fopen("history1.txt","a+");


	char *cmd = NULL;
	char *argv[64];
	char delim[] = " ";
	size_t len = 0;
	//char delim[]=" ";
	char *ptr;
	pid_t pid;
	pid_t pid2;
	int i,j,n;

	system("clear");
	while(1)
	{
		l1:
		pid2=fork();
		if(pid2==0)
		{
			red();
			printf("pranav@CMD:");
			reset();
			fflush(stdout);
			//char te[100] = "$PWD/#$HOME/'~'}";
			//execlp("pwd","pwd","|","tr","-d","'\n'",NULL);
			//system("pwd | tr -d \"\n\"");
			cyan();
			system("echo -n $(pwd) ");
			exit(0);
		}
		else
		{
			wait(NULL);
			//printf(" >> ");
		}
		reset();
		//getline(&cmd, &len, stdin);
		cmd=readline("$ ");
		fflush(stdin);
		//printf("%s\n",cmd);
		if(strcmp(cmd,"quit\0")==0)
		{
				fputs("quit\n",fp);
				exit(0);
		}
		else if(strcmp(cmd,"\n")==0)
			goto l1;

		else if(cmd[0]=='^')
		{
				fseek(fp,0,SEEK_END);
				int pos=ftell(fp);

				int count=0;
				int j=1;
				int hiscount=0;
				char buffer[1024];
				while(cmd[j]!='\0')
				{
					hiscount*=10;
					hiscount+=cmd[j]-'0';
					j++;
				}

				//printf("%d\n",hiscount );
				while(pos)
				{
					fseek(fp,--pos,SEEK_SET);
					if(fgetc(fp)=='\n')
					{
						//printf("%d\n",count );
						if(count++ == hiscount)
							{
								
								break;
							}
					}
				}
				while(fgets(buffer,1024,fp))
				{
					printf("%s",buffer);
				}
		}

		else
		{
			fprintf(fp,"%s\n",cmd);
			fflush(fp);
			i=0;
			ptr=strtok(cmd,delim);

			while(ptr != NULL)
			{
				//printf("%s ",ptr);
				//strcpy(argv[i],ptr);
				argv[i]=ptr;
				i++;
				ptr = strtok(NULL,delim);
			}

			argv[i]=NULL;
			
			pid=fork();
			if(pid==0)
			{


				execvp(argv[0],argv);
				printf("%s:Given CMD INVALID\n",argv[0]);
				//exit(0);
			}
			else if(pid>0)
			{
					wait(NULL);
			}
		}

	}


	fclose(fp);
	return 0;
}
