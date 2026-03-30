#include "enemy.h"
#include "commandMaster.h"
#include <random>
using namespace std;

//コンストラクタ（Unitをnで初期化し、自身のidを設定
Enemy::Enemy(int i, string n) : Unit(n), id_(i) {}

//コマンド選択
void Enemy::cmd_select(){
    //乱数生成器の初期化
    random_device rd;
    mt19937 gen(rd());

    //MPがたりるコマンドが選択されるまでループ
    while (true) {
        //敵１のコマンド
        if (id_ == 1) {
            //1~3を生成する分布器
            uniform_int_distribution<> dist(1, 3);
            //乱数を変数に入れる(ifにdist(gen)をいれると毎回乱数が生成されるため)
            int temp = dist(gen);
            if(temp == 1){
                select_cmd = CommandMaster::Getter(1);
            }else if (temp == 2) {
                select_cmd = CommandMaster::Getter(2);
            }else{
                select_cmd = CommandMaster::Getter(6);
            }
            //コマンドが決定したらループを抜ける
            break;
        }else {//敵2のコマンド選択
            uniform_int_distribution<> dist(1, 3);
            int temp = dist(gen);

            CommandData select_cmd2;
            if(temp == 1){
                select_cmd2 = CommandMaster::Getter(1);
            }else if (temp == 2) {
                select_cmd2 = CommandMaster::Getter(2);
            }else{
                select_cmd2 = CommandMaster::Getter(7);
            }
            //選択されたコマンドの消費MP以上の現在MPがあるか確認
            if(status.getMp() >= select_cmd2.mpCost){
                //コマンドを確定させる
                select_cmd = select_cmd2;
                //MPを消費
                status.consume_mp(select_cmd2.mpCost);
                //ループを抜ける
                break;
            }
        }
    }
}