//
// Created by 鸿昊李 on 2020-03-09.
//

#include "Output.h"

Output::Output(string name) {
    this->name=name;
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

void Output::addCPUBurstTime(int time) {
    this->CPUBurstTime+=time;
}

void Output::addWaitTime(int time) {
    this->WaitTime+=time;
}

void Output::addTurnaroundTime(int time) {
    this->TurnaroundTime+=time;
}

void Output::addContextSwitch() {
    this->contextSwitch+=1;
}

void Output::addPreemption() {
    this->preemption+=1;
}

void Output::print() {
    cout<<"total cpu burst time: "<<this->CPUBurstTime<<endl;
    cout<<"total wait time: "<<this->WaitTime<<endl;
    cout<<"total Turnaround time: "<<this->TurnaroundTime<<endl;
    cout<<"total context switch: "<<this->contextSwitch<<endl;
    cout<<"total preemption: "<<this->preemption<<endl;
}
