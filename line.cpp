//
// Created by 鸿昊李 on 2020-04-16.
//

#include "line.h"
#include <string>
using namespace std;

line::line(string l,int t) {
    this->data=l;
    this->time=t;
}

line::line() {

}

void line::add(string s) {
    this->data+s;
}

void line::print() {
    cout<<this->data;
}

void line::clear() {
    this->data="";
}

void line::printl() {
    cout<<this->data<<endl;
}
