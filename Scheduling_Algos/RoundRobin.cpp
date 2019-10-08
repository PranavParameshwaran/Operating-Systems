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

int CPUTime=0;
int funcat(int i)
{
	//int pid = i;
	int at;
	//int bt;

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
	
	
	//cout<<crtime<<endl;
	
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
	int CT;
	int TAT;
	int WT;
	int RT;
	int chk;
};

struct Queue
{
	int RQueue[100];
	int head;
	int tail;
};

bool SortAT(MODE m1, MODE m2)
{
	return (m1.AT < m2.AT);
}
bool SortPID(MODE m1, MODE m2)
{
	return (m1.PID < m2.PID);
}
class RR
{
	int nfil;		//Total no. of PIDs
	MODE m[100];
	Queue Q;
	int TQ;
	
	public:
		void ProcArrived();
		void FullWork();
		int Search(int v);
		
};
void RR::ProcArrived()
{
	for(int i=0;i<nfil;i++)
			{
				if(m[i].AT<=CPUTime && m[i].RT!=0 && m[i].chk==0)
				{
					
					//cout<<"TAIL_lop: "<<Q.tail<<endl;
					Q.tail++;
					Q.RQueue[Q.tail] = m[i].PID;
					
					m[i].chk=1;
				}
			}
}

void RR::FullWork()
{
	Q.head = -1;
	Q.tail = -1;
	
	cout<<"Enter the No. Files\n";
	cin>>nfil;
	cout<<"Enter the Time Quanta\n";
	cin>>TQ;
	cout<<"Enter the Process ID\n";
	for(int i=0;i<nfil;i++)
	{
		m[i].PID = i+1;
		m[i].chk=0;
	}
	//****** Getting Input*******
	
	cout<<"Enter the arrival time for the files\n";
	for(int i=0;i<nfil;i++)
	{
		m[i].AT = funcat(i);
		//cin>>m[i].AT;
	}

	//******** Getting BT of File****************
	cout<<"Enter the Burst time for the files\n";
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
		m[i].RT = m[i].BT;
		
	}
	sort(m,m+nfil,SortAT);

	//****** COMPUTATION*******

	int cpid=0;		//Completed PIDs
	int indexa;
	CPUTime = m[0].AT;
	int k=0;
	int temp;
	Q.head++;
	Q.tail++;
	while(cpid<nfil)
	{
		

		if(k==0)
		{
			Q.RQueue[Q.tail] = m[k].PID;
			m[k].chk=1;
			if(m[k].RT > TQ)
			{
				m[k].RT = m[k].RT - TQ;
				CPUTime+= TQ;
				ProcArrived();
				m[k].chk=0;
				Q.head++;
				Q.tail++;
				Q.RQueue[Q.tail]=m[k].PID;
				m[k].chk=1;
				
			}
			else if(m[k].RT <= TQ)
			{
				CPUTime+= m[k].RT;
				m[k].RT = 0;
				m[k].CT = CPUTime;
				cpid++;
				ProcArrived();
				m[k].chk=0;
				Q.head++;
			}
			
			k++;
		}
		
		else
		{
			temp = Search(Q.RQueue[Q.head]);
			if(m[temp].RT > TQ)
			{
				m[temp].RT = m[temp].RT - TQ;
				CPUTime+= TQ;
				ProcArrived();
				m[temp].chk=0;
				Q.head++;

				Q.tail++;
				Q.RQueue[Q.tail] = m[temp].PID;
				
				m[temp].chk=1;


			}
			else
			{
				
				CPUTime+= m[temp].RT;
				m[temp].RT = 0;
				m[temp].CT = CPUTime;
				cpid++;
				ProcArrived();
				m[temp].chk=0;
				Q.head++;
			}

			if(Q.head==Q.tail+1)
			{
				Q.tail=-1;
				Q.head=0;
				indexa=-1;
				for(int i=0;i<nfil;i++)
				{
					if(m[i].AT>CPUTime && m[i].RT!=0 && m[i].chk==0)
					{
						if(m[i].AT < m[indexa].AT || indexa == -1)
						{
							indexa = i;
						}
					}
				}
				CPUTime = m[indexa].AT;
				ProcArrived();

			}

		}		
	}
	
	sort(m,m+nfil,SortPID);
	for(int i=0;i<nfil;i++)
	{
		m[i].TAT=m[i].CT-m[i].AT;
		m[i].WT=m[i].TAT-m[i].BT;
	}
	
	cout<<"PID\tAT\tBT\tCT\tTAT\tWT\tRT\tCHK\n";
	for(int i=0;i<nfil;i++)
	{
		cout<<m[i].PID<<"\t"<<m[i].AT<<"\t"<<m[i].BT<<"\t"<<m[i].CT<<"\t"<<m[i].TAT<<"\t"<<m[i].WT<<"\t"<<m[i].RT<<"\t"<<m[i].chk<<endl;
	}

}

int RR::Search(int v)
{
	for(int i=0;i<nfil;i++)
		if(v == m[i].PID)
			return i;
}

int main()
{
	RR r;
	r.FullWork();
	return 0;
}
