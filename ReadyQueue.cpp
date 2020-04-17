//
// Created by 鸿昊李 on 2020-03-09.
//

#include "ReadyQueue.h"
#include <vector>
#include <algorithm>


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
    int min = 0;
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

bool mysort(Process p1, Process p2) {
    if(p1.getTau() < p2.getTau()){
        return true;
    }else if(p1.getTau()==p2.getTau()){
        if(p1.getName()<p2.getName()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void ReadyQueue::sjf_insert(Process p) {
    bool inserted=false;
    int i;
    if(readyQueue.size()==0){
        readyQueue.push_back(p);
        return;
    }else{
        std::vector<Process> temp;
        for (int j = 0; j < readyQueue.size(); ++j) {
            temp.push_back(readyQueue[j]);
        }
        temp.push_back(p);
        sort(temp.begin(),temp.end(),mysort);
        readyQueue.clear();
        for (int k = 0; k < temp.size(); ++k) {
            readyQueue.push_back(temp[k]);
        }

    }

}

void ReadyQueue::debug() {
    for (int i = 0; i < this->size(); ++i) {
        readyQueue[i].print();
    }

}

void ReadyQueue::swap(Process &p1, Process &p2) {
    Process t=p1;
    p1=p2;
    p2=t;
}

string ReadyQueue::print_string() {
    string ret;
    if (this->readyQueue.size() == 0) {
        ret+= "[Q <empty>]" ;
    } else {
        ret+= "[Q ";

        for (int i = 0; i < this->readyQueue.size(); ++i) {
            if (i + 1 == this->readyQueue.size()) {
                ret+=this->readyQueue[i].getName();
                ret+="]";
            } else {
                ret+=this->readyQueue[i].getName();
                ret+=" ";
            }
        }

    }
    return ret;
}

