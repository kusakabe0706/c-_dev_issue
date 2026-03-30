
#pragma once

class Status{
    private:
    //最大HP、現在のHP、攻撃力、防御力、MP、素早さ、麻痺が続く残りターン
    int max_hp_, hp_, atk_, def_, mp_, spd_, para_turn_;
    //麻痺しているか、防御の構えをとっているか、カウンターの構えをとっているか、にげることができたか
    bool is_para_, is_def_, is_counter_, is_escape_;

    public:
    //コンストラクタ
    Status();
    
    //ゲッター（現在の値を確認する）
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

    //セッター（値を上書き）
    void set_max_hp(int max_hp);
    void set_hp(int hp); 
    void set_atk(int atk);
    void set_def(int def);
    void set_mp(int mp);
    void set_spd(int spd);

    //MPを消費する（0未満にはならない）
    void consume_mp(int c_mp);

    //異常状態フラグのON/OFF
    void set_para(bool is_para, int para_turns = 0);
    void set_is_def(bool is_def);
    void set_is_counter(bool is_counter);
    void set_is_escape(bool is_escape);

    //ターン終了時の処理
    //1ターンで切れる構えを解除し、麻痺の残りターンを減らす
    void update_status();
};
