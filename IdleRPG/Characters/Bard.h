#pragma once
#include <array>

#include "Character.h"

class Bard : public Character
{
  public:
    Bard();

  protected:
    void OnTurnStart(Character& attacking) override;
    void OnHitAttack(Character& attacking) override;
    void OnTurnEnd(Character& attacking) override;
    

  private:
    enum BardNoteType {Sharp, Flat};
    enum BardSongType {GreaterRestoration, LesserRestoration, Evasion, Misfire, Momentum, Smite, LesserDamage, GreaterDamage};
  
    bool isEvading{false};
    int extraAttackCounter{0};

    int sharpDamageAmount = 50;
    int flatHealAmount = 50;

    int greaterRestorationAmount = 450;
    int lesserRestorationAmount = 225;
    int misfireDamageAmount = 30;
    int smiteValue = 200;
    int lesserDamageAmount = 50;
    int greaterDamageAmount = 100;

    std::array<BardNoteType, 3> song;
    size_t currentPlaceInSong = 0;
    bool songComplete = false;

    std::string GetSongString() const;
    static std::string GetNoteString(BardNoteType noteType);
    static BardNoteType GetNoteType();
    void AddNoteToSong(BardNoteType noteType);
    void PlaySong(Character& attacking);
    BardSongType GetSongType() const;
    int GetSongNumber() const;
    
};
