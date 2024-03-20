#pragma once
#include "ActivatedCharacter.h"

class Barbarian : public ActivatedCharacter
{
public:
  Barbarian();

private:
  const int rageBonusDamage = 50;
  const float rageBonusAccuracy = 0.3f;
  const float rageBonusResilience = 0.2f;
  
  bool isRaging{false};
  bool canContinueRage{false};
  
  void ActivateAbility(Character& attackedCharacter) override;
  
  void OnTurnStart(Character& attacking) override;
  void OnTakeDamage(Character& attackedBy, int damageAmount) override;
  void OnDealBasicAttackDamage(int damageAmount) override;

  void OnEnterRage();
  void OnExitRage();
};

