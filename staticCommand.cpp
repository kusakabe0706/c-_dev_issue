#include "StaticCommand.h"
#include "Unit.h"
#include "calc.h"
#include "show.h"
#include <string>
using namespace std;

//攻撃
void StaticCommand::attack(Unit *attacker, Unit *target){
    //ステータスの取得
    int atk = attacker->getStatus()->getAtk();
    int def = target->getStatus()->getDef();
    bool isdef = target->getStatus()->get_is_def();
    //calcクラスにダメージ計算をしてもらう
    int damage;
    //画面にアクション文字を表示
    Show::displayAction(1, attacker->getName());
    //カウンターの判定
    if (target->getStatus()->get_is_counter()) {
        //敵がカウンターをつかっていた場合
        Show::addLog(target->getName() + "のカウンターが発動");
        //攻撃した本人のHPを減らす
        int current_hp = attacker->getStatus()->getHp();
        attacker->getStatus()->set_hp(current_hp - damage);

        Show::addLog(attacker->getName() + "に" + to_string(damage) + "のダメージ");
    }else {
        //普通に攻撃が当たった場合
        int current_hp = target->getStatus()->getHp();
        target->getStatus()->set_hp(current_hp - damage);

        Show::addLog(target->getName() + "に" + to_string(damage) + "のダメージ");
    }
}

//防御
void StaticCommand::guard(Unit *unit){
    //防御フラグを立てる
    unit->getStatus()->set_is_def(true);

    Show::displayAction(2, unit->getName());
}

void StaticCommand::heal(Unit *unit){
    //使用した本人のHPを20回復
    int current_hp = unit->getStatus()->getHp();
    unit->getStatus()->set_hp(current_hp + 20);

    Show::displayAction(3, unit->getName());
}

//攻撃力アップ
void StaticCommand::atk_buff(Unit *unit){
    Show::displayAction(4, unit->getName());

    //現在の攻撃力を取得し1.5倍にする
    int current_atk = unit->getStatus()->getAtk();
    int next_atk = (int)(current_atk * 1.5);

    unit->getStatus()->set_atk(next_atk);

    Show::addLog(unit->getName() + "の攻撃力が上がった");
}

//逃げる
void StaticCommand::escape(Unit *unit){
    Show::displayAction(5, unit->getName());
    //逃げるフラグを立てる
    unit->getStatus()->set_is_escape(true);

    Show::addLog(unit->getName() + "は逃げ切った");
}

//カウンター
void StaticCommand::counter(Unit *unit){
    Show::displayAction(6, unit->getName());
    //カウンターフラグを立てる
    unit->getStatus()->set_is_counter(true);

    Show::addLog(unit->getName() + "はカウンターの構えをとった");

}

//でんじは
void StaticCommand::paralyse(Unit *attacker, Unit *target){
    Show::displayAction(7, attacker->getName());
    //麻痺フラグをたて、麻痺するターンを２にする
    target->getStatus()->set_para(true, 2);

    Show::addLog(target->getName() + "は麻痺してしまった(2ターン)");
}