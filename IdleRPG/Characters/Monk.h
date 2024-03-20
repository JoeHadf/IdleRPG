#pragma once
#include "ActivatedCharacter.h"

class Monk : public ActivatedCharacter
{
  public:
    Monk();

  protected:
    void OnTurnStart(Character& attacking) override;
    void OnEvade(Character& attackedBy) override;
    void OnTurnEnd(Character& attacking) override;

  private:
    bool isEvading{false};
    bool isDoingFlurryOfBlows{false};

    int flurryOfBlowsReducedDamage{50};
  
    void ActivateAbility(Character& attackedCharacter) override;
  
};
