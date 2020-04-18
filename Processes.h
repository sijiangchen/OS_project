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
    void replace(Process process);
    void queue_sort_by_arrival_time();

    //accessors
    Process& operator[](int i);
    Process& findRunning();
    int size();
    int get_max_burst_time();


    //FOR DEBUG USE
    void print();

private:
    deque<Process> processes;
};


bool sort_by_arrival(Process p1, Process p2);