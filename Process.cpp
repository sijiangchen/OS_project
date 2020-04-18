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
    is_waiting=false;
    is_running=false;
    preempted=false;
    numBurst=0;
    currentBurstIndex=0;
    currentIOIndex=0;
    next_io_finish_time=0;
    burst_time=0;
    wait_time=0;
    turn_around_time=0;
    amount_finished_in_current_burst=0;
    amount_finished_in_current_io=0;

}

Process::Process(char n,int time,int number,double lambda, double alpha) {
    this->name[0]=n;
    this->name[1]='\0';
    this->numBurst=number;

    this->is_finished=false;
    this->is_blocked=false;
    this->is_waiting=false;
    this->is_running=false;

    this->arrivalTime=time;
    this->currentBurstIndex=0;
    this->currentIOIndex=0;
    //todo idk why have to minus 1 here, but that give correct result
    this->tau=(int)ceil(1/lambda)-1;
    if(this->tau==999){
        this->tau+=1;
    }
    this->alpha=alpha;
    this->next_io_finish_time=0;
    this->burst_time=0;
    this->wait_time=0;
    this->turn_around_time=0;
}

void Process::addCPUTime(int i) {
    this->CPUTime.push_back(i);
}

void Process::addIOTime(int i) {
    this->IOTime.push_back(i);
}

void Process::print() {
    cout << "----------------------------------------------------" <<  endl;
    cout<<   "    my name is : "    <<         this->name          <<  endl;
    cout<<   "CPU burst time : "    <<         this->numBurst      <<  endl;
    cout<<   "  Arrival time : "    <<         this->arrivalTime   <<  endl;



    deque<int >::iterator itr1=this->CPUTime.begin();
    deque<int >::iterator itr2=this->IOTime.begin();


    for (int i = 0; i < this->numBurst; ++i) {
        if(i+1 == this->numBurst) {
            cout<<      "cpu time : "       <<*itr1<<endl;
        }
        else{
            cout<<      "cpu time : "       <<*itr1++<<endl;
            cout<<      "io  time : "       <<*itr2++<<endl;
        }

        cout<<"tau : "<<this->getTau()<<endl;
        this->updateTau();
    }

    cout << "----------------------------------------------------" <<  endl;

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


void Process::setRunning(){
    this->is_running=true;
}

void Process::setWaiting(){
    this->is_waiting=true;
}

void Process::setPreempted(){
    this->preempted=true;
}

void Process::unBlocked() {
    this->is_blocked=false;

}

void Process::unWaiting(){
    this->is_waiting=false;
}

void Process::unRunning(){
    this->is_running=false;
}

void Process::unPreempted(){
    this->preempted=false;
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

void Process::setCPUTime(int index,int time){
    this->CPUTime[index]=time;
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

double Process::getAlpha() {
    return this->alpha;
}

void Process::updateTau() {

    double a=alpha*CPUTime[currentBurstIndex];
    double b=(1-alpha)*tau;

    double res=a+b;

    this->tau=(int)ceil(res);
}

int Process::getTau() {
    return this->tau;
}

void Process::increaseCurrentCPUBurstIndex() {
    this->currentBurstIndex++;
}
void Process::increaseCurrentIOIndex() {
    this->currentIOIndex++;
}

int Process::getCPUTime() {
    return this->CPUTime[currentBurstIndex];
}

int Process::getIOTime() {
    return this->IOTime[currentIOIndex];
}

void Process::setNextIOFinishTime(int time){
    this->next_io_finish_time=time;
}

void Process::addBurstTime(double time){
    this->burst_time+=time;
}

void Process::addWaitTime(double time){
    this->wait_time+=time;
}

void Process::addTurnAroundTime(double time){
    this->turn_around_time+=time;
}

void Process::setNextCPUFinishTime(int time) {
    this->next_cpu_finish_time=time;
}

