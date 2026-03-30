#pragma once
#include <string>
using namespace std;

struct CommandData{
    int id_;
    string name_;
    int mpCost;

    CommandData() : id_(0), name_(""), mpCost(0){}
    CommandData(int id, string name, int mp) : id_(id), name_(name), mpCost(mp) {}
};