#include<iostream>
#include<stdio.h>
#include<cstdlib>
using namespace std;

class Sort{
	public:
		int inputi[200];
		float inputf[200];
		char inputc[200];
		int outputi[200];
		float outputf[200];
		char outputc[200];

		int n;
		// ---------------
		/*
		void Read();
		void Refresh();
		*/
		// ---------------
		void BSort(int x[]);
		void BSort(float x[]);
		void BSort(char x[]);
		// ---------------
		void ISort(int x[]);
		void ISort(float x[]);
		void ISort(char x[]);
		// ---------------
		void SSort(int x[]);
		void SSort(float x[]);
		void SSort(char x[]);
		// ---------------
		void print(char type);
};
// ------------------------------------------------
/*
void Sort::Read(){
	cout<<"Enter the array: ";
	for(int i=0;i<n;i++){
		cin>>x[i];
		//x[i]=rand()%100;
		xcopy[i]=x[i];
	}
}

void Sort::Refresh(){
	for(int i=0;i<n;i++){
		x[i]=xcopy[i];
	}
}
*/
// ------------------------------------------------
void Sort::BSort(int x[]){
	for(int i=0;i<n;i++) inputi[i] = x[i];

	for(int i=1;i<n+1;i++){
		int tcheck=0;
		for(int j=0;j<n-i;j++){
			if(x[j]>x[j+1]){
				int temp=x[j];
				x[j]=x[j+1];
				x[j+1]=temp;
				tcheck=1;
			}
		}
		if(tcheck==0)break;
	}

	for(int i=0;i<n;i++) outputi[i] = x[i];
}
void Sort::BSort(float x[]){
	for(int i=0;i<n;i++) inputf[i] = x[i];

	for(int i=1;i<n+1;i++){
		int tcheck=0;
		for(int j=0;j<n-i;j++){
			if(x[j]>x[j+1]){
				float temp=x[j];
				x[j]=x[j+1];
				x[j+1]=temp;
				tcheck=1;
			}
		}
		if(tcheck==0)break;
	}

	for(int i=0;i<n;i++) outputf[i] = x[i];
}
void Sort::BSort(char x[]){
	for(int i=0;i<n;i++) inputc[i] = x[i];

	for(int i=1;i<n+1;i++){
		int tcheck=0;
		for(int j=0;j<n-i;j++){
			if(x[j]>x[j+1]){
				char temp=x[j];
				x[j]=x[j+1];
				x[j+1]=temp;
				tcheck=1;
			}
		}
		if(tcheck==0)break;
	}

	for(int i=0;i<n;i++) outputc[i] = x[i];
}
// ------------------------------------------------
void Sort::ISort(int x[]){
	for(int i=0;i<n;i++) inputi[i] = x[i];

	for(int i=1;i<n;i++){
		for(int j=i;j>0;j--){
			if(x[j-1]>x[j]){
				int temp=x[j];
				x[j]=x[j-1];
				x[j-1]=temp;
			}
			else break;
		}
	}

	for(int i=0;i<n;i++) outputi[i] = x[i];
}
void Sort::ISort(float x[]){
	for(int i=0;i<n;i++) inputf[i] = x[i];

	for(int i=1;i<n;i++){
		for(int j=i;j>0;j--){
			if(x[j-1]>x[j]){
				float temp=x[j];
				x[j]=x[j-1];
				x[j-1]=temp;
			}
			else break;
		}
	}

	for(int i=0;i<n;i++) outputf[i] = x[i];
}
void Sort::ISort(char x[]){
	for(int i=0;i<n;i++) inputc[i] = x[i];

	for(int i=1;i<n;i++){
		for(int j=i;j>0;j--){
			if(x[j-1]>x[j]){
				char temp=x[j];
				x[j]=x[j-1];
				x[j-1]=temp;
			}
			else break;
		}
	}

	for(int i=0;i<n;i++) outputc[i] = x[i];
}
// ------------------------------------------------
void Sort::SSort(int x[]){
	for(int i=0;i<n;i++) inputi[i] = x[i];

	for(int i=0;i<n;i++){
		int max=x[0];
		int imax=0;
		for(int j=1;j<n-i;j++){
			if(x[j]>max){
				max=x[j];
				imax=j;
			}
		}
		int temp=x[n-i-1];
		x[n-i-1]=x[imax];
		x[imax]=temp;
	}

	for(int i=0;i<n;i++) outputi[i] = x[i];
}
void Sort::SSort(float x[]){
	for(int i=0;i<n;i++) inputf[i] = x[i];

	for(int i=0;i<n;i++){
		float max=x[0];
		int imax=0;
		for(int j=1;j<n-i;j++){
			if(x[j]>max){
				max=x[j];
				imax=j;
			}
		}
		float temp=x[n-i-1];
		x[n-i-1]=x[imax];
		x[imax]=temp;
	}

	for(int i=0;i<n;i++) outputf[i] = x[i];
}
void Sort::SSort(char x[]){
	for(int i=0;i<n;i++) inputc[i] = x[i];

	for(int i=0;i<n;i++){
		char max=x[0];
		int imax=0;
		for(int j=1;j<n-i;j++){
			if(x[j]>max){
				max=x[j];
				imax=j;
			}
		}
		char temp=x[n-i-1];
		x[n-i-1]=x[imax];
		x[imax]=temp;
	}

	for(int i=0;i<n;i++) outputc[i] = x[i];
}
// ------------------------------------------------
void Sort::print(char type){
	if(type == 'i')
	{
		cout<<"The values in old array are: 	";
		for(int i=0;i<n;i++){
			cout<<inputi[i]<<" ";
		}
		cout<<"\n";
		cout<<"The values in sorted array are:	";
		for(int j=0;j<n;j++){
			cout<<outputi[j]<<" ";
		}
		cout<<"\n";
	}
	else if(type == 'f')
	{
		cout<<"The values in old array are: 	";
		for(int i=0;i<n;i++){
			cout<<inputf[i]<<" ";
		}
		cout<<"\n";
		cout<<"The values in sorted array are:	";
		for(int j=0;j<n;j++){
			cout<<outputf[j]<<" ";
		}
		cout<<"\n";
	}
	else if(type == 'c')
	{
		cout<<"The values in old array are: 	";
		for(int i=0;i<n;i++){
			cout<<inputc[i]<<" ";
		}
		cout<<"\n";
		cout<<"The values in sorted array are:	";
		for(int j=0;j<n;j++){
			cout<<outputc[j]<<" ";
		}
		cout<<"\n";
	}
}
// ------------------------------------------------
int main(){
	cout<<"----------------------Sorting-----------------------\n";
	
	Sort s;

	int size = 0;
	cout<<"Enter the size of array: ";
	cin>>size;
	s.n = size;

	int xi[size];
	float xf[size];
	char xc[size];

	char type = 'i';
	cout<<"Enter the type of values (i - integer, f - float, c - char): ";
	cin>>type;

	if(type == 'i')
	{
		cout<<"Enter the array: ";
		for(int i=0;i<size;i++){
			cin>>xi[i];
		}
		s.BSort(xi);
		s.print('i');
	}
	else if(type == 'f')
	{
		cout<<"Enter the array: ";
		for(int i=0;i<size;i++){
			cin>>xf[i];
		}
		s.BSort(xf);
		s.print('f');
	}
	else if(type == 'c')
	{
		cout<<"Enter the array: ";
		for(int i=0;i<size;i++){
			cin>>xc[i];
		}
		s.BSort(xc);
		s.print('c');
	}
	cout<<"\n----------------------------------------------------------\n";
}







/*

Assignment Statement: Develop C / C++ application for the following:
(i) Sort an array of integers (or) characters (or) float values using Function Overloading.
(ii) Solve (i) using Function Templates feature.
(iii) Create a Generic (Stack or Queue or List - any one) Package with standard operations support using class templates feature.
(iv) Simulate the behavior or MV and CP command using Command Line Arguments in C.
(v) Use Variable Number of Arguments feature in C to setup a sort application that can sort multiple sized lists; (similar to python's support for sort.)
eg: {{9,8},{2,3,1}}  o/p shoud be :{{8,9},{1,2,3}}
note the input list can be varying number of sub arrays;

*/