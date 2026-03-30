#pragma once
#include <vector>
#include "Unit.h"

class Player : public Unit{
    private:
    //プレイヤーが使用可能なコマンドのIDリスト
    std::vector<int> skillid;
    
    public:
    //コンストラクタ
    Player();
    //コマンド選択
    void cmd_select();
    //攻撃対象選択
    void enemy_select(std::vector<Unit*>& enemies);
};