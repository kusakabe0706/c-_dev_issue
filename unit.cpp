#include "unit.h"
#include <random>
using namespace std;

Unit::Unit(string nm) : name(nm), target(nullptr){
    random_status();
}

string Unit::getName() const {return name;}
Status* Unit::getStatus() {return &status;}
CommandData Unit::getSelectCmd() const {return select_cmd;}
Unit* Unit::get_target() const {return target;}

void Unit::set_target(Unit* t) {target = t;}

bool Unit::is_alive() const {return status.getHp() > 0;}

void Unit::random_status(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> hp_dist(50, 100);
    uniform_int_distribution<> atk_dist(20, 30);
    uniform_int_distribution<> def_dist(5, 15);
    uniform_int_distribution<> mp_dist(20, 50);
    uniform_int_distribution<> spd_dist(10, 50);

    status.set_max_hp(hp_dist(gen));
    status.set_hp(status.get_max_hp());
    status.set_atk(atk_dist(gen));
    status.set_def(def_dist(gen));
    status.set_mp(mp_dist(gen));
    status.set_spd(spd_dist(gen));
};