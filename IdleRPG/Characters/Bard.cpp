#include "Bard.h"

#include <iostream>

#include "../RandomHelper.h"
using namespace RandomHelper;

Bard::Bard() : Character("Bard", CharacterType::Bard, 900, 60, 10, 5, 0.9f, 0.2f, 0.2f), song()
{
}

void Bard::OnTurnStart(Character& attacking)
{
  if(isEvading)
  {
    isEvading = false;
    bonusEvasion = 0.0f;
  }
}

void Bard::OnHitAttack(Character& attacking)
{
  if(!songComplete)
  {
    const BardNoteType currentNoteType = GetNoteType();

    AddNoteToSong(currentNoteType);

    std::cout << GetSongString() << '\n';

    switch(currentNoteType)
    {
      case Sharp:
        std::cout << name << " plays a  " << GetNoteString(currentNoteType) << " dealing " << sharpDamageAmount << " damage " << '\n';
        attacking.TakeDamage(*this, sharpDamageAmount);
        break;
      case Flat:
        std::cout << name << " plays a  " << GetNoteString(currentNoteType) << " healing " << flatHealAmount << " health " << '\n';
        Heal(flatHealAmount);
        break;
    }
  }
  else
  {
    PlaySong(attacking);
  }
  
}

void Bard::OnTurnEnd(Character& attacking)
{
  if(extraAttackCounter > 0)
  {
    extraAttackCounter--;
    if(extraAttackCounter <= 0)
    {
      bonusAttackCount = 0;
    }
  }
}


std::string Bard::GetSongString() const
{
  std::string songString{};
  
  if(song[0] == Sharp)
  {
    songString += "#";
  }
  else
  {
    songString += "b";
  }

  for(int i = 1; i < currentPlaceInSong; i++)
  {
    if(song[i] == Sharp)
    {
      songString += " #";
    }
    else
    {
      songString += " b";
    }
  }

  return songString;
}

std::string Bard::GetNoteString(BardNoteType noteType)
{
  switch(noteType)
  {
    case Sharp:
      return "sharp";
    case Flat:
      return "flat";
    default:
      return "";
  }
}

Bard::BardNoteType Bard::GetNoteType()
{
  return static_cast<BardNoteType>(RandomInRange(0, 1));
}

void Bard::AddNoteToSong(BardNoteType noteType)
{
  if(currentPlaceInSong < song.size())
  {
    song[currentPlaceInSong] = noteType;
    currentPlaceInSong++;

    if(currentPlaceInSong >= song.size())
    {
      songComplete = true;
    }
  }
  else
  {
    songComplete = true;
  }
  
}

void Bard::PlaySong(Character& attacking)
{
  currentPlaceInSong = 0;
  songComplete = false;

  BardSongType songType = GetSongType();

  switch(songType)
  {
    case GreaterRestoration:
      std::cout << name << " plays the song of greater restoration, healing " << greaterRestorationAmount << " health" << '\n';
      Heal(greaterRestorationAmount);
      break;
    case LesserRestoration:
      std::cout << name << " plays the song of lesser restoration, healing " << lesserRestorationAmount << " health" << '\n';
      Heal(lesserRestorationAmount);
      break;
    case Evasion:
      std::cout << name << " plays the song of evasion, entering a defensive stance" << '\n';
      isEvading = true;
      bonusEvasion = 1.0f;
      break;
    case Misfire:
      std::cout << name << " plays the song of misfire, dealing " << misfireDamageAmount << " damage to themselves" << '\n';
      TakeDamage(*this, misfireDamageAmount);
      break;
    case Momentum:
      std::cout << name << " plays the song of momentum, allowing them to attack multiple times" << '\n';
      extraAttackCounter = 2;
      bonusAttackCount = 2;
      break;
    case Smite:
      std::cout << name << " plays the song of smite, dealing " << smiteValue << " damage and healing " << smiteValue << " health" << '\n';
      attacking.TakeDamage(*this, smiteValue);
      Heal(smiteValue);
      break;
    case LesserDamage:
      std::cout << name << " plays the song of lesser damage, gaining " << lesserDamageAmount << " damage " << '\n';
      bonusDamageAvg += lesserDamageAmount;
      break;
    case GreaterDamage:
      std::cout << name << " plays the song of greater damage, gaining " << greaterDamageAmount << " damage " << '\n';
      bonusDamageAvg += greaterDamageAmount;
      break;
  }
}

Bard::BardSongType Bard::GetSongType() const
{
  return static_cast<BardSongType>(GetSongNumber());
}

int Bard::GetSongNumber() const
{
  int currentSongNumber = 0;

  if(song[0] == Sharp) currentSongNumber += 1;
  if(song[1] == Sharp) currentSongNumber += 2;
  if(song[2] == Sharp) currentSongNumber += 4;

  return currentSongNumber;
}
