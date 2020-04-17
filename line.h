//
// Created by 鸿昊李 on 2020-04-16.
//

#ifndef OSPROJECT1_LINE_H
#define OSPROJECT1_LINE_H

#include <string>
#include <iostream>
using namespace std;

class Line {
public:
    Line();
    Line(string l,int t,string type);
    void add(string s);
    void printl();

    void clear();

    int getTime(){ return time;};
    string getType(){ return type;};
private:
    int time=0;
    string data;
    string type;
};


#endif //OSPROJECT1_LINE_H
