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
bool SortPr(MODE m1, MODE m2)
{
	return (m1.Pr > m2.Pr);
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

	cout<<"Enter the number of FIles\n";
	cin>>nfil;
	//cout<<"Enter the Process ID\n";
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
	cout<<"Enter the BT for the files\n";
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
	}
	cout<<"Enter the Priority for the files\n";
	for(int i=0;i<nfil;i++)
	{
		cin>>m[i].Pr;
		
	}

	sort(m,m+nfil,SortAT);
	//****** COMPUTATION*******

	m[0].CT=m[0].AT+m[0].BT;
	m[0].TAT=m[0].CT-m[0].AT;
	m[0].WT=m[0].TAT-m[0].BT;
	m[0].check = 1;
	
	//sort(m,m+nfil,SortPr);
	int prevIndex = 0;
	int min;
	int index = -1;

	
	checkagain:
	for(int i=1;i<nfil;i++)
	{
		
		//finding minimum burst time for next operation if CT>AT
		//Local = 
		if(m[i].check ==0 && m[i].AT <= m[prevIndex].CT)
		{
			index = -1;
			for(int j=0;j<nfil;j++)
			{
				if(m[j].check ==0 && m[j].AT <= m[prevIndex].CT)
				{	
					if(m[j].Pr > m[index].Pr || index == -1)
					{
						index = j;
					}
				}
				
			}
			cout<<"INDEX :"<<m[index].AT<<" "<<index<<endl; 
			if(index!=-1)
			{
				m[index].CT = m[prevIndex].CT + m[index].BT;
				m[index].TAT = m[index].CT - m[index].AT;
				m[index].WT = m[index].TAT - m[index].BT;
				m[index].check=1;

				prevIndex=index;
			}
		}
		else if(m[i].check ==0 && m[i].AT > m[prevIndex].CT)
		{
			m[i].CT = m[i].AT + m[i].BT;
			m[i].TAT = m[i].CT - m[i].AT;
			m[i].WT = m[i].TAT - m[i].BT;
			m[i].check=1;
			prevIndex = i;
		}

		
		
	}

	for(int l=0;l<nfil;l++)
	{
		if(m[l].check==0)
			goto checkagain;
	}


	sort(m,m+nfil,SortPID);
	
	//****** DISPLAY*******	

	cout<<"PID\tAT\tBT\tPr\tCT\tTAT\tWT\n";
	for(int i=0;i<nfil;i++)
		cout<<m[i].PID<<"\t"<<m[i].AT<<"\t"<<m[i].BT<<"\t"<<m[i].Pr<<"\t"<<m[i].CT<<"\t"<<m[i].TAT<<"\t"<<m[i].WT<<"\t"<<m[i].check<<endl;

}

int main()
{
	int ch;

	while(1)
	{
		cout<<"Enter choice\n 1. Priority\n2. Exit\n";
		cin>>ch;

		switch(ch)
		{
			case 1: Priority p;
					p.FullWork();
					break;

			case 2:exit(1);
					break;

			default: cout<<"Wrong Choice Enter Again\n";
					 break;
		}
	}

	return 0;
}
