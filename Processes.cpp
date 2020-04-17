//
// Created by 鸿昊李 on 2020-03-09.
//

#include "Processes.h"

Processes::Processes() {

}

void Processes::add(Process process) {
    this->processes.push_back(process);
}

void Processes::print() {
    deque<Process>::iterator itr=this->processes.begin();
    for (; itr !=this->processes.end() ; ++itr) {
        itr->print();
    }
}

Process& Processes::operator[](int i) {
    return this->processes[i];
}

int Processes::size() {
    return this->processes.size();
}

void Processes::remove(Process process) {
    deque<Process> temp;

    for (int i = 0; i < this->size(); ++i) {
        if(this->processes[i].getName()!=process.getName()){
            temp.push_back(this->processes[i]);
        }
    }
    this->processes.clear();
    for (int j = 0; j < temp.size(); ++j) {
        this->processes.push_back(temp[j]);
    }

}

void Processes::replace(Process process) {
    for (int i = 0; i < this->size(); ++i) {
        if(this->processes[i].getName()==process.getName()){
            this->processes[i]=process;
        }
    }
}
