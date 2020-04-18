//
// Created by 鸿昊李 on 2020-03-09.
//

#include "Processes.h"
#include <algorithm>

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

int Processes::get_max_burst_time() {
    int max = 0;

    deque<Process>::iterator itr=this->processes.begin();
    for (; itr !=this->processes.end() ; ++itr) {
        if (itr->getBurstTime() > max) {
            max = itr->getBurstTime();
        }
    }

    return max;
}

void Processes::queue_sort_by_arrival_time() {
    std::sort(processes.begin(), processes.end(), sort_by_arrival);
}

int Processes::findRunning() {
    for (int i = 0; i < processes.size(); ++i) {
        if(processes[i].isRunning()){
            return i;
        }
    }

    return -1;
}


bool sort_by_arrival(Process p1, Process p2) {
    return p1.getArrivalTime() < p2.getArrivalTime();
}