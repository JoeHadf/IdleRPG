#pragma once
#include "ActivatedCharacter.h"

class Fighter : public ActivatedCharacter
{
  public:
    Fighter();

  private:
    enum FighterBuffType{CriticalStrike, AttackCount, Damage};
  
    const int totalCritBuffs{4};
    const int totalAttackBuffs{3};
    const int damageBuff{20};

    int currentCritBuffs{0};
    int currentAttackBuffs{0};
    
    void ActivateAbility(Character& attackedCharacter) override;

    static FighterBuffType GetBuffType();

    void DoCritBuff();
    void DoAttackBuff();
    void DoDamageBuff();
  
};
