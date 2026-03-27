#include "enemy.h"
#include <random>
using namespace std;

Enemy::Enemy(int i, string n) : Unit(n), id_(i) {}

void Enemy::cmd_select(){
    random_device rd;
    mt19937 gen(rd());

    while (true) {
        if (id_ == 1) {
            uniform_int_distribution<> dist(1, 3);
            if(dist(gen) == 1){
                select_cmd = CommandData(1, "攻撃", 0);
            }else if (dist(gen) == 2) {
                select_cmd = CommandData(2, "防御", 0);
            }else{
                select_cmd = CommandData(6, "カウンター", 0);
            }
            break;
        }else {
            uniform_int_distribution<> dist(1, 3);
            CommandData select_cmd2
            if(dist(gen) == 1){
                select_cmd2 = CommandData(1, "攻撃", 0);
            }else if (dist(gen) == 2) {
                select_cmd2 = CommandData(2, "防御", 0);
            }else{
                select_cmd2 = CommandData(7, "麻痺付与", 10);
            }

            if(status.get_mp() >= select_cmd2.mp){
                select_cmd = select_cmd2;
                status.consume_mp(select_cmd2.mp);
                break;
            }
        }
    }
}