#include <string>
using namespace std;
class Argument {
public:
    //constructors
    Argument();

    Argument(int argc,char* argv[]);
    Argument(const Argument& argv);
    Argument operator=(Argument &argv);

    //accessors
    unsigned int getSeed() const;
    double getLambda() const;
    int getUpperBound() const;
    int getNumProcess() const;
    int getContextSwitchTime() const;
    double getAlpha() const;
    int getTimeSlice() const;
    string getRROption() const;
    //modifiers


private:
    unsigned int seed;
    double lambda;
    int upperBound;
    int numProcess;
    int contextSwitchTime;
    double alpha;
    int timeSlice;
    string RROption="END";
};