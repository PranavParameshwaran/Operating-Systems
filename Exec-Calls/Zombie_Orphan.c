#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	// ZOMBIE PROCESS. TO SHOW IT RUN THIS AcND OPEN A NEW TERMINAL AND RUN 'ps -e -o pid,ppid,stat,cmd' and go to the last part. You will see a.out and (defunct)-> zombie process still in table
	pid_t pid;
	pid = fork();
	if(pid>0)
		sleep(30);

	else
		exit(0);

	// ORPHAN PROCESS
	/*pid_t pid;
	pid = fork();
	if(pid>0)
		printf("Parent Executed\n");

	else
	{	sleep(10);
		//system("ps -e -o pid,ppid,cmd");
		printf("Child slept and became orphan\n");
	}*/

	return 0;
}