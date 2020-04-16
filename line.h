//
// Created by 鸿昊李 on 2020-04-16.
//

#ifndef OSPROJECT1_LINE_H
#define OSPROJECT1_LINE_H

#include <string>
#include <iostream>
using namespace std;

class line {
public:
    line();
    line(string l,int t);
    void add(string s);
    void printl();
    void print();
    void clear();

private:
    int time=0;
    string data="";
};


#endif //OSPROJECT1_LINE_H
