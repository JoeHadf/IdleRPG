#pragma once
#include "Character.h"

class ActivatedCharacter : public Character
{
  public:
    ActivatedCharacter(const std::string& name, CharacterType type, int health, int damageAvg, int damageRange, int armour, float accuracy,
                        float evasion, float resilience, int abilityThreshold);

    void DeclareAttack(Character& attackedCharacter) override;

  protected:
    int abilityCharge{0};
    int abilityThreshold{};
    bool canGainCharge{true};

    virtual void ActivateAbility(Character& attackedCharacter) = 0;

    bool DoBasicAttack(Character& attackedCharacter) override;
};
