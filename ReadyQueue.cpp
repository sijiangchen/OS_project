//
// Created by 鸿昊李 on 2020-03-09.
//

#include "ReadyQueue.h"

void ReadyQueue::push_back(Process p) {
    this->readyQueue.push_back(p);
}

void ReadyQueue::push_front(Process p) {
    this->readyQueue.push_front(p);
}

void ReadyQueue::pop_front() {
    this->readyQueue.pop_front();
}

void ReadyQueue::pop_back() {
    this->readyQueue.pop_back();
}

bool ReadyQueue::isEmpty() {
    if(this->readyQueue.size()==0){
        return true;
    }
    return false;
}

ReadyQueue::ReadyQueue() {

}

void ReadyQueue::clear() {
    this->readyQueue.clear();
}

Process ReadyQueue::operator[](int i) {
    return this->readyQueue[i];
}

int ReadyQueue::size() {
    return this->readyQueue.size();
}

void ReadyQueue::print() {
    if(this->readyQueue.size()==0){
        cout<<"[Q <empty>]"<<endl;
    }else{
        cout<<"[Q ";

        for (int i = 0; i < this->readyQueue.size(); ++i) {
            if(i+1==this->readyQueue.size()){
                cout<<this->readyQueue[i].getName()<<"]"<<endl;
            }else{
                cout<<this->readyQueue[i].getName()<<" ";

            }
        }

    }

}

