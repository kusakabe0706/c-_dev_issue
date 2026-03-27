#include "player.h"
#include <iostream>
#include <limits>
using namespace std;

Player::Player() : Unit("プレイヤー") {}

void Player::cmd_select(){
    CommandData cmds[5] = {
        CommandData(1, "攻撃" ,0),
        CommandData(2, "防御", 0),
        CommandData(3, "回復", 15),
        CommandData(4, "攻撃力アップ", 10),
        CommandData(5, "逃げる", 0)
    };

    while (true) {
        int select;
        if(cin >> select && select >= 1 && select <= 5){
            CommandData selected = cmds[select - 1];
            if(status.get_mp() >= selected.mp){
                select_cmd = selected;
                status.consume_mp(selected.mp);
                break;
            }else{
                cout << "MPが足りません" << endl;
            }
        }else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Player::enemy_select(vector<Unit*>& enemies){
    vector<Unit*> alive_enemies;
    for(auto* e : enemies){
        if(e->is_alive()) alive_enemies.push_back(e);
    }

    cout << "ターゲットを選択" << endl;
    for(size_t i = 0; i < alive_enemies.size(); ++i){
        cout << i + 1 << ":" << alive_enemies[i]->get_name() << endl;
    }

    int idx;
    while (true) {
        if(cin >> idx && idx >= 1 && idx <= (int)alive_enemies.size()){
            target = alive_enemies[idx - 1];
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

}