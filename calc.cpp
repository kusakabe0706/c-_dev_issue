#include "Calc.h"
#include "Unit.h"
#include "Status.h"
#include "Command.h"
#include <algorithm>

int Calc::getRandom(int min, int max)
{
    if (min > max) return min;
    return min + (rand() % (max - min + 1));
}

int Calc::calculateDamage(Unit* attacker, Unit* target, const CommandData& cmd)
{
    int atk = attacker->getStatus()->getAtk();
    int def = target->getStatus()->getDef();
    int Damage = atk - def ;

    // 攻撃バフ判定
    if (attacker->getStatus()->getAtkBuff())
    {
        Damage = static_cast<int>(Damage * 1.5);
    }

    // 防御判定
    if (target->getStatus()->getGuard())
    {
        Damage /= 2;
    }

    return std::max(1, Damage);
}

int Calc::calculateCounterDamage(int receivedDamage)
{
    return static_cast<int>(receivedDamage * 1.5);
}