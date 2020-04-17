//
// Created by 鸿昊李 on 2020-03-09.
//

#include "Output.h"

Output::Output(string name) {
  this->name=name;
      CPUBurstTime=0;
      WaitTime=0;
      TurnaroundTime=0;
      contextSwitch=0;
      preemption=0;

}

double Output::getCPUBurstTime() {
    return this->CPUBurstTime;
}

double Output::getWaitTime() {
    return this->WaitTime;
}

double Output::getTurnaroundTime() {
    return this->TurnaroundTime;
}

int Output::getContextSwitch() {
    return this->contextSwitch;
}

int Output::getPreemption() {
    return this->preemption;
}

void Output::addCPUBurstTime(double time) {
    this->CPUBurstTime+=time;
}

void Output::addWaitTime(double time) {
    this->WaitTime+=time;
}

void Output::addTurnaroundTime(double time) {
    this->TurnaroundTime+=time;
}

void Output::addContextSwitch() {
    this->contextSwitch+=1;
}

void Output::addPreemption() {
    this->preemption+=1;
}
/*
void Output::print() {
    cout<<"total cpu burst time: "<<this->CPUBurstTime<<endl;
    cout<<"total wait time: "<<this->WaitTime<<endl;
    cout<<"total Turnaround time: "<<this->TurnaroundTime<<endl;
    cout<<"total context switch: "<<this->contextSwitch<<endl;
    cout<<"total preemption: "<<this->preemption<<endl;
}
*/

ostream& Output::print(ostream& out_str) {
    out_str<<setiosflags(ios::fixed)<<setprecision(3);
    out_str<<"-- average CPU burst time: "<<this->CPUBurstTime/this->contextSwitch<<" ms"<<endl;
    out_str<<"-- average wait time: "<<this->WaitTime/this->contextSwitch<<" ms"<<endl;
    out_str<<"-- average turnaround time: "<<this->TurnaroundTime/this->contextSwitch<<" ms"<<endl;
    out_str<<"-- total number of context switches: "<<this->contextSwitch<<endl;
    out_str<<"-- total number of preemptions: "<<this->preemption<<endl;
    return out_str;
}

void Output::print() {
    cout<<"total cpu burst time: "<<this->CPUBurstTime<<endl;
    cout<<"total wait time: "<<this->WaitTime<<endl;
    cout<<"total Turnaround time: "<<this->TurnaroundTime<<endl;
    cout<<"total context switch: "<<this->contextSwitch<<endl;
    cout<<"total preemption: "<<this->preemption<<endl;
}
