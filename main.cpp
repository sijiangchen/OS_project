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
#include <algorithm>
#include <vector>
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


void CreateOutputs(Output sjf, Output srt, Output fcfs, Output rr, ofstream& out) {
    //create output.
    out<<"Algorithm FCFS"<<endl;
    fcfs.print(out);

    out<<"Algorithm SRT"<<endl;
    sjf.print(out);

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
            <<" ms) "<<processes[i].getNumBurst();
        if(processes[i].getNumBurst()==1){
            cout<<" CPU burst (tau ";
        }else{
            cout<<" CPU bursts (tau ";
        }
        cout<<processes[i].getTau()
            <<"ms)"<<endl;
    }
    cout<<"time 0ms: Simulator started for SJF [Q <empty>]"<<endl;

    vector<Line> lines;
    //
    int timeline=0;
    ReadyQueue rq;
//
    int counter=0;
    int switch_time=0;
    bool cpu_free=true;
    Process future;
    while(processes.size()!=0){
        //check for cpu burst completion
        //recalculate tau
        //switch out
        //will block on io
        //terminated

        if(!cpu_free){
            for (int i = 0; i < processes.size(); ++i) {
                if(processes[i].isRunning()){
                    if(timeline==processes[i].getNextCPUFinishTime()){
                        processes[i].unRunning();
                        processes[i].setBlocked();
                        string s;
                        s+="Process ";
                        s+=processes[i].getName();
                        int left=processes[i].getNumBurst()-(processes[i].getCurrentBurstIndex()+1);
                        if(left==0){
                            processes[i].addTurnAroundTime(timeline-processes[i].getArrivalTime()+0.5*argv.getContextSwitchTime());
                            s+=" terminated ";
                            s+=rq.print_string();
                            rq.removeProcess(processes[i]);
                            ret.addWaitTime(processes[i].getWaitTime());
                            ret.addCPUBurstTime(processes[i].getBurstTime());
                            ret.addTurnaroundTime(processes[i].getTurnAroundTime());
                            processes.remove(processes[i]);
                            lines.push_back(Line(s,timeline,"terminated"));
                            cpu_free=true;

                            switch_time+=argv.getContextSwitchTime()/2;
                            break;
                        }
                        s+=+" (tau ";
                        s+=to_string(processes[i].getTau());
                        s+="ms) completed a CPU burst; ";
                        s+=to_string(left);
                        if(left==1){
                            s+=" burst to go ";
                        }else{
                            s+=" bursts to go ";
                        }

                        s+=rq.print_string();
                        Line l(s,timeline,"finishCPU");
                        lines.push_back(l);
                        processes[i].updateTau();
                        s.clear();
                        s+="Recalculated tau = ";
                        s+=to_string(processes[i].getTau());
                        s+="ms for process ";
                        s+=processes[i].getName();
                        s+=" ";
                        s+=rq.print_string();
                        Line l2(s,timeline,"recalculatedTau");
                        lines.push_back(l2);
                        s.clear();
                        s+="Process ";
                        s+=processes[i].getName();
                        s+=" switching out of CPU; will block on I/O until time ";
                        s+=to_string(timeline+processes[i].getIOTime()+argv.getContextSwitchTime()/2);
                        processes[i].setNextIOFinishTime(timeline+processes[i].getIOTime()+argv.getContextSwitchTime()/2);
                        s+="ms ";
                        s+=rq.print_string();
                        Line l3(s,timeline,"finishIO");
                        lines.push_back(l3);
                        cpu_free=true;
                        switch_time=argv.getContextSwitchTime()/2;
                        processes[i].increaseCurrentCPUBurstIndex();
                    }

                }
            }
        }
        //io burst completion
        for (int i = 0; i < processes.size(); ++i) {
            if(timeline==0){
                break;
            }
            if(processes[i].getNextIOFinishTime()==timeline){
                string name=processes[i].getName();
                string tau=to_string(processes[i].getTau());
                processes[i].unBlocked();
                processes[i].increaseCurrentIOIndex();
                rq.sjf_insert(processes[i]);
                string q=rq.print_string();

                string temp="Process ";
                temp+=name;
                temp+=" (tau ";
                temp+=tau;
                temp+="ms) completed I/O; added to ready queue ";
                temp+=q;
                Line l(temp,timeline,"finishIO");
                lines.push_back(l);
            }
        }
        //new process arrivals
        for (int i = 0; i < processes.size(); ++i) {
            if(processes[i].getArrivalTime()==timeline){
                string temp="Process "+
                            processes[i].getName()+" (tau "+to_string(processes[i].getTau())+
                            "ms) arrived; added to ready queue ";
                Line l(temp,timeline,"arrive");
                rq.sjf_insert(processes[i]);
                l.add(rq.print_string());
                lines.push_back(l);
            }
        }

        //check cpu free or not
        if(cpu_free and switch_time==0){
            //check for shortest process in ready queue
            if(rq.size()!=0){
                ret.addContextSwitch();
                Process shortest=rq[0];
                shortest.addWaitTime(0.5*argv.getContextSwitchTime());
                shortest.addBurstTime(shortest.getCPUTime(shortest.getCurrentBurstIndex()));
                shortest.setRunning();
                shortest.setNextCPUFinishTime(timeline+argv.getContextSwitchTime()/2+shortest.getCPUTime(shortest.getCurrentBurstIndex()));
                string temp;
                temp+="Process ";
                temp+=shortest.getName();
                temp+=" (tau ";
                temp+=to_string(shortest.getTau());
                temp+="ms) started using the CPU for ";
                temp+=to_string(shortest.getCPUTime(shortest.getCurrentBurstIndex()));
                temp+="ms burst ";
                processes.replace(shortest);
                rq.removeProcess(shortest);
                //check if any io will finish in two future seconds
                int now=timeline;
                vector<int> index;
                for (int i = 0; i < processes.size(); ++i) {
                    int finishtime=processes[i].getNextIOFinishTime();
                    if(finishtime==(now+1)){
                        rq.sjf_insert(processes[i]);
                        index.push_back(i);
                    }
                }

                temp+=rq.print_string();
                for (int j = 0; j < index.size(); ++j) {
                    rq.removeProcess(processes[index[j]]);
                }

                Line l(temp,timeline+argv.getContextSwitchTime()/2,"startCPU");
                lines.push_back(l);

                cpu_free=false;
            }
        }



        if(switch_time!=0){
            switch_time--;
        }
        timeline++;
        counter++;

        if(rq.size()!=0){
            for (int i = 0; i < rq.size(); ++i) {
                rq[i].addWaitTime(1);
            }
        }
    }
    string t;
    t+="Simulator ended for SJF [Q <empty>]";
    Line last(t,timeline+1,"finish");
    lines.push_back(last);

