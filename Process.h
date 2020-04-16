

//each process store its own arrival time, cpu burst (not changeable)
//finshed,turnaround time, wait time, preemption count, cpu_left... (changeable)
#include <string>
#include <deque>
using namespace std;


class Process{
public:
    Process();
    Process(char n,int time,int number,double lambda,double alpha);

    //accessors
    bool isFinished();
    bool isBlocked();
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

    //modifiers
    void addCPUTime(int i);
    void addIOTime(int i);
    void setFinished();
    void setBlocked();
    void unblocked();
    void setAlpha(double a);
    //use negative number for - operation
    void updateCPUTime(int index, int time);
    void updateIOTime(int index, int time);
    void updateTau();
    void increaseCurrentCPUBurstIndex();
    void increaseCurrentIOIndex();

    //debugger
    void print();
private:
    char name[2];
    bool is_finished;
    bool is_blocked;
    int arrivalTime;
    int numBurst;
    int currentBurstIndex;
    int currentIOIndex;
    double alpha;
    int tau;
    deque<int> CPUTime;
    deque<int> IOTime;

};