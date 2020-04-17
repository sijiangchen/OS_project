#include <iostream>
#include <string>
#include <iomanip>

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
    void changeName(string new_name) { name = new_name; }

    //debugger
    //void print();
    
    //output the summaries
    ostream& print(ostream& out_str);
    
private:
    string name;
    double CPUBurstTime;
    double WaitTime;
    double TurnaroundTime;
    int contextSwitch;
    int preemption;

};
