#pragma once
#include "ActivatedCharacter.h"

class Druid : public ActivatedCharacter
{
  public:
    Druid();
  
  private:
    std::string owlbearName = "Owlbear";
    int owlbearBonusDamage = 200;
    int owlbearBonusArmour = 30;
    float owlbearBonusResilience = 0.6f;

  void ActivateAbility(Character& attackedCharacter) override;
    
};
