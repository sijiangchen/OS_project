#include <iostream>
#include <string>
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

    //accessors
    void print();
    bool isEmpty();
    int size();
    Process& operator[](int i);
    Process& getShortestJob();

private:
    deque<Process> readyQueue;
};