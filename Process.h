

//each process store its own arrival time, cpu burst (not changeable)
//finshed,turnaround time, wait time, preemption count, cpu_left... (changeable)
#include <string>
#include <deque>
using namespace std;

#ifndef Process_h
#define Process_h
class Process{
public:
    Process();
    Process(char n,int time,int number,double lambda,double alpha);

    //accessors
    bool isFinished();
    bool isBlocked();
    bool isRunning(){return is_running;}
    bool isWaiting(){return is_waiting;}
    bool ispreempted(){return preempted;}
    int getCurrentBurstIndex();
    int getCurrentIOIndex();
    int getCPUTime(int index);
    int getCPUTime();
    int getIOTime(int index);
    int getIOTime();
    int getArrivalTime();
    int getNumBurst();
    double getAlpha();
    int getTau();
    string getName();
    int getNextIOFinishTime()const{return next_io_finish_time;}
    int getNextCPUFinishTime()const{return next_cpu_finish_time;}
    double getBurstTime()const{return burst_time;} //total burst time
    double getWaitTime()const{return wait_time;}    //total wait time
    double getTurnAroundTime()const{return turn_around_time;} //total turn around time
    
    //modifiers
    void create_copy_cpu();
    void addCPUTime(int i);
    void addIOTime(int i);
    void setFinished();
    void setBlocked();
    void setRunning();
    void setWaiting();
    void setPreempted();
    void unBlocked();
    void unWaiting();
    void unRunning();
    void unPreempted();
    void setAlpha(double a);
    void setCPUTime(int index,int time);
    //use negative number for - operation
    void updateCPUTime(int index, int time);
    void updateIOTime(int index, int time);
    void updateTau();
    void increaseCurrentCPUBurstIndex();
    void increaseCurrentIOIndex();
    void setNextIOFinishTime(int time);
    void setNextCPUFinishTime(int time);
    void addBurstTime(double time);
    void addWaitTime(double time);
    void addTurnAroundTime(double time);
    bool prerun=false;

    //debugger
    void print();
private:
    char name[2];
    bool is_finished;
    bool is_blocked;
    bool is_running;
    bool is_waiting;
    bool preempted;
    int arrivalTime;
    int numBurst;
    int currentBurstIndex;
    int currentIOIndex;
    double alpha;
    int tau;
    deque<int> CPUTime;
    deque<int> CPUTimecopy;
    deque<int> IOTime;
    int next_io_finish_time;
    int next_cpu_finish_time;
    double burst_time;
    double wait_time;
    double turn_around_time;

    // for RR only
    int amount_finished_in_current_burst;
    int amount_finished_in_current_io;


};

#endif
