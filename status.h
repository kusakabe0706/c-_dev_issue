
#pragma once

class Status{
    private:
    int max_hp_, hp_, atk_, def_, mp_, spd_, para_turn_;
    bool is_para_, is_def_, is_counter_, is_escape_;

    public:
    //コンストラクタ
    Status();
    //ゲッター
    int get_max_hp() const;
    int getHp() const;
    int getAtk() const;
    int getDef() const;
    int getMp() const;
    int getSpd() const;
    bool get_is_para() const;
    bool get_is_def() const;
    bool get_is_counter() const;
    bool get_is_escape() const;

    //セッター
    void set_max_hp(int max_hp);
    void set_hp(int hp);
    void set_atk(int atk);
    void set_def(int def);
    void set_mp(int mp);
    void set_spd(int spd);
    void consume_mp(int c_mp);
    void set_para(bool is_para, int para_turns = 0);
    void set_is_def(bool is_def);
    void set_is_counter(bool is_counter);
    void set_is_escape(bool is_escape);
    
    //ステータスの更新
    void update_status();
};
