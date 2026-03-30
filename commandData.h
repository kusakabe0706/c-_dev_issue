#pragma once
#include <string>
using namespace std;

//コマンドの基本データ(id,名前,消費MP)をまとめる構造体
struct CommandData{
    int id_; //コマンドの識別ID
    string name_; //コマンドの名前
    int mpCost; //コマンドを使うための必要なMP

    //デフォルトコンストラクタ
    CommandData() : id_(0), name_(""), mpCost(0){}
    //値を指定してコマンドを作るときのコンストラクタ
    CommandData(int id, string name, int mp) : id_(id), name_(name), mpCost(mp) {}
};