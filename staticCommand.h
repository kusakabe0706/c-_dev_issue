#pragma once

class Unit;

class StaticCommand{
    public:
    static void attack(Unit* attacker, Unit* target);

    static void guard(Unit* unit);

    static void heal(Unit* unit);

    static void atk_buff(Unit* unit);

    static void escape(Unit* unit);

    static void counter(Unit* unit);

    static void paralyse(Unit* attacker, Unit* target);
};