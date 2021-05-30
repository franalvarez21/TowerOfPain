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
  uint8_t music;
  uint8_t cycle;
  uint8_t musicalLullaby[4][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 1, 2, 0, 1, 1, 2, 0}, {0, 1, 2, 0, 1, 2, 0, 1, 1, 2}, {0, 0, 0, 1, 0, 0, 1, 0, 0, 1}};
  uint8_t lullaby = 0;

  void init(Arduboy2 *arduboy)
  {
    this->arduboy = arduboy;

    cycle = 10;
    sound = false;
    music = 0;
  }

  void tick(ArduboyTones *soundtones)
  {
    cycle--;
    if (cycle < 1)
    {
      lullaby++;
      if (lullaby == 10)
      {
        lullaby = 0;
      }

      if (musicalLullaby[music][lullaby] > 0)
      {
        if (musicalLullaby[music][lullaby] == 1)
        {
          soundtones->tone(80, 25);
        }
        else
        {
          soundtones->tone(50, 25);
        }
      }
      cycle = 10;
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

  void subtleKoBeep(ArduboyTones *soundtones)
  {
    soundtones->tone(200, 40);
  }

  void subtleOkBeep(ArduboyTones *soundtones)
  {
    soundtones->tone(600, 40);
  }

  uint8_t sizeTypeAbs(uint8_t a, uint8_t b)
  {
    return a < b ? b - a : a - b;
  }
};

#include "Stats.h"
#include "Text.h"
