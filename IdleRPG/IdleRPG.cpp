#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "RandomHelper.h"
#include "Characters/Character.h"
#include "Characters/Cleric.h"
#include "Characters/Fighter.h"
#include "Characters/Barbarian.h"
#include "Characters/Bard.h"
#include "Characters/Druid.h"
#include "Characters/Monk.h"

enum class WinType {Player1, Player2, Draw};

Character* GetCharacter(CharacterType character)
{
    switch(character)
    {
        case CharacterType::Artificer:
            break;
        case CharacterType::Barbarian:
            return new Barbarian();
        case CharacterType::Bard:
            return new Bard();
        case CharacterType::Cleric:
            return new Cleric();
        case CharacterType::Druid:
            return new Druid();
        case CharacterType::Fighter:
            return new Fighter();
        case CharacterType::Monk:
            return new Monk();
        case CharacterType::Paladin:
            break;
        case CharacterType::Ranger:
            break;
        case CharacterType::Rogue:
            break;
        case CharacterType::Sorcerer:
            break;
        case CharacterType::Warlock:
            break;
        case CharacterType::Wizard:
            break;
    }
    return new Fighter();
}

WinType DoFight(CharacterType player1Character, CharacterType player2Character)
{
    const int playerGoingFirst = RandomHelper::RandomInRange(1,2);

    const CharacterType goFirstType = (playerGoingFirst == 1) ? player1Character : player2Character;
    const CharacterType goSecondType = (playerGoingFirst == 1) ? player2Character : player1Character;

    Character* goFirstPlayer = GetCharacter(goFirstType);
    Character* goSecondPlayer = GetCharacter(goSecondType);

    bool fightIsOngoing = true;
    
    while(fightIsOngoing)
    {
        std::cout << goFirstPlayer->GetName() << ": " << goFirstPlayer->GetHealth() << '\n';
        std::cout << goSecondPlayer->GetName() << ": " << goSecondPlayer->GetHealth() << '\n';
        std::cout << '\n';
        
        goFirstPlayer->DeclareAttack((*goSecondPlayer));
        fightIsOngoing = !goFirstPlayer->IsDead() && ! goSecondPlayer->IsDead();

        if(fightIsOngoing)
        {
            goSecondPlayer->DeclareAttack((*goFirstPlayer));
            fightIsOngoing = !goFirstPlayer->IsDead() && ! goSecondPlayer->IsDead();
        }
    }

    WinType winType;

    if(goFirstPlayer->IsDead() && goSecondPlayer->IsDead())
    {
        winType = WinType::Draw;
    }
    else if(goSecondPlayer->IsDead())
    {
        if(playerGoingFirst == 1)
        {
            winType = WinType::Player1;
        }
        else
        {
            winType = WinType::Player2;
        }
    }
    else
    {
        if(playerGoingFirst == 1)
        {
            winType = WinType::Player2;
        }
        else
        {
            winType = WinType::Player1;
        }
    }

    delete goFirstPlayer;
    delete goSecondPlayer;

    return winType;
}

float DoFightSet(CharacterType player1Type, CharacterType player2Type)
{
    int player1Count = 0;
    int player2Count = 0;
    int drawCount = 0;

    int gameCount = 1000;

    for(int i = 0; i < gameCount; i++)
    {
        WinType winner = DoFight(player1Type, player2Type);

        if(winner == WinType::Player1)
        {
            player1Count++;
        }
        else if(winner == WinType::Player2)
        {
            player2Count++;
        }
        else
        {
            drawCount++;
        }
    }

    float player1WinRate = (100 * player1Count) / static_cast<float>(gameCount);

    std::cout << "Player 1: " << (100 * player1Count) / static_cast<float>(gameCount) << "%" << '\n';
    std::cout << "Player 2: " << (100 * player2Count) / static_cast<float>(gameCount) << "%" <<'\n';
    std::cout << "Draws: " << (100 * drawCount) / static_cast<float>(gameCount) << "%" <<'\n';

    return player1WinRate;
}

std::string GetWinRateString(float winRate)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << winRate;
    std::string mystring = ss.str();

    if(winRate < 10)
    {
        mystring = "0" + mystring;
    }

    mystring = mystring + "%";
    
    return mystring;
}

void PrintWinRateTable()
{
    const int minTypeID = 1;
    const int maxTypeID = 6;

    const int numberOfTypes = maxTypeID - minTypeID + 1;
    
    std::string winRates[numberOfTypes][numberOfTypes];

    for(int i = 1; i <= numberOfTypes; i++)
    {
        const CharacterType player1Type = static_cast<CharacterType>(i);

        winRates[i-1][i-1] = "____";
        
        for(int j = i+1; j <= numberOfTypes; j++)
        {
            const CharacterType player2Type = static_cast<CharacterType>(j);
            
            if(i != j)
            {
                const float player1WinRate = DoFightSet(player1Type, player2Type);
                winRates[i-1][j-1] = GetWinRateString(player1WinRate);
                winRates[j-1][i-1] = GetWinRateString(100 - player1WinRate);
            }
        }
    }

    for(int i = 0; i < numberOfTypes; i++)
    {
        for(int j = 0; j < numberOfTypes; j++)
        {
            std::cout << winRates[i][j] << " ";
        }
        
        std::cout << '\n';
    }
}

int main(int argc, char* argv[])
{
    srand(1);

    //DoFight(CharacterType::Bard, CharacterType::Cleric);

    PrintWinRateTable();

    return 0;
}