//    sort(lines.begin(),lines.end(),sjf_sort);
    int max=lines.size();
    for (int j = 0; j < max; ++j) {
        if(j+1!= max&&lines[j].getTime()>lines[j+1].getTime()){
            lines[j+1].printl();
            lines[j].printl();
            j++;
        }else{
            lines[j].printl();

        }
    }

    cout<<endl;

    return ret;
};


void srt_second(Processes& processes,ReadyQueue& rq,
                int timeline,int cs_time,vector<Line>& lines,
                bool& cpu_free,int &cpu_in,int &cpu_out,int & has_run,
                vector<Process> &temp,vector<Process> &temp2){
    //cpu finish

    if(!cpu_free){
        has_run++;
        for (int i = 0; i < processes.size(); ++i) {
            if(processes[i].isRunning()){
                if(processes[i].getNextCPUFinishTime()==timeline){
                    //finish a burst, start to move to rq
                    processes[i].unRunning();
                    processes[i].setNextIOFinishTime(timeline+processes[i].getIOTime()+cs_time/2);
                    processes[i].setBlocked();
                    cpu_in=cs_time/2;
                    cpu_free=true;
                    string t;
                    t+="Process "+processes[i].getName()+" (tau "+to_string(processes[i].getTau());
                    t+="ms) completed a CPU burst; "+to_string(processes[i].getNumBurst()-processes[i].getCurrentBurstIndex()-1);
                    t+=" bursts to go "+rq.print_string();
                    lines.push_back(Line(t,timeline,"finishCPU"));
                    t.clear();
                    processes[i].updateTau();
                    t+="Recalculated tau = "+to_string(processes[i].getTau())+"ms for process ";
                    t+=processes[i].getName()+" "+rq.print_string();
                    lines.push_back(Line(t,timeline,"finishCPU"));
                    t.clear();
                    t+="Process "+processes[i].getName()+" switching out of CPU; will block on I/O until time ";
                    t+=to_string(processes[i].getNextIOFinishTime())+"ms "+rq.print_string();
                    lines.push_back(Line(t,timeline,"io"));
                    processes[i].increaseCurrentCPUBurstIndex();
                    processes.replace(processes[i]);

                }
            }
        }
    }

    //io finihs
    for (int i = 0; i < processes.size(); ++i) {
        if(processes[i].isBlocked()){
            if(processes[i].getNextIOFinishTime()==timeline){
                //need preem or not
                Process running=processes.findRunning();
                if(processes[i].getTau()<running.getTau()){
                    //preemt
                    running.unRunning();
                    running.updateCPUTime(running.getCurrentBurstIndex(),-1*(has_run));
                    cpu_out=2;
                    temp.push_back(running);
                    cpu_free=true;
                    processes[i].increaseCurrentIOIndex();
                    rq.sjf_insert(processes[i]);
                    string t="Process "+processes[i].getName()+
                            " (tau "+to_string(processes[i].getTau())+
                            "ms) completed I/O; preempting "+running.getName()
                            +" "+rq.print_string();
                    lines.push_back(Line(t,timeline,"pree"));
                    cpu_in=2;
                }else{
                    //add back to queue
                    processes[i].unBlocked();
                    processes[i].increaseCurrentIOIndex();
                    rq.sjf_insert(processes[i]);
                }
            }
        }
    }

    if(cpu_out==0){
        if(temp.size()!=0){
            rq.sjf_insert(temp[0]);
            temp.clear();
        }
    }
    //new arrival
    for (int i = 0; i < processes.size(); ++i) {
        if(processes[i].getArrivalTime()==timeline){
            string t;
            rq.sjf_insert(processes[i]);
            t+="Process "+processes[i].getName()+" ";
            t+="(tau "+to_string(processes[i].getTau())+"ms) arrived; added to ready queue "+rq.print_string();
            lines.push_back(Line(t,timeline,"arrival"));
        }
    }

    //run new cpu
    if(cpu_free){
        if(rq.size()!=0){

            if(cpu_out!=0){
                cpu_out--;
            }else{
                if(cpu_in!=0){
                    cpu_in--;
                }else{
                    has_run=0;
                    string t;
                    t+="Process "+rq[0].getName()+" (tau "+to_string(rq[0].getTau());
                    t+="ms) started using the CPU with "+to_string(rq[0].getCPUTime())+"ms burst remaining ";
                    rq[0].setRunning();
                    rq[0].setNextCPUFinishTime(timeline+rq[0].getCPUTime());
                    processes.replace(rq[0]);
                    rq.removeProcess(rq[0]);
                    t+=rq.print_string();
                    lines.push_back(Line(t,timeline,"startCPU"));
                    cpu_out=cs_time/2;
                    cpu_free=false;
                }
            }
        }
    }
    //need preemt?




}

