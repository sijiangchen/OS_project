#include <iostream>

#include <string>
#include <deque>
#include "Process.h"
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

    //accessors
    bool isEmpty();

private:
    deque<Process> readyQueue;
};