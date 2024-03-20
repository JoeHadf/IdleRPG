#include "Druid.h"

#include <iostream>

Druid::Druid() : ActivatedCharacter("Druid", CharacterType::Druid,700, 70, 20, 10, 0.8f, 0.3f, 0.2f,10)
{
}

void Druid::ActivateAbility(Character& attackedCharacter)
{
  std::cout << name << " transforms into an owlbear" << '\n';
  
  canGainCharge = false;

  name = owlbearName;
  bonusDamageAvg = owlbearBonusDamage;
  bonusArmour = owlbearBonusArmour;
  bonusResilience = owlbearBonusResilience;
}


