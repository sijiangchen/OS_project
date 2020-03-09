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

Process Processes::operator[](int i) {
    return this->processes[i];
}

int Processes::size() {
    return this->processes.size();
}
