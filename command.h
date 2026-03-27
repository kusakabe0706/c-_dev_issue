#pragma once
#include "unit.h"
using namespace std;

class Unit;

class Command{
    public:
    static void attack(Unit* attacker, Unit* target);
    static void guard(Unit* unit);
    static void heal(Unit* unit);
    static void buff(Unit* unit);
    static void escape();
    static void counter(Unit* unit);
    static void paralyse(Unit* attacker, Unit* target);
};