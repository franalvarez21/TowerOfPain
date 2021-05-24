#pragma once

struct Clock
{
  size_t circle;

  void init(void)
  {
    circle = 10;
  }

  void tick(void)
  {
    circle--;
    if (circle < 1)
    {
      circle = 10;
    }
  }
};

struct Utils
{
  Arduboy2 *arduboy;
  Tinyfont *tinyfont;
  ArduboyTones *soundtones;

  Clock clock;
  bool sound;

  void init(Arduboy2 *arduboy, Tinyfont *tinyfont, ArduboyTones *soundtones)
  {
    this->arduboy = arduboy;
    this->tinyfont = tinyfont;
    this->soundtones = soundtones;

    clock.init();
    sound = false;
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
