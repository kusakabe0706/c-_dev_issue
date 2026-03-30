#pragma once
#include "CommandData.h"

//すべてのコマンドのデータとして機能する
class CommandMaster{
    public:
    //コマンドのIDを渡すと、そのコマンドの詳細データを返す関数
    //staticなので実態を作らなくても呼べる
    static CommandData Getter(int id);
};