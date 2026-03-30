#pragma once
//前方宣言（ポインタだけつかうので、名前だけ教える)
class Unit;

//呼ばれたコマンドを実際に実行し結果を反映する
class StaticCommand{
    public:
    //1:攻撃
    static void attack(Unit* attacker, Unit* target);
    //2:防御
    static void guard(Unit* unit);
    //3:回復
    static void heal(Unit* unit);
    //4:攻撃力アップ
    static void atk_buff(Unit* unit);
    //5:逃げる
    static void escape(Unit* unit);
    //6:カウンター
    static void counter(Unit* unit);
    //7:でんじは
    static void paralyse(Unit* attacker, Unit* target);
};