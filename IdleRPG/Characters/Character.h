#pragma once
#include <string>

#include "../CharacterTypeHelper.h"
using namespace CharacterTypeHelper;

namespace CharacterTypeHelper
{
  enum class CharacterType;
}

class Character
{
  public:
    virtual ~Character() = default;
  
    virtual void DeclareAttack(Character& attackedCharacter);

    std::string GetName();
    CharacterType GetType() const;
    int GetHealth() const;
    bool IsDead() const;
  
    int TakeBasicAttackDamage(Character& attackedBy, int damage);
    int TakeDamage(Character& attackedBy, int damageAmount);
    void Heal(int healAmount);

  protected:
    std::string name{};
    CharacterType type{};
    
    int currentHealth{};
    int bonusDamageAvg{0};
    int bonusDamageRange{0};
    int bonusArmour{0};
    float bonusAccuracy{0};
    float bonusEvasion{0};
    float bonusResilience{0};

    int bonusAttackCount{0};
    float bonusCriticalStrikeChance{0.0f};

    Character(std::string characterName, CharacterType characterType, int health, int damageAvg, int damageRange, int armour, float accuracy, float evasion, float resilience);
  
    int GetDamageAvg() const;
    int GetDamageRange() const;
    int GetArmour() const;
    float GetAccuracy() const;
    float GetEvasion() const;
    float GetResilience() const;
    int GetAttackCount() const;
    float GetCriticalStrikeChance() const;

    void DoAllBasicAttacks(Character& attackedCharacter);
    virtual bool DoBasicAttack(Character& attackedCharacter);

    virtual void OnTurnStart(Character& attacking){}
    virtual void OnTakeBasicAttackDamage(Character& attackedBy, int damageAmount){}
    virtual void OnTakeDamage(Character& attackedBy, int damageAmount){}
    virtual void OnEvade(Character& attackedBy){}
    virtual void OnDealBasicAttackDamage(int damageAmount){}
    virtual void OnHitAttack(Character& attacking){}
    virtual void OnMissAttack(Character& attacking){}
    virtual void OnTurnEnd(Character& attacking){}
  
  private:
    const int maxHealth{};
    const int baseDamageAvg{};
    const int baseDamageRange{};
    const int baseArmour{};
    const float baseAccuracy{};
    const float baseEvasion{};
    const float baseResilience{};

    const int baseAttackCount{1};
    const float baseCriticalStrikeChance{0.1f};
  
    int GetDamage() const;
    bool RollAccuracy() const;
    bool RollEvasion() const;
    bool RollCriticalStrike() const;
};
