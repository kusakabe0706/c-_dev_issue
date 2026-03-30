#include "staticCommand.h"
#include "unit.h"
#include "calc.h"
#include "show.h"
#include <string>
using namespace std;

void StaticCommand::attack(Unit *attacker, Unit *target){
    //ステータスの取得
    int atk = attacker->getStatus()->getAtk();
    int def = target->getStatus()->getDef();
    bool isdef = target->getStatus()->get_is_def();

    int damage;

    Show::displayAction(1, attacker->getName());

    if (target->getStatus()->get_is_counter()) {
        Show::addLog(target->getName() + "のカウンターが発動");

        int current_hp = attacker->getStatus()->getHp();
        attacker->getStatus()->set_hp(current_hp - damage);

        Show::addLog(attacker->getName() + "に" + to_string(damage) + "のダメージ");
    }else {
        int current_hp = target->getStatus()->getHp();
        target->getStatus()->set_hp(current_hp - damage);

        Show::addLog(target->getName() + "に" + to_string(damage) + "のダメージ");
    }
}

void StaticCommand::guard(Unit *unit){
    unit->getStatus()->set_is_def(true);

    Show::displayAction(2, unit->getName());
}

void StaticCommand::heal(Unit *unit){
    int current_hp = unit->getStatus()->getHp();
    unit->getStatus()->set_hp(current_hp + 20);

    Show::displayAction(3, unit->getName());
}

void StaticCommand::atk_buff(Unit *unit){
    Show::displayAction(4, unit->getName());

    int current_atk = unit->getStatus()->getAtk();
    int next_atk = (int)(current_atk * 1.5);

    unit->getStatus()->set_atk(next_atk);

    Show::addLog(unit->getName() + "の攻撃力が上がった");
}

void StaticCommand::escape(Unit *unit){
    Show::displayAction(5, unit->getName());

    unit->getStatus()->set_is_escape(true);

    Show::addLog(unit->getName() + "は逃げ切った");
}

void StaticCommand::counter(Unit *unit){
    Show::displayAction(6, unit->getName());

    unit->getStatus()->set_is_counter(true);

    Show::addLog(unit->getName() + "はカウンターの構えをとった");

}

void StaticCommand::paralyse(Unit *attacker, Unit *target){
    Show::displayAction(7, attacker->getName());

    target->getStatus()->set_para(true, 2);

    Show::addLog(target->getName() + "は麻痺してしまった(2ターン)");
}