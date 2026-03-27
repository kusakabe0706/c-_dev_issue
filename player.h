#pragma once
#include <vector>
#include "unit.h"
using namespace std;

class Player : public Unit{
    public:
    Player();
    void cmd_select();
    void enemy_select(vector<Unit*>& enemies);
};