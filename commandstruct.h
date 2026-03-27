#pragma once
#include <string>
using namespace std;

struct CommandData{
    int id_;
    string name_;
    int mp_;
    CommandData : id_(0), name_(""), mp_(0){}
    CommandData(int id, string name, int mp) : id_(id), name_(name), mp_(mp) {}
};