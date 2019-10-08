#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<sstream>
#include<algorithm>

using namespace std;

string GetStdoutFromCommand(string cmd) {

string data;
FILE * stream;
const int max_buffer = 256;
char buffer[max_buffer];
cmd.append(" 2>&1");

stream = popen(cmd.c_str(), "r");
if (stream) {
while (!feof(stream))
if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
pclose(stream);
}
return data;
}

int TextTOValue(string var)
{
	stringstream stlen(var);
	int val;
	stlen >> val;
	return val;
}

int StrToInt(char s[], int start, int end)
{
	int val = 0;
	for(int i = start; i <= end; i++)
	{
		if((int)s[i] >= 48 && (int)s[i] <= 57)
			val = (10*val) + (int)s[i] - 48;
	}
	return val;
}

int funcat(int i)
{
	int at;

	ostringstream s1;
	s1 << (i+1);
	string s2 = s1.str();
	string path = "stat test_" + s2 + ".txt";

	string command_stat = GetStdoutFromCommand(path);

	char crtime[18];

	for(int j=0;j<500-5;j++)
	{
		char check[6];
		check[0] = command_stat[j];
		check[1] = command_stat[j + 1];
		check[2] = command_stat[j + 2];
		check[3] = command_stat[j + 3];
		check[4] = command_stat[j + 4];
		check[5] = command_stat[j + 5];

		check[6] = '\0';

		if(strcmp(check, "Modify") == 0)
		{
			for(int k=j+19; k<j+37; k++)
			{
				crtime[k-j-19] = command_stat[k];
			}
			crtime[18] = '\0';
			break;
		}
	}
	
	int crtime_hr = StrToInt(crtime, 0, 1);
	int crtime_min = StrToInt(crtime, 3, 4);
	int crtime_sec = StrToInt(crtime, 6, 7);
	int crtime_sec_decimal = StrToInt(crtime, 9, 12);

	double creation_time = 3600 * crtime_hr + 60 * crtime_min + crtime_sec + (0.0001 * crtime_sec_decimal);

	at = (int)creation_time;
	cout<<at<<endl;

	return at;

}


struct MODE
{
	int PID;
	int AT;
	int BT;
	int Pr;
	int CT;
	int TAT;
	int WT;
	bool check;
};

bool SortAT(MODE m1, MODE m2)
{
	return (m1.AT < m2.AT);
}
bool SortPID(MODE m1, MODE m2)
{
	return (m1.PID < m2.PID);
}
class Priority
{
	int nfil;
	MODE m[100];
	int WQueue[100];
	
	public:
		void FullWork();
		
};

void Priority::FullWork()
{
	//****** Getting Input*******

	int temp[100];
	cout<<"Enter the number of FIles\n";
	cin>>nfil;
	for(int i=0;i<nfil;i++)
	{
		m[i].PID=i+1;
	}
	cout<<"Enter the arrival time for the files\n";
	for(int i=0;i<nfil;i++)
	{
		m[i].AT = funcat(i);
		//cin>>m[i].AT;
		m[i].check = 0;
	}

	//******** Getting BT of File****************
	
	cout<<"Enter the burst time for the files\n";
	for(int i=0;i<nfil;i++)
	{
		
		ostringstream s1;
		s1 << (i+1);
		string s2 = s1.str();
		string path = "wc -m test_" + s2 + ".txt";
		string ls = GetStdoutFromCommand(path);
		m[i].BT=TextTOValue(ls);
		cout<<TextTOValue(ls)<<endl;
		//cin>>m[i].BT;
		temp[i]=m[i].BT;
	}
	cout<<"Enter the Priority for the files\n";
	for(int i=0;i<nfil;i++)
	{
		cin>>m[i].Pr;
		
	}

	sort(m,m+nfil,SortAT);

	//****** COMPUTATION*******

	int index = -1;
	int CPUTime = m[0].AT;
	int cpid=0;
	int iter=0;
	//int i=m[0].AT;
	
	//while(i<1000)
	while(cpid<nfil)
	{
		if(iter==0)
		{
			if( (m[0].BT - (m[1].AT - m[0].AT)) < 0)
			{
				CPUTime+=m[0].BT;
				m[0].BT=0;
			}
			else
			{
				m[0].BT=m[0].BT - (m[1].AT - m[0].AT);
				CPUTime+=(m[1].AT - m[0].AT);
			}
			//cout<<m[0].BT<<" "<<CPUTime<<endl;
			if(m[0].BT==0) 
			{
				m[0].CT = CPUTime;
				cpid++;
				m[0].check=1;
			}
			iter++;
		}
		
		index = -1;
		for(int j=0;j<nfil;j++)
		{
			if(m[j].check ==0 && m[j].AT <= CPUTime)
			{	
				if(m[j].Pr > m[index].Pr || index == -1)
				{
					index = j;
				}
			}
			
		}
		CPUTime++;
		if(index!=-1)
		{
			m[index].BT--;
			if(m[index].BT==0) 
			{
				m[index].CT = CPUTime;
				cpid++;
				m[index].check=1;
			}
		}
	}
	sort(m,m+nfil,SortPID);

	for(int l=0;l<nfil;l++)
	{
		m[l].BT = temp[l];
		m[l].TAT=m[l].CT-m[l].AT;
		m[l].WT=m[l].TAT-m[l].BT;
	}

	//****** DISPLAY*******	

	cout<<"PID\tAT\tBT\tCT\tTAT\tWT\n";
	for(int i=0;i<nfil;i++)
		cout<<m[i].PID<<"\t"<<m[i].AT<<"\t"<<m[i].BT<<"\t"<<m[i].CT<<"\t"<<m[i].TAT<<"\t"<<m[i].WT<<"\t"<<m[i].check<<endl;

}

int main()
{
	int ch;

	while(1)
	{
		cout<<"Enter choice\n 1. Priority PRe-Emp\n2. Exit\n";
		cin>>ch;

		switch(ch)
		{
			case 1: Priority s;
					s.FullWork();
					break;

			case 2:exit(1);
					break;

			default: cout<<"Wrong Choice Enter Again\n";
					 break;
		}
	}

	return 0;
}
