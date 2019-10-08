#include<stdio.h>
#include<cstdlib>
#include<iostream>
using namespace std;

//Structs
template <class T>
struct node
{
  	T x;
  	struct node<T> *nptr;
};

template <class T>
class Queue{
	public:
		struct node<T> *fptr = NULL;
		struct node<T> *rptr = NULL;

		void enqueue(T x);
		T dequeue();
		void print();
		int isFull();
		int isEmpty();
};
// ------------------------------------------------
template <class T>
void Queue<T>::enqueue(T x){
	struct node<T> *temp = new struct node<T>;
	if(temp==NULL) cout<<"No memory.\n";
	else {
		if(fptr==NULL){
			temp->x = x;
			fptr = temp;
			rptr = temp;
			rptr->nptr = NULL;
		}
		else {
			temp->x = x;
			rptr->nptr = temp;
			rptr = temp;
			rptr->nptr = NULL;
		}
	}
}
// ------------------------------------------------
template <class T>
T Queue<T>::dequeue(){
	T t=0;
	t=fptr->x;
	if(fptr->nptr==NULL){
		fptr=NULL;
		rptr=NULL;
	}
	else {
		fptr=fptr->nptr;
	}
	return t;
}
// ------------------------------------------------
template <class T>
int Queue<T>::isFull(){
	if(new struct node<T> == NULL)return 1;
	else return 0;
}
// ------------------------------------------------
template <class T>
int Queue<T>::isEmpty(){
	if(fptr==NULL)return 1;
	else return 0;
}
// ------------------------------------------------
template <class T>
void Queue<T>::print(){
	if(fptr==NULL){
		cout<<"Queue is Empty.\n";
	}
	else {
		cout<<"\nElements of queue are,\n";
		struct node<T> *tptr = fptr;
		int i=1;
		for(;tptr!=NULL;tptr=tptr->nptr){
			cout<<"Node "<<i<<": "<<tptr->x<<"\n";
			i++;
		}
		cout<<"\n\n";
	}
}
// ------------------------------------------------

//Start


int main(){
	cout<<"--------------------------Queue using LL----------------------------\n";

	char type = 'i';
	cout<<"Enter the type of values (i - integer, f - float, c - char): ";
	cin>>type;

	Queue <int>qi;
	Queue <float>qf;
	Queue <char>qc;

	int tempor=1;
	while(tempor>0){
  		cout<<"What do you want do?\nEnqueue		-	1\nDequeue		-	2\nCheck if Full		-	3\nCheck if Empty		-	4\nExit			-	0\nEnter Option: ";
		cin>>tempor;
		
		if(tempor==1){
  			//Enqueue
  			cout<<"-------Enqueue--------\n";
			cout<<"Enter value: ";
			if(type == 'i')
			{
				int inp;
				cin>>inp;
				qi.enqueue(inp);
				qi.print();
			}
			else if(type == 'f')
			{
				float inp;
				cin>>inp;
				qf.enqueue(inp);
				qf.print();
			}
			else if(type == 'c')
			{
				char inp;
				cin>>inp;
				qc.enqueue(inp);
				qc.print();
			}
  		}
  		
  		if(tempor==2){
			//Dequeue
			
				if(type == 'i')
				{
					if(qi.isEmpty()==0){
						int v = qi.dequeue();	
						cout<<"Dequeued value is "<<v<<".\n";
					}
					else cout<<"Cannot dequeue as queue is empty.\n";
					qi.print();
				}
				else if(type == 'f')
				{
					if(qf.isEmpty()==0){
						float v = qf.dequeue();	
						cout<<"Dequeued value is "<<v<<".\n";
					}
					else cout<<"Cannot dequeue as queue is empty.\n";
					qf.print();
				}
				else if(type == 'c')
				{
					if(qc.isEmpty()==0){
						char v = qc.dequeue();	
						cout<<"Dequeued value is "<<v<<".\n";
					}
					else cout<<"Cannot dequeue as queue is empty.\n";
					qc.print();
				}
		}
	
		if(tempor==3){
			//IsFull
			int fl = 0;
			if(type == 'i')
			{
				fl = qi.isFull();
			}
			else if(type == 'f')
			{
				fl = qf.isFull();
			}
			else if(type == 'c')
			{
				fl = qc.isFull();
			}

			if(fl==1)cout<<"\nThe queue is Full.\n\n";
			else if(fl==0)cout<<"\nThe queue is not Full.\n\n";
		}
	
		if(tempor==4){
			//IsEmpty
			int fl2 = 0;
			if(type == 'i')
			{
				fl2 = qi.isEmpty();
			}
			else if(type == 'f')
			{
				fl2 = qf.isEmpty();
			}
			else if(type == 'c')
			{
				fl2 = qc.isEmpty();
			}
			if(fl2==1)cout<<"\nThe queue is Empty.\n\n";
			if(fl2==0)cout<<"\nThe queue is not Empty.\n\n";
		}
			
		cout<<"-------------------------------------\n\n";
	}
  	return 0;
}


