#pragma once
#include <string>
#include "Unit.h"

class Enemy : public Unit{
    public:
    //敵を識別するID
    int id_;
    //コンストラクタ(IDと名前を指定して生成)
    Enemy(int i, std::string n);
    //敵のコマンド設定
    void cmd_select();
};