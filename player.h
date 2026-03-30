#pragma once
#include <vector>
#include "unit.h"

class Player : public Unit{
    private:
    std::vector<int> skillid;
    
    public:
    //コンストラクタ
    Player();
    //コマンド選択
    void cmd_select();
    //攻撃対象選択
    void enemy_select(std::vector<Unit*>& enemies);
};