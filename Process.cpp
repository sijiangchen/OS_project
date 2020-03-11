//
// Created by 鸿昊李 on 2020-03-09.
//
#include <string>
#include <iostream>
#include <cmath>
#include "Process.h"
using namespace std;
Process::Process() {
    name[0]='\0';
    name[1]='\0';
    is_finished=false;
    is_blocked=false;
    numBurst=0;
    currentBurstIndex=0;
    currentIOIndex=0;
}

Process::Process(char n,int time,int number) {
    this->name[0]=n;
    this->name[1]='\0';
    this->numBurst=number;
    this->is_finished=false;
    this->is_blocked=false;
    this->arrivalTime=time;
    currentBurstIndex=0;
    currentIOIndex=0;
}

void Process::addCPUTime(int i) {
    this->CPUTime.push_back(i);
}

void Process::addIOTime(int i) {
    this->IOTime.push_back(i);
}

void Process::print() {
    cout<<"my name is : "<<this->name<<endl;
    cout<<"CPu burst time : "<<this->numBurst<<endl;
    cout<<"Arrival time : "<<this->arrivalTime<<endl;
    deque<int >::iterator itr1=this->CPUTime.begin();
    deque<int >::iterator itr2=this->IOTime.begin();
    for (int i = 0; i < this->numBurst; ++i) {
        if(i+1==this->numBurst){
            cout<<"cpu time : "<<*itr1<<endl;
        }else{
            cout<<"cpu time : "<<*itr1++<<endl;
            cout<<"io  time : "<<*itr2++<<endl;
        }
    }

}

bool Process::isFinished() {
    return this->is_finished;
}

void Process::setFinished() {
    this->is_finished=true;
}

void Process::setBlocked() {
    this->is_blocked=true;
}

void Process::unblocked() {
    this->is_blocked=false;

}

int Process::getCurrentBurstIndex() {
    return this->currentBurstIndex;
}

int Process::getCurrentIOIndex() {
    return this->currentIOIndex;
}

bool Process::isBlocked() {
    return this->is_blocked;
}

int Process::getCPUTime(int index) {
    return this->CPUTime[index];
}

int Process::getIOTime(int index) {
    return this->IOTime[index];
}

void Process::updateCPUTime(int index,int time) {
    this->CPUTime[index]+=time;
}

void Process::updateIOTime(int index,int time) {
    this->IOTime[index]+=time;
}

string Process::getName() {
    return this->name;
}

void Process::setAlpha(double a) {
    this->alpha=(int)ceil(1/a);
}

int Process::getArrivalTime() {
    return this->arrivalTime;
}

int Process::getNumBurst() {
    return this->numBurst;
}

int Process::getAlpha() {
    return this->alpha;
}

