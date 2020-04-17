//RCS id:
//lih19
//huangh10
//chens32
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <queue>
#include <iterator>
#include <stdlib.h>
#include <list>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "Process.h"
#include "Argument.h"
#include "Processes.h"
#include "ReadyQueue.h"
#include "Output.h"
#include "line.h"

using namespace std;

//helper function
double getNextRandomNumber(){
    return drand48();
}
double getGenerated(double r,double lambda){
    return -log( r ) / lambda;
}


void CreateOutputs(Output sjf, Output srt, Output fcfs, Output rr) {
    //create output.
}

Argument ValidateInput(int argc,char *argv[]) {
    //valid input
    Argument ret(argc,argv);
    return ret;
}


Processes CreateProcesses(Argument argv) {
    Processes ret;
    //call seed
    srand48( argv.getSeed());

    double lambda=argv.getLambda();
    double upperBound=argv.getUpperBound();
    int numProcess=argv.getNumProcess();

    char currentName='A';
    double random=0;
    double randomResult=0;
    for (int i = 0; i < numProcess; ++i) {
        do{
            random=getNextRandomNumber();
            randomResult=getGenerated(random,lambda);
        }while(randomResult>upperBound);

        int cpuNumber=(int)trunc(getNextRandomNumber()*100)+1;
        Process temp(currentName,(int)floor(randomResult),cpuNumber,lambda,argv.getAlpha());
        for (int j = 0; j < cpuNumber; ++j) {
            do{
                random=getNextRandomNumber();
                randomResult=getGenerated(random,lambda);
            }while(randomResult>upperBound);
            temp.addCPUTime((int)ceil(randomResult));
            if(j+1==cpuNumber){
                break;
            }
            do{
                random=getNextRandomNumber();
                randomResult=getGenerated(random,lambda);
            }while(randomResult>upperBound);
            temp.addIOTime((int)ceil(randomResult));
        }
        ret.add(temp);
        currentName++;
    }

    return ret;
}

//return Output on success
//edit output.debug for debugging
Output ShortestJobFirst(Processes processes, Argument argv) {
    //In SJF, processes are stored in the ready queue in order of priority based on their CPU burst times.
    // More specifically, the process with the shortest CPU burst time will be selected as the next process
    // executed by the CPU.
    Output ret("SJF");
    //print initial processes arrival time and cpu burst count and tau
    for (int i = 0; i < processes.size(); ++i) {
//        processes[i].print();
        cout<<"Process "<<processes[i].getName()
        <<" [NEW] (arrival time "<<processes[i].getArrivalTime()
        <<" ms) "<<processes[i].getNumBurst()<<" CPU bursts (tau "<<processes[i].getTau()
        <<"ms)"<<endl;
    }
    cout<<"time 0ms: Simulator started for SJF [Q <empty>]"<<endl;

    vector<line> lines;
    //
    int timeline=0;
    ReadyQueue rq;
//
    bool cpu_free=true;
    while(processes.size()!=0){
        //check for cpu burst completion
            //recalculate tau
            //switch out
                //will block on io
                //terminated


        //io burst completion
        //new process arrivals
        for (int i = 0; i < processes.size(); ++i) {
            if(processes[i].getArrivalTime()==timeline){
                string temp="time "+to_string(timeline)+"ms: Process "+
                processes[i].getName()+" (tau "+to_string(processes[i].getTau())+
                "ms) arrived; added to ready queue ";
                line l(temp,timeline);
                lines.push_back(l);
                rq.sjf_insert(processes[i]);
                cout<<"size of rq: "<<rq.size()<<endl;
//                rq.debug();
                break;
            }
        }
        //check cpu free or not
        if(cpu_free){
            Process shortest=rq.getShortestJob();
//            shortest.print();
            cpu_free=false;
        }
        //check for shortest process in ready queue

        if(timeline>=10000)break;
        timeline++;
    }

//    for (int j = 0; j < lines.size(); ++j) {
//        lines[j].printl();
//    }
//


    return ret;
};

Output ShortestRemainingTime(Processes processes, Argument argv) {
    //The SRT algorithm is a preemptive version of the SJF algorithm. In SRT, when a process arrives,
    // before it enters the ready queue, if it has a CPU burst time that is less than the remaining time of
    // the currently running process, a preemption occurs. When such a preemption occurs, the currently
    // running process is added back to the ready queue.
    Output ret("SRT");
    ReadyQueue ();

    return ret;
};


//this function is used to simulate every millisecond of each process
void EverySecond(Processes& processes, ReadyQueue& rq,int timeline){
    
    int num_process=processes.size();
    for(int i=0;i<num_process;++i){
        Process p=processes[i];
        if(p.isFinished()) continue;
        //the first time it arrives
        if(p.isWaiting()){
            p.addWaitTime(1);
        }
        
        if(p.getCurrentBurstIndex()==0){
            if(p.getArrivalTime()==timeline){
                rq.push_back(p);
                p.setWaiting();
                cout<<"time "<<timeline<<"ms: Process "<<p.getName()<<" arrived; added to ready queue ";
                rq.print();
            }
                  }
        
               //finish i/o burst and enter the ready queue
                 
               if(p.isBlocked()&&p.getNextIOFinishTime()==timeline){
                  p.setWaiting();
                  p.unBlocked();
                  rq.push_back(p);
                  cout<<"time "<<timeline<<"ms: Process "<<p.getName()<<" completed I/O; added to ready queue ";
                  rq.print();
               }
   
        processes[i]=p;
}
}

