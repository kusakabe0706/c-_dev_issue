#include "Player.h"
#include "show.h"
#include "CommandMaster.h"
#include <iostream>
#include <limits>
using namespace std;

//コンストラクタ
Player::Player() : Unit("プレイヤー") {
    //プレイヤーの技のidをセット
    skillid = {1, 2, 3, 4, 5};
}

//コマンド選択
void Player::cmd_select(){
    //MPが足りるコマンドを選ぶまでループ
    while (true) {
        //showクラスのuiを呼び出し、ユーザが選んだ技のidを受け取る
        int selectid = Show::displayCommandList(skillid);
        //選ばれたidをつかって、技を取り出す
        CommandData select = CommandMaster::Getter(selectid);
        //現在のMPが、技の消費mp以上あるかチェック
        if (status.getMp() >= select.mpCost) {
            //足りていればコマンド確定
            select_cmd = select;
            status.consume_mp(select.mpCost);
            break;
        }else {
            //足りない場合はログを出してやり直し
            Show::addLog("MPが足りません");
        }
    }
}

//攻撃対象の選択
void Player::enemy_select(vector<Unit*>& enemies){
    vector<Unit*> alive_enemies;
    //生きている敵だけをalive_enemiesに集める
    for(auto* e : enemies){
        if(e->is_alive()) alive_enemies.push_back(e);
    }

    cout << "ターゲットを選択" << endl;
    for(size_t i = 0; i < alive_enemies.size(); ++i){
        cout << i + 1 << ":" << alive_enemies[i]->getName() << endl;
    }

    int idx;
    //正しい数字が入力されるまでループ
    while (true) {
        //cinで数字を受け取り、それが１～生きている敵の数の間かチェック
        if(cin >> idx && idx >= 1 && idx <= (int)alive_enemies.size()){
            //選ばれた敵をターゲットとしてロックオンする
            target = alive_enemies[idx - 1];
            break;
        }
        //変な文字が入力された時のエラーリセット処理
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

}