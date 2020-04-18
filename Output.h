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
    int getNumOfBurst(){return num_of_burst;}
    
    //modifier
    void addCPUBurstTime(double time);
    void addWaitTime(double time);
    void addTurnaroundTime(double time);
    void addContextSwitch();
    void addPreemption();
    void changeName(string new_name) { name = new_name; }
    void setNumOfBurst(int num);
    
    //debugger
    void print();
    
    //output the summaries
    ostream& print(ostream& out_str);
    
private:
    string name;
    double CPUBurstTime;
    double WaitTime;
    double TurnaroundTime;
    int contextSwitch;
    int preemption;
    int num_of_burst;
};