Output ShortestRemainingTime(Processes processes, Argument argv) {
    //The SRT algorithm is a preemptive version of the SJF algorithm. In SRT, when a process arrives,
    // before it enters the ready queue, if it has a CPU burst time that is less than the remaining time of
    // the currently running process, a preemption occurs. When such a preemption occurs, the currently
    // running process is added back to the ready queue.

    Output ret("SRT");
    ReadyQueue rq;
    int cs_time=argv.getContextSwitchTime();

    //print initial processes arrival time and cpu burst count and tau
    for (int i = 0; i < processes.size(); ++i) {
        processes[i].create_copy_cpu();
        cout<<"Process "<<processes[i].getName()
            <<" [NEW] (arrival time "<<processes[i].getArrivalTime()
            <<" ms) "<<processes[i].getNumBurst();
        if(processes[i].getNumBurst()==1){
            cout<<" CPU burst (tau ";
        }else{
            cout<<" CPU bursts (tau ";
        }
        cout<<processes[i].getTau()
            <<"ms)"<<endl;
    }
    cout<<"time 0ms: Simulator started for SRT [Q <empty>]"<<endl;

    vector<Line> lines;
    //
    int timeline=0;
    bool cpu_free=true;
    int cstime=argv.getContextSwitchTime();
    int cpu_in=2;
    int cpu_out=0;

    vector<Process>temp;
    vector<Process>temp2;
    int has_run=0;
    while(processes.size()!=0){
        if(timeline==310)break;
        srt_second(processes,rq,timeline,cstime,lines,cpu_free,cpu_in,cpu_out,
                   has_run,temp,temp2);
        timeline++;

    }

    string t;
    t+="Simulator ended for SRT [Q <empty>]";
    Line last(t,timeline+cstime/2,"finish");
    lines.push_back(last);

//    sort(lines.begin(),lines.end(),sjf_sort);
    int max=lines.size();
    for (int j = 0; j < max; ++j) {
        if(j+1!= max&&lines[j].getTime()>lines[j+1].getTime()){
            lines[j+1].printl();
            lines[j].printl();
            j++;
        }else{
            lines[j].printl();
        }
    }

    cout<<endl;


    return ret;
};



