//
// Created by 鸿昊李 on 2020-03-09.
//
#include <string>
#include <iostream>
#include "Process.h"
using namespace std;
Process::Process() {
    name[0]='\0';
    name[1]='\0';
    is_finished=false;
    numBurst=0;
}

Process::Process(char n,int time,int number) {
    this->name[0]=n;
    this->name[1]='\0';
    this->numBurst=number;
    this->is_finished=false;
    this->arrivalTime=time;
}

void Process::addCPUTime(int i) {
    this->CPUTime.push_back(i);
}

void Process::addIOTime(int i) {
    this->IOtime.push_back(i);
}

void Process::print() {
    cout<<"my name is : "<<this->name<<endl;
    cout<<"CPu burst time : "<<this->numBurst<<endl;
    cout<<"Arrival time : "<<this->arrivalTime<<endl;
    list<int >::iterator itr1=this->CPUTime.begin();
    list<int >::iterator itr2=this->IOtime.begin();
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

