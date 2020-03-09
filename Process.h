

//each process store its own arrival time, cpu burst (not changeable)
//finshed,turnaround time, wait time, preemption count, cpu_left... (changeable)
#include <string>
#include <list>
using namespace std;


class Process{
public:
    Process();
    Process(char n,int time,int number);

    //accessors
    bool isFinished();

    //modifiers
    void addCPUTime(int i);
    void addIOTime(int i);
    void setFinished();

    //debugger
    void print();
private:
    char name[2];
    bool is_finished;
    int arrivalTime;
    int numBurst;
    list<int> CPUTime;
    list<int> IOtime;

};