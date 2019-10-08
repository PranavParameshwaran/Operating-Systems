#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>

int main(int argc, char const *argv[])
{
    if(argc!=3)
        printf("Argument Number Error: Expected 3, Got %d\n", argc);
    else
    {
    	FILE *fp1;
    	FILE *fp2;
    	fp1 = fopen(argv[1],"r");
    	fp2 = fopen(argv[2],"w+");
    	char charbuf;
        int iter=0;
        float faa;
    	while(!feof(fp1))
    	{
            charbuf=fgetc(fp1);
    		fputc(charbuf,fp2);
    	} 
    	fclose(fp1);
        fclose(fp2);
    }
    
    return 0;
}
