#include <string>
#include <deque>
#include "Process.h"

using namespace std;

class Processes{
public:
    Processes();

    void add(Process process);

    //FOR DEBUG USE
    void print();

private:
    deque<Process> processes;
};