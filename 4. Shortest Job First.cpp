#include <iostream>
#include <vector>
using namespace std;

class Process{

private:
    int name;   //contains process number
    int arrivalTime;
    int burstTime;
    int waitTime;
    int turnaroundTime;

public:
    int getName() { return name;  }

    int getAT() { return arrivalTime; }

    int getBT() { return burstTime; }

    int getWT() { return waitTime; }

    int getTAT() { return turnaroundTime; }

    void setName(int n) { name = n; }

    void setAT(int t) { arrivalTime = t; }

    void setBT(int t) { burstTime = t; }

    void setWT(int t) { waitTime = t; }

    void setTAT(int t) { turnaroundTime = t; }

};



void SJFP(Process *p, int numOfProcesses,int totalBT)
{
    int at = 0;
    vector<int> readyQueue;
    vector<int> executedSJF;
    int remainingTime[10];

    for(int i = 0; i < numOfProcesses; i++)
    {
        remainingTime[i] = p[i].getBT();        //initialize remaining time = burst time
    }

    for(int time = 0; time < totalBT; time++)
    {
        //store the arrived process into vector(ready queue)
        for(int i=0;i<numOfProcesses;i++)
        {
            at = p[i].getAT();
            if(at == time)
            {
                readyQueue.push_back(i);
            }
        }

        int pos, temp;
        //sort the vector(ready queue)
        for(unsigned int i = 0; i < readyQueue.size(); i++)
        {
            pos = i;
            for(unsigned int j = i+1; j < readyQueue.size(); j++)
            {
                if(remainingTime[readyQueue[j]]<remainingTime[readyQueue[pos]])
                {
                    pos=j;
                }
            }
            temp=readyQueue[i];
            readyQueue[i]=readyQueue[pos];
            readyQueue[pos]=temp;
        }

        remainingTime[readyQueue[0]]--;         //reduce the remaining burst time
        executedSJF.push_back(readyQueue[0]);   //execute the process

        if (remainingTime[readyQueue[0]] == 0)
        {
            int a = time+1 - p[readyQueue[0]].getAT();
            p[readyQueue[0]].setTAT(a);
            int b = p[readyQueue[0]].getTAT() - p[readyQueue[0]].getBT();
            p[readyQueue[0]].setWT(b);
            readyQueue.erase(readyQueue.begin());       //erase the process which finishes execution
        }
    }

    cout << "\nGantt Chart of SJF:" <<endl;
    for(int i = 0; i < executedSJF.size(); i++)
    {
        cout << "| P" << executedSJF[i] << " ";
    }
    cout << "|" <<endl;
    cout << "0" ;
    for (int i=0; i< executedSJF.size();i++)
    {
        if (i >= 10)
        {
            cout << "   "<< i+1;
        }
        else
        {
        cout << "    "<< i+1;
        }
    }

    int totalturnaroundTime = 0;
    int totalwaitingTime = 0;

    cout << "\nProcess Name\t Arrival Time\t Burst Time\t Turnaround Time\tWaiting Time" <<endl;
    for(int i=0;i<numOfProcesses;i++)
    {
        totalturnaroundTime += p[i].getTAT();
        totalwaitingTime += p[i].getWT();
        cout <<"\nP["<<p[i].getName()<<"]\t\t  " <<p[i].getAT()<<"\t\t    "<<p[i].getBT()<<"\t\t    "<<p[i].getTAT()<<"\t\t\t"<<p[i].getWT();
    }

    float avTotalaverageTime = (float)totalturnaroundTime/numOfProcesses;
    float avwaitingTime = (float)totalwaitingTime/numOfProcesses;

    cout << endl;
    cout << "Average Turnaround Time: " << avTotalaverageTime << endl;
    cout << "Average Waiting Time: " << avwaitingTime << endl;

}

int main()
{
    int numOfProcesses;
    do
    {
        cout<<"Enter Total Number of Process(3-10):";
        cin>>numOfProcesses;
    }while(numOfProcesses>10 || numOfProcesses <3);

    Process p[10];

     cout<<"\nEnter Burst Time and Arrival time: \n";
    int in = 0;
    int totalBT = 0;
    for(int i=0;i<numOfProcesses;i++)
    {
        cout<<"\nP["<<i<<"]\n";
        p[i].setName(i);
        cout<<"Arrival Time: ";
        cin>>in;
        p[i].setAT(in);
        cout<<"Burst Time: ";
        cin>>in;
        totalBT += in;
        p[i].setBT(in);
    }
    SJFP(p,numOfProcesses,totalBT);

}
