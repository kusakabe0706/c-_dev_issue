
#pragma once
#include <string>
#include "Status.h"
#include "CommandData.h"

class Unit{
    protected://子クラスからは自由に触れる変数
    std::string name; //キャラの名前
    Status status;  //HPや攻撃力などのステータス情報
    CommandData select_cmd; //そのターンに選んだ行動
    Unit* target; //攻撃を仕掛ける相手

    public:
    //コンストラクタ(名前を決めて生成)
    Unit(std::string nm);
    //仮想デストラクタ
    virtual ~Unit() = default;

    //ゲッター
    std::string getName() const; 
    Status* getStatus(); //ステータスを触るためのポインタを渡す
    CommandData getSelectCmd() const; //選んだコマンドを確認
    Unit* get_target() const; //今誰を狙っているか確認

    //セッター
    void set_target(Unit* t); //狙う相手をセットする

    //生存判定
    bool is_alive() const;

    //コマンドを選択
    virtual void cmd_select() = 0; //子クラスに必ず作らせる

    //生成された瞬間にステータスをランダムで決める
    void random_status();
};
