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
    if (this->readyQueue.size() == 0) {
        return true;
    }
    return false;
}

ReadyQueue::ReadyQueue() {

}

void ReadyQueue::clear() {
    this->readyQueue.clear();
}

Process &ReadyQueue::operator[](int i) {
    return this->readyQueue[i];
}

int ReadyQueue::size() {
    return this->readyQueue.size();
}

void ReadyQueue::print() {
    if (this->readyQueue.size() == 0) {
        cout << "[Q <empty>]" << endl;
    } else {
        cout << "[Q ";

        for (int i = 0; i < this->readyQueue.size(); ++i) {
            if (i + 1 == this->readyQueue.size()) {
                cout << this->readyQueue[i].getName() << "]" << endl;
            } else {
                cout << this->readyQueue[i].getName() << " ";

            }
        }

    }

}

Process ReadyQueue::getShortestJob() {
    Process ret;
    int min = 10000;
    for (int i = 0; i < this->readyQueue.size(); ++i) {
        if (i == 0 || readyQueue[i].getTau() < min) {
            ret = this->readyQueue[i];
            min = ret.getTau();
        }
    }
    return ret;
}

void ReadyQueue::removeProcess(Process p) {
    deque<Process> temp;

    for (int i = 0; i < this->readyQueue.size(); ++i) {
        if (this->readyQueue[i].getName() != p.getName()) {
            temp.push_back(this->readyQueue[i]);
        }
    }
    this->readyQueue.clear();
    for (int j = 0; j < temp.size(); ++j) {
        this->readyQueue.push_back(temp[j]);
    }

}



void ReadyQueue::sjf_insert(Process p) {
    deque<Process> temp;
    bool inserted=false;
    int i;
    if(readyQueue.size()==0){
        readyQueue.push_back(p);
        return;
    }
    for ( i = 0; i < readyQueue.size(); ++i) {
        if(!inserted){
            if(p.getTau()<readyQueue[i].getTau()){
                temp.push_back(p);
                temp.push_back(readyQueue[i]);
                break;
            }else if (p.getTau()==readyQueue[i].getTau()){
                if(p.getName()<readyQueue[i].getName()){
                    temp.push_back(p);
                    temp.push_back(readyQueue[i]);
                    break;
                }else{
                    temp.push_back(readyQueue[i]);
                    temp.push_back(p);
                }
            }else{
                temp.push_back(readyQueue[i]);
            }
        }else{
            break;
        }
    }
    for (int j = i+1; j < readyQueue.size(); ++j) {
        temp.push_back(readyQueue[j]);
    }
    readyQueue.clear();

}

void ReadyQueue::debug() {
    for (int i = 0; i < this->size(); ++i) {
        readyQueue[i].print();
    }

}

