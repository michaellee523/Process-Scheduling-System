#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    double waitingTime;
    double turnaroundTime;


};


int main()
{
    vector <int> sortVec;
    vector <int> tempVec;
    vector <int> displayVec;
    int numOfProcess;
    double tempTurnAroundTime;
    double tempWaitingTime;
    int totalTime = 0;
    double totalTurnAroundTime = 0;
    double totalWaitingTime = 0;
    double AverageTurnAroundTime = 0;
    double AverageWaitingTime = 0;
    int execTime = 0;
    int current;
    int temp;
    int tempArrivedTime;
    bool zero = false;

    cout << " Please enter total number of process (3-10) : ";
    cin >> numOfProcess;
    Process P[numOfProcess];
    int bTime[10];

    while (numOfProcess < 3 || numOfProcess > 10)
    {
        cout << endl;
        if (numOfProcess < 3)
            cout << " The minimum number of process is 3. Please try again! " << endl;
        else if (numOfProcess > 10)
            cout << " The maximum number of process is 10. Please try again! " << endl;
        cout << " Please enter total number of process (3-10) : ";
        cin >> numOfProcess;
    }

    int firstProcess = 9999;
    for (int i=0; i<numOfProcess; i++)
    {
        cout << endl;
        P[i].pid =i;
        cout << " P" << i << endl;
        cout << " Arrival Time  : ";
        cin >> P[i].arrivalTime;
        if (firstProcess > P[i].arrivalTime)
        {
            firstProcess = P[i].arrivalTime;
        }
        cout << " Burst Time    : ";
        cin >> P[i].burstTime;
        totalTime = totalTime + P[i].burstTime;
        cout << " Priority (1-6): ";
        cin >> P[i].priority;
        while (P[i].priority < 1 || P[i].priority > 6)
        {
            cout << " Priority is only allowed within 1 to 6! " << endl;
            cout << " Priority (1-6): ";
            cin >> P[i].priority;
        }
    }
    for (int i=0; i<numOfProcess; i++)
    {
        if (P[i].arrivalTime == 0)
        {
            zero = true;
        }
    }


    for(int i = 0; i<numOfProcess; i++)
    {
        bTime[i] = P[i].burstTime;
    }

    for(int currentTime=firstProcess; currentTime<totalTime+firstProcess; currentTime++)
    {
        for(int k=0; k<numOfProcess; k++)
        {
            tempArrivedTime = P[k].arrivalTime;
            if(tempArrivedTime == currentTime)
            {
                sortVec.push_back(k);
            }
        }
        for(int x = 0; x<sortVec.size(); x++)
        {
            current = x;
            for(int y = x+1; y<sortVec.size(); y++)
            {
                if(P[sortVec[y]].priority < P[sortVec[current]].priority)
                {
                    current=y;
                }
                else if (P[sortVec[y]].priority == P[sortVec[current]].priority)
                {
                    if(P[sortVec[y]].arrivalTime < P[sortVec[current]].arrivalTime)
                    {
                        current=y;
                    }
                }
            }
           temp=sortVec[x];
           sortVec[x]=sortVec[current];
           sortVec[current]=temp;
        }

        bTime[sortVec[0]] = bTime[sortVec[0]] - 1;
        displayVec.push_back(sortVec[0]);

        if (bTime[sortVec[0]] == 0)
        {
            tempTurnAroundTime = currentTime + 1 - P[sortVec[0]].arrivalTime;
            P[sortVec[0]].turnaroundTime = tempTurnAroundTime;
            tempWaitingTime = P[sortVec[0]].turnaroundTime - P[sortVec[0]].burstTime;
            P[sortVec[0]].waitingTime = tempWaitingTime;
            sortVec.erase(sortVec.begin());
        }
    }


    //Print table
    cout << endl;
    cout << " +-----+--------------+------------+------------+-----------------+--------------+" << endl
         << " | PID | Arrival Time | Burst Time |  Priority  | Turnaround Time | Waiting Time |" << endl
         << " +-----+--------------+------------+------------+-----------------+--------------+" << endl;

    for(int i=0; i<numOfProcess; i++)
    {
        printf(" | %2d  |      %2d      |     %2d     |     %2d     |       %2.0f        |      %2.0f      |\n"
               , P[i].pid, P[i].arrivalTime, P[i].burstTime, P[i].priority, P[i].turnaroundTime, P[i].waitingTime );
        puts(" +-----+--------------+------------+------------+-----------------+--------------+");
    }
    cout << endl;
    for (int i=0; i<numOfProcess; i++)
    {
        totalTurnAroundTime = totalTurnAroundTime + P[i].turnaroundTime;
        totalWaitingTime = totalWaitingTime + P[i].waitingTime;
    }

    AverageTurnAroundTime = (double)totalTurnAroundTime/numOfProcess;
    AverageWaitingTime = (double)totalWaitingTime/numOfProcess;
    cout << " Total Turnaround Time     = " << totalTurnAroundTime << endl;
    cout << " Total Waiting Time        = " << totalWaitingTime << endl << endl;
    cout << " Average Turnaround Time   = " << AverageTurnAroundTime << endl;
    cout << " Average Waiting Time      = " << AverageWaitingTime << endl << endl;



    //Print Gantt Chart
    cout << " ";
    if (zero == false)
    {
       cout << "+------";
    }
    for (int x=0; x<displayVec.size(); x++)
    {

        if (x!=displayVec.size()-1)
        {
            if (displayVec[x] != displayVec[x+1])
            {
                cout << "+------";
            }
        }
        else
            cout << "+------";
    }
    cout << "+" << endl << " ";
    if (zero == false)
    {
        cout << "|  XX" << "  ";
    }
    for (int x=0; x<displayVec.size(); x++)
    {
        if (x!=displayVec.size()-1)
        {
            if (displayVec[x] != displayVec[x+1])
            {
            cout << "|  P" << displayVec[x] << "  ";
            }
        }
        else
            cout << "|  P" << displayVec[x] << "  ";
    }
    cout << "|" << endl << " ";
    if (zero == false)
    {
        cout << "+------";
    }
    for (int x=0; x<displayVec.size(); x++)
    {
        if (x!=displayVec.size()-1)
        {
            if (displayVec[x] != displayVec[x+1])
            {
                cout << "+------";
            }
        }
        else
            cout << "+------";
    }
    cout << "+" << endl << " ";
    if (zero == false)
    {
        cout << "0" << "      ";
        execTime = firstProcess;

    }
    cout << execTime;
    for (int x=0; x<displayVec.size(); x++)
    {
        if (x!=displayVec.size()-1)
        {
            if (displayVec[x] != displayVec[x+1])
            {
                execTime++;
                if (execTime >=10)
                    cout << "     " << execTime;
                else
                    cout << "      " << execTime;
            }
            else if (displayVec[x] == displayVec[x+1])
            {
                execTime++;
            }
        }
        else
        {
            execTime++;
            if (execTime >=10)
                    cout << "     " << execTime;
                else
                    cout << "      " << execTime;
        }
    }

}
