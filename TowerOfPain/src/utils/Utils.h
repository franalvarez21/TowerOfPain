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

#include "Stats.h"
#include "Texts.h"

struct Utils
{
  Arduboy2 arduboy;
  Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
  Stats stats;
  Texts texts;

  bool soundFlag;
  uint8_t music;
  uint8_t cycle;
  uint8_t musicalLullaby[4][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 1, 2, 0, 1, 1, 2, 0}, {0, 1, 2, 0, 1, 2, 0, 1, 1, 2}, {0, 1, 1, 1, 3, 3, 3, 1, 1, 1}};
  uint8_t lullaby = 0;

  void init()
  {
    ArduboyTones sound(arduboy.audio.enabled);
    texts.init(&tinyfont);

    cycle = 10;
    soundFlag = false;
    music = 0;
  }

  void tick()
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
          ArduboyTones::tone(80, 25);
        }
        else if (musicalLullaby[music][lullaby] == 2)
        {
          ArduboyTones::tone(50, 50);
        }
        else
        {
          ArduboyTones::tone(80, 50);
        }
      }
      cycle = 10;
    }
  }

  void changesoundFlag()
  {
    if (soundFlag)
    {
      soundFlag = false;
      Arduboy2Base::audio.off();
    }
    else
    {
      soundFlag = true;
      Arduboy2Base::audio.on();
      okBeep();
      lullaby = 0;
    }
  }

  void koBeep()
  {
    ArduboyTones::tone(250, 50);
  }

  void okBeep()
  {
    ArduboyTones::tone(700, 50);
  }

  void subtleKoBeep()
  {
    ArduboyTones::tone(200, 40);
  }

  void subtleOkBeep()
  {
    ArduboyTones::tone(600, 40);
  }

  uint8_t sizeTypeAbs(uint8_t a, uint8_t b)
  {
    return a < b ? b - a : a - b;
  }
};
