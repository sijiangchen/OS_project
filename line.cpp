//
// Created by 鸿昊李 on 2020-04-16.
//

#include "line.h"
#include <string>
using namespace std;

Line::Line(string l,int t,string type) {
    this->data=l;
    this->time=t;
    this->type=type;
}

Line::Line() {

}

void Line::add(string s) {
    this->data+=s;
}



void Line::clear() {
    this->data="";
}

void Line::printl() {
    cout<<"time "<<time<<"ms: "<<this->data<<endl;
}

