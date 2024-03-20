#include "Barbarian.h"

#include <iostream>

Barbarian::Barbarian() : ActivatedCharacter("Barbarian", CharacterType::Barbarian,1100, 120, 100, 0, 0.6f, 0.1f, 0.3f,3)
{
      
}

void Barbarian::ActivateAbility(Character& attackedCharacter)
{
  std::cout << name << " begins to rage" << '\n';
  isRaging = true;
  OnEnterRage();
}

void Barbarian::OnTurnStart(Character& attacking)
{
  if(isRaging && !canContinueRage)
  {
    std::cout << name << " calms down" << '\n';
    isRaging = false;
    OnExitRage();
  }

  canContinueRage = false;
}

void Barbarian::OnTakeDamage(Character& attackedBy, int damageAmount)
{
  canContinueRage = true;
}

void Barbarian::OnDealBasicAttackDamage(int damageAmount)
{
  canContinueRage = true;
}

void Barbarian::OnEnterRage()
{
  canGainCharge = false;
  bonusDamageAvg = rageBonusDamage;
  bonusAccuracy = rageBonusAccuracy;
  bonusResilience = rageBonusResilience;
}

void Barbarian::OnExitRage()
{
  canGainCharge = true;
  bonusDamageAvg = 0;
  bonusAccuracy = 0.0f;
  bonusResilience = 0.0f;
}


