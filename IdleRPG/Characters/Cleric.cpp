#include "Cleric.h"

#include <iostream>

Cleric::Cleric() : ActivatedCharacter("Cleric", CharacterType::Cleric,1200, 60, 20, 15, 0.90f, 0.05f, 0.5f,3)
{
      
}

void Cleric::ActivateAbility(Character& attackedCharacter)
{
  const int attackedCharacterHealth = attackedCharacter.GetHealth();

  const int smiteDamage = floor(smiteDamageRatio * attackedCharacterHealth);
  const int smiteHeal = ceil(smiteHealRatio * smiteDamage);

  std::cout << name << " smites " << attackedCharacter.GetName() << " dealing " << smiteDamage << " damage and healing " << smiteHeal << " health" <<'\n';

  attackedCharacter.TakeDamage(*this, smiteDamage);
  Heal(smiteHeal);
}