//this function is used to simulate every millisecond of each process
//void EverySecond(Processes& processes, ReadyQueue& rq,int timeline,bool begin){
//    int num_process=processes.size();
//    for(int i=0;i<num_process;++i){
//        Process p=processes[i];
//        if(begin){ p=processes[num_process-1-i];}
//        if(p.isFinished()) continue;
//
//        if(p.isWaiting()){      //when waiting in the ready queue
//            p.addWaitTime(1);
//        }
//
//
//        //finish i/o burst and enter the ready queue
//        if(p.isBlocked()&&p.getNextIOFinishTime()==timeline){
//            p.setWaiting();
//            p.unBlocked();
//            if(begin) rq.push_front(p);
//            else rq.push_back(p);
//            cout<<"time "<<timeline<<"ms: Process "<<p.getName()<<" completed I/O; added to ready queue ";
//            rq.print();
//                     }
//
//         //the first time it arrives
//        if(p.getCurrentBurstIndex()==0){
//            if(p.getArrivalTime()==timeline){
//                if(begin) rq.push_front(p);
//                else rq.push_back(p);
//                p.setWaiting();
//                cout<<"time "<<timeline<<"ms: Process "<<p.getName()<<" arrived; added to ready queue ";
//                rq.print();
//            }
//                  }
//
//
//        if(begin) processes[num_process-1-i]=p;
//        else processes[i]=p;
//}
//}



