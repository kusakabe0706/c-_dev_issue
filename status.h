
#pragma once
using namespace std;

class Status{
    private:
    int max_hp_, hp_, atk_, def_, mp_, spd_, para_turn_;
    bool is_para_, is_def_, is_atk_buff_;

    public:
    Status();
    int get_max_hp() const;
    int get_hp() const;
    int get_atk() const;
    int get_def() const;
    int get_mp() const;
    int get_spd() const;
    bool get_is_para() const;
    bool get_is_def() const;

    void set_max_hp(int max_hp);
    void set_hp(int hp);
    void set_atk(int atk);
    void set_def(int def);
    void set_mp(int mp);
    void set_spd(int spd);
    void consume_mp(int c_mp);
    void set_para(bool is_para, int para_turns = 0);
    void set_id_def(bool is_def);
    
    void update_status();
}
