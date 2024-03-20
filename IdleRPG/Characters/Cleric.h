#pragma once
#include "ActivatedCharacter.h"
#include "Character.h"

class Cleric : public ActivatedCharacter
{
public:
  Cleric();

private:
  const float smiteDamageRatio = 0.3f;
  const float smiteHealRatio = 0.6f;
  
  void ActivateAbility(Character& attackedCharacter) override;
  
};