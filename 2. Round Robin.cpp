/*
Did by Wong Zi Xiang 1142701102
*/
#include <iostream>
#include <stdio.h>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    double waitingTime;
    double turnaroundTime;
    bool idleCheck;
    bool inQueue;
};

int main()
{
    int i,j,k,n;
    int Quantum;
    int currentTime = 0;
    int totalTime = 0;
    int firstProcess;
    int subtract;
    int processIndex = 1;

    int leftoverQuantum = 0;
    double totalWT = 0;
    double totalTT = 0;
    int totalBT = 0;
    cout << "Enter total number of process(3-10): ";
    cin  >> n;
    while(n < 3 || n > 10){
        if (n < 3){
            cout << "Minimum number of process is 3, please try again: ";
        }
        if (n > 10){
            cout << "Minimum number of process is 3, please try again: ";
        }
        cin >> n;
    }

    Process p[n];
    Process temp;

    cout <<"Enter burst time and arrival time for each process:\n";
    for( i=0; i<n; i++) {
        p[i].pid = i+1;
        cout << "P" << (i+1) << "\n";
        cout << "Burst Time: ";
        cin  >> p[i].burstTime;
        cout << "Arrival Time: ";
        cin  >> p[i].arrivalTime;
        if(p[i].arrivalTime == 0){ //If arrival time is 0, schedule will start with idle
            p[i].idleCheck = false;
        }
        if(p[i].arrivalTime > 0){ //If arrival time is not 0, schedule might start with idle
            p[i].idleCheck = true;
        }
        totalTime = totalTime + p[i].burstTime;
        totalBT = totalBT + p[i].burstTime;
        p[i].inQueue = false;
        cout << endl;
    }
    cout << "\nTime Quantum: ";
    cin  >> Quantum;
    int rounds;//Rounds
    //If have remainder, still count
    if(totalTime % Quantum != 0){
        rounds = totalTime/Quantum + 1;
    }
    else{
        rounds = totalTime/Quantum;
    }

    //If there are too many processes finish early, extra round will be needed
    for( i=0; i<n; i++) {
        if(p[i].burstTime > Quantum){
            if(p[i].burstTime % Quantum != 0){
                leftoverQuantum = leftoverQuantum + (p[i].burstTime % Quantum);
            }
        }
    }
    if(leftoverQuantum > Quantum){
    	rounds = rounds + 1;
    }

    //Array spaces allocated according to rounds
    int queueIndex[rounds];
    int execTime[rounds+1];
    int queueBurst[rounds];

    int processSize = (sizeof(p)/sizeof(p[0]));

    //Swapping process based on arrival time and then burst time
    for ( i = 0; i < processSize; i++){
         j = i + 1;
        for (; j <= processSize; j++){
            if(p[j].arrivalTime < p[i].arrivalTime){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            if(p[j].arrivalTime == p[i].arrivalTime){
            	if(p[j].burstTime < p[i].burstTime){
            		temp = p[i];
            		p[i] = p[j];
            		p[j] = temp;
            	}
           	}
        }
    }

    queueIndex[0] = p[0].pid;
    queueBurst[0] = p[0].burstTime;
    execTime[0] = 0;
    firstProcess = p[0].arrivalTime;
    totalTime = totalTime + firstProcess;

    int queueCount = 0; //Current process's queue number
    int cutQueue = queueCount;//Is used when there are process needed to be put back into queue

    for(currentTime = firstProcess; currentTime < totalTime; queueCount++){

        //If none of the process arrives at 0, execTime[0] is 0, execTime[1] is set as the start point
       	if(firstProcess != 0){
            execTime[queueCount + 1] = currentTime;
       	}
       	//If there is process arrives at 0, execTime[0] is set as start point
       	if(firstProcess == 0){
            execTime[queueCount] = currentTime;
       	}

       	//If process's burst time is less than quantum time, subtract = current process's burst time
        if(queueBurst[queueCount] < Quantum){
            subtract = queueBurst[queueCount];
        }
        else{
            subtract = Quantum;
        }
        queueBurst[queueCount] = queueBurst[queueCount] - subtract;
        currentTime =  currentTime + subtract;


        //Check if any process arrived during the burst time and add them to queue
        for( j = processIndex; j < processSize; j++){
            if(p[j].arrivalTime <= currentTime && p[j].inQueue == false){
                queueBurst[cutQueue + 1] = p[j].burstTime;
                queueIndex[cutQueue + 1] = p[j].pid;
                p[j].inQueue = true;
                cutQueue++;
            }
            else if(p[j].arrivalTime > currentTime){
               	;
            }
        }
        int currentProcess; //Current process array number

        //To find out current process array number
        for( k = 0; k < n; k++){
            if(p[k].pid == queueIndex[queueCount]){
                currentProcess = k;
            }
        }

        //If current process haven't finish executing, put it back into queue
        if(queueBurst[queueCount] > 0){
            queueBurst[cutQueue + 1] = queueBurst[queueCount];
            queueIndex[cutQueue + 1] = queueIndex[queueCount];
            cutQueue++;
        }
         //Calculate waiting time and turnaround time for the process if it finishes running
        else if(queueBurst[queueCount] == 0){
            p[currentProcess].turnaroundTime = currentTime - p[currentProcess].arrivalTime;
            p[currentProcess].waitingTime = p[currentProcess].turnaroundTime - p[currentProcess].burstTime;
            totalTT += p[currentProcess].turnaroundTime;//Adding to total turnaround time
        }
    }

    //To readjust the array depending on whether there are idling or not
    if(firstProcess != 0){
        execTime[rounds] = currentTime - subtract;
        execTime[rounds + 1] = currentTime;
    }
    else{
        execTime[rounds] = currentTime;
    }

    //calculate total waiting time
    totalWT = totalTT - totalBT;

    //Sort to ascending PID
    for ( i = 0; i < processSize; i++){
         j = i + 1;
        for (; j < processSize; j++){
            if(p[j].pid < p[i].pid){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    //Table
    cout << "Time Quantum = " << Quantum << endl;
    cout << "+-----+--------------+------------+-----------------+--------------+" << endl
         << "| PID | Arrival Time | Burst Time | Turnaround Time | Waiting Time |" << endl
         << "+-----+--------------+------------+-----------------+--------------+" << endl;

    for( i=0; i<n; i++) {
        printf("| %2d  |      %2d      |     %2d     |       %2.0f        |      %2.0f      |\n"
               , p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].turnaroundTime, p[i].waitingTime );
        puts("+-----+--------------+------------+-----------------+--------------+");
    }
    double avgTT = totalTT/processSize;
    double avgWT = totalWT/processSize;
    cout << "Average Turnaround Time = " << totalTT << "/" << processSize << " = " << avgTT << "ms" << endl;
    cout << "Average Waiting Time = " << totalWT << "/" << processSize << " = " << avgWT << "ms" << endl;

    cout << "\n\nGantt Chart:" << endl;
    k = 0;
    for(i = 0; i < processSize; i++){
        if(p[i].idleCheck == false){
            break;
        }
        if(p[i].idleCheck == true){
            k++;
        }
    }
    if (k == processSize){
        cout << "+----";
    }
    for( i = 0; i < rounds; i++){
        cout << "+----";
   	}
   	cout << "+" << endl;
   	if (k == processSize){
        cout << "| XX ";
    }
    for( i = 0; i < rounds; i++){
   		cout << "| P" << queueIndex[i] << " ";
   	}
    cout << "|"<< endl;
    if (k == processSize){
        cout << "+----";
    }
    for( i = 0; i < rounds; i++){
        cout << "+----";
   	}
   	cout << "+" << endl;
    if(firstProcess != 0){
        for( i = 0; i <= rounds + 1; i++){
            if(execTime[i] >= 10){
                cout << execTime[i] << "   ";
            }
            else{
                cout << execTime[i] << "    ";
            }
        }
    }
    else{
        for( i = 0; i <= rounds; i++){
            if(execTime[i] >= 10){
                cout << execTime[i] << "   ";
            }
            else{
                cout << execTime[i] << "    ";
            }
        }
    }

    cin.ignore();
    cin.get();
    return 0;
}



