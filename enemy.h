#pragma once
#include <string>
#include "unit.h"
using namespace std;

class Enemy : public Unit{
    public:
    int id_;
    Enemy(int i, string n);
    void cmd_select();
};