//Output FirstComeFirstServed(Processes processes, Argument argv) {
//    //The FCFS algorithm is a non-preemptive algorithm in which processes line up in the ready queue,
//    // waiting to use the CPU. This is your baseline algorithm (and may be implemented as RR with an
//    // infinite time slice).
//    Output ret("FCFS");
//    int cs_time=argv.getContextSwitchTime();
//    bool begin=false;
//    ReadyQueue rq;
//    int timeline=0;
//    cout<<"time "<<timeline<<"ms: Simulator started for FCFS ";
//    rq.print();
//
//    int num_process=processes.size();
//
//    //set CPU state variables
//    bool isrunning=false;
//    //bool iscontextswitching=false;
//    bool isidle=true;
//    int bursttime=0;
//    int num_process_finished=0;
//    //int num_cs=0;  //number of context switches
//    Process* current_process;
//    //initialize the ready queue
//    EverySecond(processes, rq, timeline);
//
//    //while there are unfinished processes
//    while(num_process_finished<num_process){
//        if(isidle){
//            //if there is a process in the ready queue
//            if(rq.size()!=0){
//                for(int i=0;i<num_process;++i){
//                    if(processes[i].getName()==rq[0].getName())
//                        current_process=&processes[i];
//                }
//
//                rq.pop_front();//remove the current process from the ready queue
//                bursttime=current_process->getCPUTime(current_process->getCurrentBurstIndex());
//                current_process->addBurstTime(bursttime);
//                isidle=false;
//                current_process->unWaiting();
//                //cpu context switch in
//
//                for(int t=1;t<=cs_time/2-1;++t){
//                    timeline++;
//                    EverySecond(processes,rq, timeline);
//
//                }
//                timeline++;
//                cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" started using the CPU for "<<bursttime<<"ms burst ";
//                rq.print();
//                EverySecond(processes,rq, timeline);
//
//                //cpu burst
//
//                isrunning=true;
//                current_process->setRunning();
//                ret.addContextSwitch();
//                ret.addCPUBurstTime(bursttime);
//
//                for(int t=1;t<=bursttime-1;++t){
//                    timeline++;
//                    EverySecond(processes, rq, timeline);
//                }
//                timeline++;
//                //finish cpu burst
//                isrunning=false;
//                current_process->unRunning();
//
//                //calculate the finished processes
//                if(current_process->getCurrentBurstIndex()==current_process->getNumBurst()-1){
//                    ret.addWaitTime(current_process->getWaitTime());
//                    cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" terminated ";
//                    rq.print();
//                    current_process->setFinished();
//                    num_process_finished++;
//                }
//                else{
//                    //enter the i/o subsystem
//                    int num_burst_to_go=current_process->getNumBurst()-1-current_process->getCurrentBurstIndex();
//                    if(num_burst_to_go==1)
//                        cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" completed a CPU burst; "<<num_burst_to_go<<" burst to go ";
//                    else
//                        cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" completed a CPU burst; "<<num_burst_to_go<<" bursts to go ";
//                    rq.print();
//                    current_process->increaseCurrentCPUBurstIndex();
//                    int next_IO_time=current_process->getIOTime(current_process->getCurrentIOIndex());
//                    current_process->setNextIOFinishTime(timeline+next_IO_time+cs_time/2);
//                    cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" switching out of CPU; will block on I/O until time "<<current_process->getNextIOFinishTime()<<"ms ";
//                    rq.print();
//                    current_process->setBlocked();
//                    current_process->increaseCurrentIOIndex();
//                }
//
//                //cpu context switch out
//
//                EverySecond(processes, rq, timeline);
//                for(int t=1;t<=cs_time/2;++t){
//                    timeline++;
//                    EverySecond(processes, rq, timeline);
//                }
//
//                isidle=true;
//
//            }
//                //if the ready queue is empty
//            else{
//                ++timeline;
//                EverySecond(processes, rq, timeline);
//
//            }
//
//        }
//    }
//
//    int total_turnaround=ret.getCPUBurstTime()+ret.getWaitTime()+ret.getContextSwitch()*cs_time;
//    ret.addTurnaroundTime(total_turnaround);
//    cout<<"time "<<timeline<<"ms: Simulator ended for FCFS ";
//    rq.print();
//
//    return ret;
//};



