#pragma once

struct Cutscene
{
  Utils *utils;
  size_t number;
  size_t timer;

  void init(Utils *utils)
  {
    this->utils = utils;
  }

  void start(size_t number)
  {
    this->number = number;
    number = 0;
    timer = 30;
  }

  bool enabled()
  {
    return (timer == 0);
  }

  void eventDisplay(Stats *stats, Text *text)
  {
    if (enabled())
    {
      text->printCommonLine(80, 52, 28);
    }
    else
    {
      timer--;
    }

    if (number != 1)
    {
      if (utils->cycle <= 5)
      {
        utils->arduboy->drawBitmap(4, 4, Character::framePlayer1, 32, 48, WHITE);
      }
      else
      {
        utils->arduboy->drawBitmap(4, 4, Character::framePlayer2, 32, 48, WHITE);
      }
    }
    else
    {
      utils->arduboy->drawBitmap(4, 4, Character::framePlayer3, 32, 48, WHITE);
    }

    switch (number)
    {
    case 0:
      text->printStoryLine(40, 8, 37);
      text->printStoryLine(40, 16, 38);
      text->printStoryLine(40, 24, 39);
      text->printStoryLine(40, 32, 40);
      break;
    case 1:
      text->printStoryLine(40, 8, 41);
      text->printStoryLine(40, 16, 42);
      text->printStoryLine(40, 24, 43);
      text->printStoryLine(40, 32, 44);
      break;
    case 2:
      text->printStoryLine(40, 8, 45);
      text->printStoryLine(40, 16, 46);
      text->printStoryLine(40, 24, 47);
      text->printStoryLine(40, 32, 48);
      break;
    }
  }
};
