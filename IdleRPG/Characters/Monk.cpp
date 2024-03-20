#include "Monk.h"

#include <iostream>

Monk::Monk() : ActivatedCharacter("Monk", CharacterType::Monk,1000, 130, 30, 0, 0.8f, 0.3f, 0.3f,5)
{
}

void Monk::OnTurnStart(Character& attacking)
{
  if(isEvading)
  {
    isEvading = false;
    bonusEvasion = 0.0f;
  }
}

void Monk::OnEvade(Character& attackedBy)
{
  isDoingFlurryOfBlows = true;
}

void Monk::OnTurnEnd(Character& attacking)
{
  if(isDoingFlurryOfBlows)
  {
    isDoingFlurryOfBlows = false;

    bonusDamageAvg = -flurryOfBlowsReducedDamage;

    std::cout << name << " performs a flurry of blows" <<'\n';

    DoBasicAttack(attacking);
    DoBasicAttack(attacking);

    bonusDamageAvg = 0;
  }
}

void Monk::ActivateAbility(Character& attackedCharacter)
{
  isEvading = true;
  bonusEvasion = 1.0f;

  std::cout << name << " prepares to evade" <<'\n';
}