//Output RoundRobin(Processes processes, Argument argv) {
//    //The RR algorithm is essentially the FCFS algorithm with predefined time slice tslice. Each process
//    // is given tslice amount of time to complete its CPU burst. If this time slice expires, the process is
//    // preempted and added to the end of the ready queue (though see the rradd parameter described below).
//    //
//    //If a process completes its CPU burst before a time slice expiration, the next process on the ready queue is
//    // immediately context-switched into the CPU.
//    //
//    //For your simulation, if a preemption occurs but there are no other processes on the ready queue,
//    // do not perform a context switch.
//    Output ret("RR");
//    int cs_time=argv.getContextSwitchTime();
//    int tslice=argv.getTimeSlice();
//    bool begin=false;
//    if(argv.getRROption()=="BEGIN") begin=true;
//    ReadyQueue rq;
//    int timeline=0;
//    cout<<"time "<<timeline<<"ms: Simulator started for RR ";
//    rq.print();
//
//    int num_process=processes.size();
//
//    //set CPU state variables
//    bool isrunning=false;
//    //bool iscontextswitching=false;
//    bool isidle=true;
//    int bursttime=0;
//    int num_process_finished=0;
//    //bool preempted=false;
//    //int num_cs=0;  //number of context switches
//    Process* current_process;
//    //initialize the ready queue
//    EverySecond(processes, rq, timeline,begin);
//
//    //while there are unfinished processes
//    while(num_process_finished<num_process){
//    if(isidle){
//        //if there is a process in the ready queue
//            if(rq.size()!=0){
//                for(int i=0;i<num_process;++i){
//                    if(processes[i].getName()==rq[0].getName())
//                       current_process=&processes[i];
//                    }
//                rq.pop_front();//remove the current process from the ready queue
//                bursttime=current_process->getCPUTime(current_process->getCurrentBurstIndex());
//                current_process->addBurstTime(bursttime);
//                isidle=false;
//                current_process->unWaiting();
//
//                //cpu context switch in
//                for(int t=1;t<=cs_time/2-1;++t){
//                    timeline++;
//                    EverySecond(processes,rq, timeline,begin);
//
//                    }
//                timeline++;
//                if(!current_process->ispreempted())
//                   cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" started using the CPU for "<<bursttime<<"ms burst ";
//                else
//                    cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" started using the CPU with "<<bursttime<<"ms burst remaining ";
//                rq.print();
//                EverySecond(processes,rq, timeline,begin);
//
//                  //cpu burst
//
//                isrunning=true;
//                current_process->setRunning();
//                ret.addContextSwitch();
//
//                bool tag=false;
//
//                //if current burst is not expired
//                do{
//                if(tag)  EverySecond(processes, rq, timeline,begin);
//                if(bursttime<=tslice){
//                ret.addCPUBurstTime(bursttime);
//                for(int t=1;t<=bursttime-1;++t){
//                    timeline++;
//                    EverySecond(processes, rq, timeline,begin);
//                    }
//                    bursttime=0;
//                    timeline++;
//                }
//                else{       //if current burst is expired
//                    ret.addCPUBurstTime(tslice);
//                    for(int t=1;t<=tslice-1;++t){
//                        timeline++;
//                        EverySecond(processes, rq, timeline,begin);
//                    }
//                  bursttime=bursttime-tslice;
//                  timeline++;
//                    if(rq.isEmpty()&&bursttime) {
//                        tag=true;
//                        cout<<"time "<<timeline<<"ms: Time slice expired; no preemption because ready queue is empty ";
//                        rq.print();
//                    }
//                }
//                }while(rq.isEmpty()&&bursttime);
//
//                if(bursttime==0){
//                   current_process->unPreempted();
//                }
//                //if current process is expired and the ready queue is not empty
//                else{
//                    current_process->setPreempted();
//                    current_process->setCPUTime(current_process->getCurrentBurstIndex(), bursttime);
//                    ret.addPreemption();
//                }
//
//                    //timeline++;
//                    //finish cpu burst
//                    isrunning=false;
//                    current_process->unRunning();
//
//                //when it finish a complete cpu burst
//                if(!current_process->ispreempted()){
//                    //calculate the finished processes
//                    if(current_process->getCurrentBurstIndex()==current_process->getNumBurst()-1){
//                        ret.addWaitTime(current_process->getWaitTime());
//                        cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" terminated ";
//                        rq.print();
//                        current_process->setFinished();
//                        num_process_finished++;
//                    }
//                    else{
//                      //enter the i/o subsystem
//                        int num_burst_to_go=current_process->getNumBurst()-1-current_process->getCurrentBurstIndex();
//                        if(num_burst_to_go==1)
//                            cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" completed a CPU burst; "<<num_burst_to_go<<" burst to go ";
//                        else
//                            cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" completed a CPU burst; "<<num_burst_to_go<<" bursts to go ";
//                        rq.print();
//                        current_process->increaseCurrentCPUBurstIndex();
//                        int next_IO_time=current_process->getIOTime(current_process->getCurrentIOIndex());
//                        current_process->setNextIOFinishTime(timeline+next_IO_time+cs_time/2);
//                        cout<<"time "<<timeline<<"ms: Process "<<current_process->getName()<<" switching out of CPU; will block on I/O until time "<<current_process->getNextIOFinishTime()<<"ms ";
//                        rq.print();
//                        current_process->setBlocked();
//                        current_process->increaseCurrentIOIndex();
//                    }
//                }
//                else{  //if it is preempted
//                    cout<<"time "<<timeline<<"ms: Time slice expired; process "<<current_process->getName()<<" preempted with "<<current_process->getCPUTime(current_process->getCurrentBurstIndex())<<"ms to go ";
//                    rq.print();
//                }
//                    //cpu context switch out
//
//                       EverySecond(processes, rq, timeline,begin);
//                        for(int t=1;t<=cs_time/2-1;++t){
//                           timeline++;
//                           EverySecond(processes, rq, timeline,begin);
//                             }
//                        timeline++;
//                       //which one first??
//                      if(current_process->ispreempted()){
//                          rq.push_back(*current_process);
//                          //current_process->unPreempted();
//                      }
//                        EverySecond(processes, rq, timeline,begin);
//                      if(current_process->ispreempted())
//                        current_process->setWaiting();
//                        isidle=true;
//
//            }
//                //if the ready queue is empty
//                else{
//                    ++timeline;
//                    EverySecond(processes, rq, timeline,begin);
//
//                }
//
//    }
//        }
//
//        int total_turnaround=ret.getCPUBurstTime()+ret.getWaitTime()+ret.getContextSwitch()*cs_time;
//        ret.addTurnaroundTime(total_turnaround);
//        cout<<"time "<<timeline<<"ms: Simulator ended for RR ";
//        rq.print();
//
//        return ret;
//};


