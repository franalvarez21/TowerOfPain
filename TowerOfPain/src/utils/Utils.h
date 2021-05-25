#pragma once

struct Utils
{
  Arduboy2 *arduboy;
  ArduboyTones *soundtones;

  bool sound;
  size_t cicle;

  void init(Arduboy2 *arduboy, ArduboyTones *soundtones)
  {
    this->arduboy = arduboy;
    this->soundtones = soundtones;

    cicle = 10;
    sound = false;
  }

  void tick(void)
  {
    cicle--;
    if (cicle < 1)
    {
      cicle = 10;
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
