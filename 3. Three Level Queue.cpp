//
//  main.cpp
//  OS 2
//
//  Created by Russell on 13/09/2016.
//  Copyright © 2016 Russell. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Process{
    int pid;
    int burstTime;
    int arrivalTime;
    int priority;
    int finishedTime;
    int runningTime;
public:
    Process(int pid, int burstTime, int arrivalTime, int priority, int finishedTime, int runningTime){
        this->pid=pid;
        this->burstTime=burstTime;
        this->arrivalTime=arrivalTime;
        this->priority=priority;
        this->finishedTime=finishedTime;
        this->runningTime=runningTime;
    }
    int getPid(){
        return pid;
    }
    int getBurstTime(){
        return burstTime;
    }
    int getArrivalTime(){
        return arrivalTime;
    }
    int getPriority(){
        return priority;
    }
    int getFinishedTime(){
        return finishedTime;
    }
    int getRuningTime(){
        return runningTime;
    }
    void burstTimeMinus(){
        burstTime = burstTime-1;
    }
    void setRuningTime(int runningTime){
        this->runningTime = runningTime;
    }
    void runningTimePlus(){
        runningTime++;
    }
};
class Graph {
    int pid;
    int time;
public:
    Graph(int pid, int time){
        this->pid=pid;
        this->time=time;
    }
    int getPid(){
        return pid;
    }
    int getTime(){
        return time;
    }
};

vector<Process> processes;
vector<Graph> graphArray;
int numOfProcess;

void getProcess();
bool comp(Process &, Process &);
void getProcess(){
    cout << "How many processes you want?" << endl;
    cout << "-> ";
    cin >> numOfProcess;
    int burstTime;
    int arrivalTime;
    int priority;
    for (int i=0;i<numOfProcess;i++){
        cout << "Process " << i << endl;
        cout << "Arrival time" << endl;
        cout << "-> ";
        cin >> arrivalTime;
        cout << "Burst time" << endl;
        cout << "-> ";
        cin >>burstTime;
        cout << "Priority" << endl;
        cout << "-> ";
        cin >>priority;
        processes.push_back(Process(i,burstTime,arrivalTime,priority,0,0));
    }
    sort(processes.begin(),processes.end(),comp);
}
bool comp(Process &a, Process &b){
    return a.getArrivalTime()<b.getArrivalTime();
}
bool notEnd(){
    for (int i=0;i<processes.size();i++){
        if (processes[i].getBurstTime()>0){
            return true;
        }
    }
    return false;
}
void listOutThreeQueue(){
    vector<Process> firstLevel;
    vector<Process> secondLevel;
    vector<Process> thirdLevel;
    for (int i=0; i<processes.size(); i++) {
        if (processes[i].getPriority()<=2) {
            firstLevel.push_back(processes[i]);
        }else if (processes[i].getPriority()<=4){
            secondLevel.push_back(processes[i]);
        }else{
            thirdLevel.push_back(processes[i]);
        }
    }
    cout << "First Level: ";
    for (int i=0;i<firstLevel.size();i++){
        cout << "P";
        cout << firstLevel[i].getPid()<<", ";
    }
    cout <<endl;
    cout << "Second Level: ";
    for (int i=0;i<secondLevel.size();i++){
        cout << "P";
        cout << secondLevel[i].getPid()<<", ";
    }
    cout <<endl;
    cout << "Third Level: ";
    for (int i=0;i<thirdLevel.size();i++){
        cout << "P";
        cout << thirdLevel[i].getPid()<<", ";
    }
    cout <<endl;
    
}

