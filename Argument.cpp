//
// Created by 鸿昊李 on 2020-03-09.
//

#include "Argument.h"
#include <string>

using namespace std;

Argument::Argument() {

    seed = -1;
    lambda = -1;
    upperBound = -1;
    numProcess = -1;
    contextSwitchTime = -1;
    alpha = -1;
    timeSlice = -1;
    RROption = "END";

}

Argument::Argument(int argc, char **argv) {

    seed = (unsigned int) stoi(argv[1]);
    lambda = stof(argv[2]);
    upperBound = stoi(argv[3]);
    numProcess = stoi(argv[4]);
    contextSwitchTime = stoi(argv[5]);
    alpha = stof(argv[6]);
    timeSlice = stoi(argv[7]);
    if (argc == 9) {
        RROption = argv[8];
    }
}

Argument::Argument(const Argument &argv) {
    seed=argv.getSeed();
    lambda=argv.getLambda();
    upperBound=argv.getUpperBound();
    numProcess=argv.getNumProcess();
    contextSwitchTime=argv.getContextSwitchTime();
    alpha=argv.getAlpha();
    timeSlice=argv.getTimeSlice();
    RROption=argv.getRROption();

}

Argument Argument::operator=(Argument &argv) {
    Argument ret;
    ret.seed=argv.getSeed();
    ret.lambda=argv.getLambda();
    ret.upperBound=argv.getUpperBound();
    ret.numProcess=argv.getNumProcess();
    ret.contextSwitchTime=argv.getContextSwitchTime();
    ret.alpha=argv.getAlpha();
    ret.timeSlice=argv.getTimeSlice();
    ret.RROption=argv.getRROption();
    return ret;
}

unsigned int Argument::getSeed() const {
    return seed;
}

double Argument::getLambda() const {
    return lambda;
}

int Argument::getUpperBound() const {
    return upperBound;
}

int Argument::getNumProcess() const {
    return numProcess;
}

int Argument::getContextSwitchTime() const {
    return contextSwitchTime;
}

double Argument::getAlpha() const {
    return alpha;
}

int Argument::getTimeSlice() const {
    return timeSlice;
}

string Argument::getRROption() const {
    return RROption;
}
