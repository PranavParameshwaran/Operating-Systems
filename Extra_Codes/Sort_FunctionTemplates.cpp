#include<iostream>
#include<stdio.h>
#include<cstdlib>
using namespace std;

template <class T>
class Sort{
	public:
		int n;
		// ---------------
		/*
		void Read();
		void Refresh();
		*/
		// ---------------
		void BSort(T x[]);
		// ---------------
		void ISort(T x[]);
		// ---------------
		void SSort(T x[]);
		// ---------------
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
template <class T>
void Sort<T>::BSort(T x[]) {
	cout<<"The values in old array are: 	";
	for(int i=0;i<n;i++){
		cout<<x[i]<<" ";
	}
	cout<<"\n";

	for(int i=1;i<n+1;i++){
		int tcheck=0;
		for(int j=0;j<n-i;j++){
			if(x[j]>x[j+1]){
				T temp=x[j];
				x[j]=x[j+1];
				x[j+1]=temp;
				tcheck=1;
			}
		}
		if(tcheck==0)break;
	}

	cout<<"The values in sorted array are:	";
	for(int j=0;j<n;j++){
		cout<<x[j]<<" ";
	}
	cout<<"\n";
}
// ------------------------------------------------
template <class T>
void Sort<T>::ISort(T x[]) {
	cout<<"The values in old array are: 	";
	for(int i=0;i<n;i++){
		cout<<x[i]<<" ";
	}
	cout<<"\n";

	for(int i=1;i<n;i++){
		for(int j=i;j>0;j--){
			if(x[j-1]>x[j]){
				T temp=x[j];
				x[j]=x[j-1];
				x[j-1]=temp;
			}
			else break;
		}
	}

	cout<<"The values in sorted array are:	";
	for(int j=0;j<n;j++){
		cout<<x[j]<<" ";
	}
	cout<<"\n";
}
// ------------------------------------------------
template <class T>
void Sort<T>::SSort(T x[]) {
	cout<<"The values in old array are: 	";
	for(int i=0;i<n;i++){
		cout<<x[i]<<" ";
	}
	cout<<"\n";

	for(int i=0;i<n;i++){
		T max=x[0];
		int imax=0;
		for(int j=1;j<n-i;j++){
			if(x[j]>max){
				max=x[j];
				imax=j;
			}
		}
		T temp=x[n-i-1];
		x[n-i-1]=x[imax];
		x[imax]=temp;
	}

	cout<<"The values in sorted array are:	";
	for(int j=0;j<n;j++){
		cout<<x[j]<<" ";
	}
	cout<<"\n";
}
// ------------------------------------------------
// ------------------------------------------------
int main(){
	cout<<"----------------------Sorting-----------------------\n";

	char type = 'i';
	cout<<"Enter the type of values (i - integer, f - float, c - char): ";
	cin>>type;


	if(type == 'i')
	{
		Sort <int>s;

		int size = 0;
		cout<<"Enter the size of array: ";
		cin>>size;
		s.n = size;

		int xi[size];

		cout<<"Enter the array: ";
		for(int i=0;i<size;i++){
			cin>>xi[i];
		}
		s.BSort(xi);
	}
	else if(type == 'f')
	{
		Sort <float>s;

		int size = 0;
		cout<<"Enter the size of array: ";
		cin>>size;
		s.n = size;

		float xf[size];

		cout<<"Enter the array: ";
		for(int i=0;i<size;i++){
			cin>>xf[i];
		}
		s.BSort(xf);
	}
	else if(type == 'c')
	{
		Sort <char>s;

		int size = 0;
		cout<<"Enter the size of array: ";
		cin>>size;
		s.n = size;

		char xc[size];

		cout<<"Enter the array: ";
		for(int i=0;i<size;i++){
			cin>>xc[i];
		}
		s.BSort(xc);
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