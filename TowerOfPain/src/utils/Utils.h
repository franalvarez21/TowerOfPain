#pragma once

struct Utils
{
  Arduboy2 *arduboy;
  ArduboyTones *soundtones;

  bool sound;
  bool music;
  size_t cicle;
  size_t musicalLullaby[10] = {0, 1, 0, 1, 1, 0, 1, 1, 1, 0};
  size_t lullaby = 0;

  void init(Arduboy2 *arduboy, ArduboyTones *soundtones)
  {
    this->arduboy = arduboy;
    this->soundtones = soundtones;

    cicle = 10;
    sound = false;
    music = false;
  }

  void tick(void)
  {
    cicle--;
    if (cicle < 1)
    {
      lullaby++;
      if (lullaby == 11)
      {
        lullaby = 0;
      }
      doBeep();
      cicle = 10;
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
    soundtones->tone(800, 50);
  }
};
