#include <string>
#include <deque>
#ifndef PROCESS_H
#define PROCESS_H
#include "Process.h"
#endif
using namespace std;

class Processes{
public:
    Processes();

    //modifiers
    void add(Process process);
    void remove(Process process);

    //accessors
    Process& operator[](int i);
    int size();

    //FOR DEBUG USE
    void print();

private:
    deque<Process> processes;
};