/*huang
void EverySecond_RR(Processes& processes, ReadyQueue& rq, int timeline，int time_slice, int i_in_time_slice, bool isEND){

    int num_process = processes.size();
    for (int i = 0; i < num_process; ++i) {
        Process p = processes[i];

        if (p.isFinished()) continue;

        //the first time it arrives
        if (p.isWaiting()){
            p.addWaitTime(1);
        }

        if (p.getCurrentBurstIndex() == 0){
            if(p.getArrivalTime() == timeline) {
                if (isEND) {  rq.push_back(p); }
                else { rq.push_front(p); }
                p.setWaiting();
                cout<<"time "<<timeline<<"ms: Process "<<p.getName()<<" arrived; added to ready queue ";
                rq.print();
            }
        }

        //finish i/o burst and enter the ready queue
        if (p.isBlocked() && p.getNextIOFinishTime() == timeline) {
            p.setWaiting();
            p.unBlocked();

            if (isEND) {  rq.push_back(p); }
            else { rq.push_front(p); }

            cout<<"time "<<timeline<<"ms: Process "<<p.getName()<<" completed I/O; added to ready queue ";
            rq.print();
        }

        processes[i]=p;
    }
}

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

    int num_process = processes.size();
    processes.queue_sort_by_arrival_time();
    // processes.print();

    bool isEND;
    if (argv.getRROption() == "END") {
        isEND = true;
    }
    else {
        isEND = false;
    }

    int time_slice = argv.getTimeSlice();

    // if time slice is larger than the max burst time. use FCFS instead
    if (processes.get_max_burst_time() < time_slice) {
        Output ret = FirstComeFirstServed(processes, argv);
        ret.changeName("RR");
        return ret;
    }


    Output ret("RR");
    ReadyQueue rq;
    Process* p;

    int timeline = processes[0].getArrivalTime();
    int finished = 0;
    int i_time_slice = 0;
    EverySecond_RR(processes, rq, timeline, time_slice, i_time_slice, isEND);

    while (finished != num_process) {
        if (rq.size() != 0){
            // ready queue not empty

            // find the process at the front
            for(int i=0;i<num_process;++i){
                if(processes[i].getName() == rq[0].getName())
                    p = &processes[i];
            }

            rq.pop_front();


        }
        else {
            // ready queue is empty
            timeline++;
            EverySecond_RR(processes, rq, timeline, time_slice, i_time_slice, isEND);
        }
    }


    return ret;
};
*/


