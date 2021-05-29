#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <Tinyfont.h>

#include "const/Map.h"
#include "const/Common.h"
#include "const/Character.h"
#include "const/Lines.h"
#include "const/Title.h"

struct Utils
{
  Arduboy2 *arduboy;
  ArduboyTones *soundtones;

  bool sound;
  bool music;
  size_t cycle;
  size_t musicalLullaby[10] = {0, 1, 0, 1, 1, 0, 1, 1, 1, 0};
  size_t lullaby = 0;

  void init(Arduboy2 *arduboy, ArduboyTones *soundtones)
  {
    this->arduboy = arduboy;
    this->soundtones = soundtones;

    cycle = 10;
    sound = false;
    music = false;
  }

  void tick(void)
  {
    cycle--;
    if (cycle < 1)
    {
      lullaby++;
      if (lullaby == 11)
      {
        lullaby = 0;
      }
      doBeep();
      cycle = 10;
    }
  }

  void doBeep()
  {
    if (musicalLullaby[lullaby] == 1 && music)
    {
      soundtones->tone(150, 50);
    }
  }

  void koBeep()
  {
    soundtones->tone(250, 50);
  }

  void okBeep()
  {
    soundtones->tone(700, 50);
  }

  size_t sizeTypeAbs(size_t a, size_t b)
  {
    return a < b ? b - a : a - b;
  }
};

#include "Stats.h"
#include "Text.h"
