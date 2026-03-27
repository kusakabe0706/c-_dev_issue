#include "unit.h"
#include <random>
using namespace std;

Unit::Unit(string nm) : name(nm), target(nullptr){
    random_status();
}

string Unit::get_name() const {return name;}
Status& Unit::get_status() {return status;}
CommandData Unit::get_select_cmd() const {return select_cmd;}
Unit* Unit::get_target() const {return target;}

void Unit::set_target(Unit* t) {target = t}

bool Unit::is_alive() const {return status.get_hp() > 0;}

void Unit::random_status(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> hp_dist(50, 100);
    uniform_int_distribution<> atk_dist();
    uniform_int_distribution<> def_dist();
    uniform_int_distribution<> mp_dist();
    uniform_int_distribution<> spd_dist();

    status.set_max_hp(hp_dist(gen));
    status.set_hp(status.get_max_hp());
    status.set_atk(atk_dist(gen));
    status.set_def(def_dist(gen));
    status.set_mp(mp_dist(gen));
    status.set_spd(spd_dist(gen));
};