int main(int argc, char *argv[]) {
    setvbuf( stdout, NULL, _IONBF, 0 );
    //output file
    ofstream out_text("simout.txt");

    //input and process creation
    Argument arguments = ValidateInput(argc,argv);
    Processes processes = CreateProcesses(arguments);

    // Output sjf = ShortestJobFirst(processes, arguments);
     processes = CreateProcesses(arguments);
     Output srt = ShortestRemainingTime(processes, arguments);

//    chen
//    processes = CreateProcesses(arguments);
//    int total_burst=0;
//    for(int i=0;i<processes.size();++i){
//        int num_burst=processes[i].getNumBurst();
//         total_burst+=num_burst;
//        if(num_burst==1)
//        cout<<"Process "<<processes[i].getName()<<" [NEW] (arrival time "<<processes[i].getArrivalTime()<<" ms) "<<num_burst<<" CPU burst"<<endl;
//        else
//        cout<<"Process "<<processes[i].getName()<<" [NEW] (arrival time "<<processes[i].getArrivalTime()<<" ms) "<<num_burst<<" CPU bursts"<<endl;
//    }
    
//    Output fcfs = FirstComeFirstServed(processes, arguments);
//    fcfs.setNumOfBurst(total_burst);
//    out_text<<"Algorithm FCFS"<<endl;
//    fcfs.print(out_text);
//    cout<<endl;
//
//
//   processes = CreateProcesses(arguments);
//    for(int i=0;i<processes.size();++i){
//           int num_burst=processes[i].getNumBurst();
//
//           if(num_burst==1)
//           cout<<"Process "<<processes[i].getName()<<" [NEW] (arrival time "<<processes[i].getArrivalTime()<<" ms) "<<num_burst<<" CPU burst"<<endl;
//           else
//           cout<<"Process "<<processes[i].getName()<<" [NEW] (arrival time "<<processes[i].getArrivalTime()<<" ms) "<<num_burst<<" CPU bursts"<<endl;
//       }
//    Output rr = RoundRobin(processes, arguments);
//    rr.setNumOfBurst(total_burst);
//    out_text<<"Algorithm RR"<<endl;
//    rr.print(out_text);

    //result
    //li
//    CreateOutputs(sjf, srt, fcfs, rr,out_text);
    /* exp-random.c */


    return 0;
}

