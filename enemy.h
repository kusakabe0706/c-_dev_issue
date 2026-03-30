#pragma once
#include <string>
#include "unit.h"

class Enemy : public Unit{
    public:
    //敵のid
    int id_;
    //コンストラクタ
    Enemy(int i, std::string n);
    //敵のコマンド設定
    void cmd_select();
};