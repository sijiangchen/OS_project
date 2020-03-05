//RCS id:
//lih19
//
//
#include <iostream>
#include <string>
#include <random>
using namespace std;

class Argument{
    //input arguments(a list of string)
};
class Processes{
    //a list of process
};
class Process{
    //each process store its own arrival time, cpu burst (not changeable)
    //finshed,turnaround time, wait time, preemption count, cpu_left... (changeable)
};
class ReadyQueue{
    //a queue of process
};
class IoQueue{
    //a queue of process
};
class Outputs{
    //a list of output
};
class Output{
    //output
};

void CreateOutputs(Output output, Output srt, Output fcfs, Output rr){
    //create output.
}

Argument ValidateInput(char* argv[]){
    //valid input
    Argument ret=Argument();
    return ret;
}
Processes CreateProcesses(Argument argv){
    Processes ret;

    return ret;
}

//return Output on success
//edit output.debug for debugging
Output ShortestJobFirst(Processes processes,Argument argv){
    //In SJF, processes are stored in the ready queue in order of priority based on their CPU burst times.
    // More specifically, the process with the shortest CPU burst time will be selected as the next process
    // executed by the CPU.
    Output ret;
    return ret;
};
Output ShortestRemainingTime(Processes processes,Argument argv){
    //The SRT algorithm is a preemptive version of the SJF algorithm. In SRT, when a process arrives,
    // before it enters the ready queue, if it has a CPU burst time that is less than the remaining time of
    // the currently running process, a preemption occurs. When such a preemption occurs, the currently
    // running process is added back to the ready queue.
    Output ret;
    return ret;
};
Output FirstComeFirstServed(Processes processes,Argument argv){
    //The FCFS algorithm is a non-preemptive algorithm in which processes line up in the ready queue,
    // waiting to use the CPU. This is your baseline algorithm (and may be implemented as RR with an
    // infinite time slice).
    Output ret;
    return ret;
};
Output RoundRobin(Processes processes,Argument argv){
    //The RR algorithm is essentially the FCFS algorithm with predefined time slice tslice. Each process
    // is given tslice amount of time to complete its CPU burst. If this time slice expires, the process is
    // preempted and added to the end of the ready queue (though see the rradd parameter described below).
    //
    //If a process completes its CPU burst before a time slice expiration, the next process on the ready queue is
    // immediately context-switched into the CPU.
    //
    //For your simulation, if a preemption occurs but there are no other processes on the ready queue,
    // do not perform a context switch.
    Output ret;
    return ret;
};

int main(int argc,char* argv[]){
    //input and process creation
    Argument arguments=ValidateInput(argv);
    Processes processes=CreateProcesses(arguments);

    //4 algo
    Output sjf=ShortestJobFirst(processes,arguments);
    Output srt=ShortestRemainingTime(processes,arguments);
    Output fcfs=FirstComeFirstServed(processes,arguments);
    Output rr=RoundRobin(processes,arguments);

    //result
    CreateOutputs(sjf,srt,fcfs,rr);
    return 0;
}