Output FirstComeFirstServed(Processes processes, Argument argv) {
    //The FCFS algorithm is a non-preemptive algorithm in which processes line up in the ready queue,
    // waiting to use the CPU. This is your baseline algorithm (and may be implemented as RR with an
    // infinite time slice).
    Output ret("FCFS");
    int cs_time=argv.getContextSwitchTime();
    ReadyQueue rq;
    int timeline=0;
    cout<<"time "<<timeline<<"ms: Simulator started for FCFS ";
    rq.print();
   
    int num_process=processes.size();
    
    //set CPU state variables
    bool isrunning=false;
    //bool iscontextswitching=false;
    bool isidle=true;
    int bursttime=0;
    int num_process_finished=0;
    //int num_cs=0;  //number of context switches
    Process* current_process;
    //initialize the ready queue
    EverySecond(processes, rq, timeline);
    
    //while there are unfinished processes
    while(num_process_finished<num_process){
        if(isidle){
            //if there is a process in the ready queue
            if(rq.size()!=0){
                for(int i=0;i<num_process;++i){
                   if(processes[i].getName()==rq[0].getName())
                       current_process=&processes[i];
                }
                rq.pop_front();//remove the current process from the ready queue
                bursttime=current_process->getCPUTime(current_process->getCurrentBurstIndex());
                current_process->addBurstTime(bursttime);
                isidle=false;
                current_process->unWaiting();
                //cpu context switch in
        
                for(int t=1;t<=cs_time/2-1;++t){
                    timeline++;
                    EverySecond(processes,rq, timeline);
                     
                }
                timeline++;
                cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" started using the CPU for "<<bursttime<<"ms burst ";
                rq.print();
                EverySecond(processes,rq, timeline);
               
              //cpu burst
               
                isrunning=true;
                current_process->setRunning();
                ret.addContextSwitch();
                ret.addCPUBurstTime(bursttime);
               
                for(int t=1;t<=bursttime-1;++t){
                   timeline++;
                   EverySecond(processes, rq, timeline);
                }
                timeline++;
                //finish cpu burst
                isrunning=false;
                current_process->unRunning();
                
                //calculate the finished processes
                if(current_process->getCurrentBurstIndex()==current_process->getNumBurst()-1){
                    ret.addWaitTime(current_process->getWaitTime());
                    cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" terminated ";
                    rq.print();
                    current_process->setFinished();
                    num_process_finished++;
                }
                else{
                  //enter the i/o subsystem
                    int num_burst_to_go=current_process->getNumBurst()-1-current_process->getCurrentBurstIndex();
                    if(num_burst_to_go==1)
                        cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" completed a CPU burst; "<<num_burst_to_go<<" burst to go ";
                    else
                        cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" completed a CPU burst; "<<num_burst_to_go<<" bursts to go ";
                    rq.print();
                    current_process->increaseCurrentCPUBurstIndex();
                    int next_IO_time=current_process->getIOTime(current_process->getCurrentIOIndex());
                    current_process->setNextIOFinishTime(timeline+next_IO_time+cs_time/2);
                    cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" switching out of CPU; will block on I/O until time "<<current_process->getNextIOFinishTime()<<"ms ";
                    rq.print();
                    current_process->setBlocked();
                    current_process->increaseCurrentIOIndex();
                }
                
                //cpu context switch out
                   
                   EverySecond(processes, rq, timeline);
                    for(int t=1;t<=cs_time/2;++t){
                       timeline++;
                       EverySecond(processes, rq, timeline);
                         }
                     
                    isidle=true;
                
        }
            //if the ready queue is empty
            else{
                ++timeline;
                EverySecond(processes, rq, timeline);
                 
            }
                    
}
    }
    
    int total_turnaround=ret.getCPUBurstTime()+ret.getWaitTime()+ret.getContextSwitch()*cs_time;
    ret.addTurnaroundTime(total_turnaround);
    cout<<"time "<<timeline<<"ms: Simulator ended for FCFS ";
    rq.print();
    
    return ret;
};

Output RoundRobin(Processes processes, Argument argv) {
    //The RR algorithm is essentially the FCFS algorithm with predefined time slice tslice. Each process
    // is given tslice amount of time to complete its CPU burst. If this time slice expires, the process is
    // preempted and added to the end of the ready queue (though see the rradd parameter described below).
    //
    //If a process completes its CPU burst before a time slice expiration, the next process on the ready queue is
    // immediately context-switched into the CPU.
    //
    //For your simulation, if a preemption occurs but there are no other processes on the ready queue,
    // do not perform a context switch.
    Output ret("RR");
    ReadyQueue ();

    return ret;
};

int main(int argc, char *argv[]) {
    setvbuf( stdout, NULL, _IONBF, 0 );
    //output file
    ofstream out_text("simout.txt");

    //input and process creation
    Argument arguments = ValidateInput(argc,argv);
    Processes processes = CreateProcesses(arguments);

    Output sjf = ShortestJobFirst(processes, arguments);
    processes = CreateProcesses(arguments);
    Output srt = ShortestRemainingTime(processes, arguments);

    //chen
    processes = CreateProcesses(arguments);
     for(int i=0;i<processes.size();++i){
        int num_burst=processes[i].getNumBurst();
        if(num_burst==1)
        cout<<"Process "<<processes[i].getName()<<" [NEW] (arrival time "<<processes[i].getArrivalTime()<<" ms) "<<num_burst<<" CPU burst"<<endl;
        else
        cout<<"Process "<<processes[i].getName()<<" [NEW] (arrival time "<<processes[i].getArrivalTime()<<" ms) "<<num_burst<<" CPU bursts"<<endl;
    }
    
    Output fcfs = FirstComeFirstServed(processes, arguments);
    out_text<<"Algorithm FCFS"<<endl;
    fcfs.print(out_text);

    //huang
    processes = CreateProcesses(arguments);
    Output rr = RoundRobin(processes, arguments);
    //result
    //li
    CreateOutputs(sjf, srt, fcfs, rr);
    /* exp-random.c */


    return 0;
}

