#include "status.h"
#include <algorithm>
using namespace std;

Status::Status(){
    max_hp_ = 0;
    hp_ = 0;
    atk_ = 0;
    def_ = 0;
    mp_ = 0;
    spd_ = 0;
    para_turn_ = 0;
    is_para_ = false;
    is_atk_buff_ = false;
    is_def_ = false;
}

int Status::get_max_hp() const {return max_hp_;}
int Status::get_hp() const {return hp_;}
int Status::get_atk() const {return atk_;}
int Status::get_def() const {return def_;}
int Status::get_mp() const {return mp_;}
int Status::get_spd() const {return spd_;}
bool Status::get_is_para() const {return is_para_;}
bool Status::get_is_def() const {return is_def_;}

void Status::set_max_hp(int max_hp) {max_hp_ = max_hp;}
void Status::set_hp(int hp) {hp_ = max(0, min(hp, max_hp_));}
void Status::set_atk(int atk) {atk_ = atk;}
void Status::set_def(int def) {def_ = def;}
void Status::set_mp(int mp) {mp_ = max(0, mp);}
void Status::consume_mp(int c_mp) {mp_ = max(0, mp_ - c_mp);}
void Status::set_spd(int spd) {spd_ = spd;}
void Status::set_id_def(bool is_def) {is_def_ = is_def;}
void Status::set_para(bool is_para, int para_turns) {is_para_ = is_para; para_turn_ = para_turns;}

void Status::update_status(){
    is_def_ = false;
    if (para_turn_ > 0) {
        para_turn_--;
        if (para_turn_ == 0) {
            is_para_ = false;
        }
    }
}
