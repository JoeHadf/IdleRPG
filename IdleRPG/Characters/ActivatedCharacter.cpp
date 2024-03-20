#include "ActivatedCharacter.h"

#include <iostream>

ActivatedCharacter::ActivatedCharacter(const std::string& characterName, CharacterType characterType, int health, int damageAvg,
  int damageRange, int armour, float accuracy, float evasion, float resilience, int abilityThreshold):
  Character(characterName, characterType, health, damageAvg, damageRange, armour, accuracy, evasion, resilience),
  abilityThreshold{abilityThreshold}
{
}

void ActivatedCharacter::DeclareAttack(Character& attackedCharacter)
{
  OnTurnStart(attackedCharacter);

  if(abilityCharge >= abilityThreshold)
  {
    abilityCharge = 0;
    ActivateAbility(attackedCharacter);

    std::cout << '\n';
  }
  
  std::cout << name << " declares an attack on " << attackedCharacter.GetName() << '\n';

  DoAllBasicAttacks(attackedCharacter);

  OnTurnEnd(attackedCharacter);
  
  std::cout << '\n';
}

bool ActivatedCharacter::DoBasicAttack(Character& attackedCharacter)
{
  const bool hitAttack = Character::DoBasicAttack(attackedCharacter);
  if(hitAttack && canGainCharge) abilityCharge++;

  return hitAttack;
}