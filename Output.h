#include <iostream>
#include <string>

using namespace std;

class Output {
    //output
public:
    Output(string name);

    //accessors
    double getCPUBurstTime();
    double getWaitTime();
    double getTurnaroundTime();
    int getContextSwitch();
    int getPreemption();
    //modifier
    void addCPUBurstTime(int time);
    void addWaitTime(int time);
    void addTurnaroundTime(int time);
    void addContextSwitch();
    void addPreemption();

    //debugger
    void print();

private:
    string name;
    double CPUBurstTime=0;
    double WaitTime=0;
    double TurnaroundTime=0;
    int contextSwitch=0;
    int preemption=0;


};