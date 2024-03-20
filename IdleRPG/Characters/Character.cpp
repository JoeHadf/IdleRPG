#include "Character.h"

#include <algorithm>
#include <iostream>

#include "../RandomHelper.h"
using namespace RandomHelper;

#include "../ClampHelper.h"
using namespace ClampHelper;

#include "../CharacterTypeHelper.h"
using namespace CharacterTypeHelper;

void Character::DeclareAttack(Character& attackedCharacter)
{
  OnTurnStart(attackedCharacter);
  
  std::cout << name << " declares an attack on " << attackedCharacter.GetName() << '\n';

  DoAllBasicAttacks(attackedCharacter);

  OnTurnEnd(attackedCharacter);
  
  std::cout << '\n';
}

std::string Character::GetName()
{
  return name;
}

CharacterType Character::GetType() const
{
  return type;
}

int Character::GetHealth() const
{
  return currentHealth;
}

bool Character::IsDead() const
{
  return currentHealth <= 0;
}

int Character::TakeBasicAttackDamage(Character& attackedBy, int damage)
{
  if(!RollEvasion())
  {
    const int damageAmount = TakeDamage(attackedBy, damage);

    if(damageAmount > 0)
    {
      OnTakeBasicAttackDamage(attackedBy, damageAmount);
    }

    return damage;
  }

  std::cout << name << " evades" << '\n';

  OnEvade(attackedBy);
  return 0;
}

int Character::TakeDamage(Character& attackedBy, int damageAmount)
{
  damageAmount -= GetArmour();
  damageAmount = ceil(damageAmount * (1.0f - GetResilience()));

  std::cout << name << " reduces the damage to " << damageAmount << '\n';

  currentHealth -= damageAmount;

  OnTakeDamage(attackedBy, damageAmount);

  return damageAmount;
}

void Character::Heal(int healAmount)
{
  const int defaultHealing = currentHealth + healAmount;
  
  if(defaultHealing > maxHealth)
  {
    currentHealth = maxHealth;
  }
  else
  {
    currentHealth = defaultHealing;
  }
}

Character::Character(std::string characterName, CharacterType characterType, int health, int damageAvg, int damageRange, int armour, float accuracy,
                     float evasion, float resilience):
  name{std::move(characterName)},
  type{characterType},
  maxHealth{health},
  baseDamageAvg{damageAvg},
  baseDamageRange{damageRange},
  baseArmour{armour},
  baseAccuracy{accuracy},
  baseEvasion{evasion},
  baseResilience{resilience}
  {
    currentHealth = health;
  }

int Character::GetDamageAvg() const
{
  return std::max(baseDamageAvg + bonusDamageAvg, 0);
}

int Character::GetDamageRange() const
{
  const int maxRange = 2 * GetDamageAvg();
  return Clamp(baseDamageRange + bonusDamageRange, 0, maxRange);
}

int Character::GetArmour() const
{
  return std::max(baseArmour + bonusArmour, 0);
}

float Character::GetAccuracy() const
{
  return Clamp(baseAccuracy + bonusAccuracy, 0.0f, 1.0f);
}

float Character::GetEvasion() const
{
  return Clamp(baseEvasion + bonusEvasion, 0.0f, 1.0f);
}

float Character::GetResilience() const
{
  return Clamp(baseResilience + bonusResilience, 0.0f, 1.0f);
}

int Character::GetAttackCount() const
{
  return std::max(baseAttackCount + bonusAttackCount, 1);
}

float Character::GetCriticalStrikeChance() const
{
  return Clamp(baseCriticalStrikeChance + bonusCriticalStrikeChance, 0.0f, 1.0f);
}

void Character::DoAllBasicAttacks(Character& attackedCharacter)
{
  const int basicAttackCount = GetAttackCount();
  
  for(int i = 0; i < basicAttackCount; i++)
  {
    DoBasicAttack(attackedCharacter);
  }
}

int Character::GetDamage() const
{
  const int damageAvg = GetDamageAvg();
  const int damageRange = GetDamageRange();
  
  const int halfRange = damageRange / 2;
  const int minDecrement = damageRange % 2;
  const int damageAmount = RandomInRange(damageAvg - halfRange - minDecrement, damageAvg + halfRange);
  
  return damageAmount;
}

bool Character::RollAccuracy() const
{
  const float randomValue = RandomInRange(0.0f,1.0f);
  return randomValue < GetAccuracy();
}

bool Character::RollEvasion() const
{
  const float randomValue = RandomInRange(0.0f,1.0f);
  return randomValue < GetEvasion();
}

bool Character::RollCriticalStrike() const
{
  const float randomValue = RandomInRange(0.0f,1.0f);
  return randomValue < GetCriticalStrikeChance();
}

bool Character::DoBasicAttack(Character& attackedCharacter)
{
  if(RollAccuracy())
  {
    int damage = GetDamage();

    if(RollCriticalStrike())
    {
      damage *= 2;
      std::cout << name << " CRITICALLY STRIKES for " << damage << " damage" << '\n';
    }
    else
    {
      std::cout << name << " hits for " << damage << " damage" << '\n';
    }
    
    if(damage > 0)
    {
      const int damageDone = attackedCharacter.TakeBasicAttackDamage(*this, damage);

      OnHitAttack(attackedCharacter);
      if(damageDone > 0)
      {
        OnDealBasicAttackDamage(damageDone);
      }
    }
    
    return true;
  }
  
  OnMissAttack(attackedCharacter);
  std::cout << name << " misses" << '\n';
  return false;
}
