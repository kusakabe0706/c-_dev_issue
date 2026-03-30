#include "player.h"
#include "show.h"
#include "commandMaster.h"
#include <iostream>
#include <limits>
using namespace std;

Player::Player() : Unit("プレイヤー") {
    //プレイヤーのidをセット
    skillid = {1, 2, 3, 4, 5};
}

void Player::cmd_select(){
    while (true) {
        int selectid = Show::displayCommandList(skillid);

        CommandData select = CommandMaster::Getter(selectid);

        if (status.getMp() >= select.mpCost) {
            select_cmd = select;
            status.consume_mp(select.mpCost);
            break;
        }else {
            Show::addLog("MPが足りません");
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