#include <iostream>
//#include <unistd.h>
//#include <sys/types.h>
#include <stdio.h>
//#include <sys/wait.h>
#include <string.h>
#include <stdarg.h>
#include <vector>
using namespace std;
void Sort(int size, ...)
{
	int temp;
	va_list valist;
	int b,b1;
	vector<int> arr;
	va_start(valist,size);
	
	arr = va_arg(valist,vector<int>);
	//printf("%d\n",arr[0] );
	int chek=0;
	for(int i=1;i<size+1;i++)
	{
		int chek=0;
		for(int j=0;j<size-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
				chek=1;
			}
		}
		if(chek==0)
			break;
		
	}
	
	
	for(int i=0;i<size;i++)
		printf("%d, ", arr[i]);
	printf("\b\b");
	va_end(valist);
	
}

int main()
{
	cout<<"--------------------------Multi Parameter Sorting----------------------------\n";
	
	char A[100];
	printf("Enter the array set\n");
	scanf(" %[^\n]", A);
	
	printf("The Sorted Set of Array is \n");
	int m=strlen(A);
	//int k=0;
	int vac[20];
	int va=0;
	if(A[0]=='{' && A[m-1] == '}' && A[1] == '{' && A[m-2]=='}')  // {{19973, 0, 1},{....}}
	{
		printf("{");
		//fflush(stdout);
		for(int i=1;i<m-1;i++)
		{
			int z;
			vector<int> v;
			if(A[i]=='{')
			{
				for(z=i;z<m-1;z++)
					if(A[z]=='}')
						break;

				//k=0;

				for(int j=i+1;j<=z;j++)
				{
					if(A[j]!=' ' && A[j]!=',' && A[j]!='{' && A[j]!='}')
					{
						char temp[10];
						memset(&temp,0,sizeof(temp));
						for(int n=j;n<=z;n++)
						{
							if(A[n]==' ' || A[n]==',' || A[n]=='{' || A[n]=='}')
							{
								j=n;
								break;
							}
							temp[n-j] = A[n];
						}
						sscanf(temp, "%d", &vac[va]);
						va++;	
					}	
				}
			}
			else if(A[i]=='}')
			{
				for(int p=0;p<va;p++)
					v.push_back(vac[p]);
				printf("{");
				Sort(va,v);
				printf("}, ");
				
				va=0;
			}
			

		}
		printf("\b\b}\n");

	}
	else
	{
		printf("Wrong Input\n");
	
	}

	cout<<"-----------------------------------------------------------------------------\n";

	return 0;
}

