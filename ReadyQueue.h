#include <iostream>
#include <string>
#include "line.h"
#include <deque>
#ifndef PROCESS_H
#define PROCESS_H
#include "Process.h"
#endif
using namespace std;

class ReadyQueue{

public:
    ReadyQueue();
    //modifiers
    void push_back(Process p);
    void push_front(Process p);
    void pop_front();
    void pop_back();
    void clear();
    void removeProcess(Process p);
    void sjf_insert(Process p);
    void swap(Process& p1,Process& p2);

    //accessors
    void print();
    string print_string();
    bool isEmpty();
    int size();
    Process& operator[](int i);
    Process getShortestJob();

    //debugger
    void debug();
private:
    deque<Process> readyQueue;
};