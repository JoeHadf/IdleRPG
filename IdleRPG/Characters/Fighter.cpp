#include "Fighter.h"

#include <iostream>

#include "../RandomHelper.h"
using namespace RandomHelper;

Fighter::Fighter() : ActivatedCharacter("Fighter", CharacterType::Fighter, 1000, 120, 30, 10, 0.9f, 0.25f, 0.1f,5)
{
      
}

void Fighter::ActivateAbility(Character& attackedCharacter)
{
  const FighterBuffType buffType = GetBuffType();

  switch(buffType)
  {
    case CriticalStrike:
      if(currentCritBuffs < totalCritBuffs)
      {
        DoCritBuff();
      }
      else
      {
        DoDamageBuff();
      }
      break;
    case AttackCount:
      if(bonusAttackCount < totalAttackBuffs)
      {
        DoAttackBuff();
      }
      else
      {
        DoDamageBuff();
      }
      break;
    case Damage:
      DoDamageBuff();
      break;
  }
}

Fighter::FighterBuffType Fighter::GetBuffType()
{
  return static_cast<FighterBuffType>(RandomInRange(0, 2));
}

void Fighter::DoCritBuff()
{
  currentCritBuffs++;
  bonusCriticalStrikeChance = currentCritBuffs * (1 / static_cast<float>(totalCritBuffs));
}

void Fighter::DoAttackBuff()
{
  bonusAttackCount++;
}

void Fighter::DoDamageBuff()
{
  bonusDamageAvg += damageBuff;
}


