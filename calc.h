#ifndef CALC_H
#define CALC_H

class Unit;
struct CommandData;

class Calc
{
public:
    Calc() = delete;

    static int getRandom(int min, int max);
    static int calculateDamage(Unit* attacker, Unit* target, const CommandData& cmd);
    static int calculateCounterDamage(int receivedDamage);
};

#endif