void draw(){
    for (int i=0; i<graphArray.size(); i++) {
        cout <<"+-----";
    }
    cout <<"+" << endl;
    for (int i=0; i<graphArray.size(); i++) {
        cout<<"| ";
        if (graphArray[i].getPid()==-1) {
            cout << " /  ";
        }else{
            cout <<" P"<<setw(2)<<graphArray[i].getPid();
        }
    }
    cout <<"|"<< endl;
    for (int i=0; i<graphArray.size(); i++) {
        cout <<"+-----";
    }
    cout <<"+" << endl;
    cout <<"0";
    for (int i=0; i<graphArray.size(); i++) {
        cout <<"    "<<setw(2)<<graphArray[i].getTime();
    }
    cout << endl;
}
void threeLevelQueue(){
    cout << "Three Level Queue: "<< endl << "First queue's quantum is 3"<< endl;
    listOutThreeQueue();
    Process *runingProcess = nullptr;
    Process *previousProcess = nullptr;
    vector<Process *> firstLevel;
    vector<Process *> secondLevel;
    vector<Process *> thirdLevel;
    int time=0;
    int firstLevelQueueRound=0;
    int count = 0;
    while(notEnd()){
        if (count<=numOfProcess){
            if (runingProcess==nullptr) {
                runingProcess = &processes[count];
                if (processes[count].getPriority()<=2) {
                    firstLevel.push_back(&processes[0]);
                }else if (processes[count].getPriority()<=4){
                    secondLevel.push_back(&processes[count]);
                }else{
                    thirdLevel.push_back(&processes[count]);
                }
                time = runingProcess->getArrivalTime();
                count++;
            }
            if (count <=numOfProcess) {
                while (processes[count].getArrivalTime()==time) {
                    if (processes[count].getPriority()<=2) {
                        firstLevel.push_back(&processes[0]);
                    }else if (processes[count].getPriority()<=4){
                        secondLevel.push_back(&processes[count]);
                    }else{
                        thirdLevel.push_back(&processes[count]);
                    }
                    count++;
                }
            }
           
        }
        if (runingProcess->getPriority()<=2) {
            if (runingProcess->getBurstTime()==0) {
                for (vector<Process*>::iterator it=firstLevel.begin(); it!=firstLevel.end();) {
                    if (*it == runingProcess) {
                        firstLevel.erase(it++);
                    }
                    else{
                        it++;
                    }
                }
//                firstLevel.erase(remove(firstLevel.begin(),firstLevel.end(),runingProcess),firstLevel.end());
                if (!firstLevel.empty()) {
                    firstLevelQueueRound = (firstLevelQueueRound+1) % firstLevel.size();
                    runingProcess = firstLevel[firstLevelQueueRound];
                }else{
                    if (!secondLevel.empty()) {
                        runingProcess = secondLevel[0];
                    }else{
                        if (!thirdLevel.empty()) {
                            runingProcess = thirdLevel[0];
                        }
                        else {
                            runingProcess = nullptr;
                        }
                    }
                }
            }else{
                if (runingProcess->getRuningTime()==3) {
                    firstLevelQueueRound = (firstLevelQueueRound+1) % firstLevel.size();
                    runingProcess->setRuningTime(0);
                    runingProcess = firstLevel[firstLevelQueueRound];
                }
            }
        }
        if (runingProcess->getPriority()<=4&&runingProcess->getPriority()>2){
            if (runingProcess->getBurstTime()==0) {
                for (vector<Process*>::iterator it=secondLevel.begin(); it!=secondLevel.end();) {
                    if (*it == runingProcess) {
                        secondLevel.erase(it++);
                    }
                    else{
                        it++;
                    }
                }
//                secondLevel.erase(remove(secondLevel.begin(),secondLevel.end(),runingProcess),secondLevel.end());
            }
            if (!firstLevel.empty()) {
                runingProcess = firstLevel[0];
            }else{
                if (!secondLevel.empty()) {
                    runingProcess = secondLevel[0];
                }
                else {
                    if (!thirdLevel.empty()) {
                        runingProcess = thirdLevel[0];
                    }else{
                        runingProcess = nullptr;
                    }
                }
            }
        }
        if (runingProcess->getPriority()<=6&&runingProcess->getPriority()>4){
            if (runingProcess->getBurstTime()==0) {
                for (vector<Process*>::iterator it=thirdLevel.begin(); it!=thirdLevel.end();) {
                    if (*it == runingProcess) {
                        thirdLevel.erase(it++);
                    }
                    else{
                        it++;
                    }
                }
//                thirdLevel.erase(remove(thirdLevel.begin(),thirdLevel.end(),runingProcess),thirdLevel.end());
            }
            if (!firstLevel.empty()) {
                runingProcess = firstLevel[0];
            }else{
                if (!secondLevel.empty()) {
                    runingProcess = secondLevel[0];
                }
                else {
                    if (!thirdLevel.empty()) {
                        runingProcess = thirdLevel[0];
                    }else{
                        runingProcess = nullptr;
                    }
                }
            }
        }
        
        if (runingProcess!=nullptr) {
            runingProcess->burstTimeMinus();
            runingProcess->runningTimePlus();
        }
        
        if (runingProcess!=previousProcess) {
            if (previousProcess==nullptr) {
                if (time>0) {
                    graphArray.push_back(Graph(-1,time));
                }
                
            }
            else{
                graphArray.push_back(Graph(previousProcess->getPid(),time));
            }
        }
        previousProcess=runingProcess;
        time++;
    }
    graphArray.push_back(Graph(runingProcess->getPid(),time));
    draw();
}

int main() {
    getProcess();
    threeLevelQueue();
    return 0;
}
