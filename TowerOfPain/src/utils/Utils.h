#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <Tinyfont.h>

#include "const/Map.h"
#include "const/Common.h"
#include "const/Character.h"
#include "const/MiniCharacter.h"
#include "const/Lines.h"
#include "const/Title.h"

struct Utils
{
  Arduboy2 *arduboy;

  bool sound;
  bool music;
  uint8_t cycle;
  uint8_t musicalLullaby[10] = {0, 1, 0, 1, 1, 0, 1, 1, 1, 0};
  uint8_t lullaby = 0;

  void init(Arduboy2 *arduboy)
  {
    this->arduboy = arduboy;

    cycle = 10;
    sound = false;
    music = false;
  }

  void tick(ArduboyTones *soundtones)
  {
    cycle--;
    if (cycle < 1)
    {
      lullaby++;
      if (lullaby == 11)
      {
        lullaby = 0;
      }
      doBeep(soundtones);
      cycle = 10;
    }
  }

  void doBeep(ArduboyTones *soundtones)
  {
    if (musicalLullaby[lullaby] == 1 && music)
    {
      soundtones->tone(150, 50);
    }
  }

  void koBeep(ArduboyTones *soundtones)
  {
    soundtones->tone(250, 50);
  }

  void okBeep(ArduboyTones *soundtones)
  {
    soundtones->tone(700, 50);
  }

  uint8_t sizeTypeAbs(uint8_t a, uint8_t b)
  {
    return a < b ? b - a : a - b;
  }
};

#include "Stats.h"
#include "Text.h"
