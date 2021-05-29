#pragma once

#include "../Game.h"

class Menu
{
protected:
  Utils *utils;
  Text *text;
  Stats *stats;
  uint8_t option;
  uint8_t maxOption;

public:
  Menu(uint8_t value = 4) : maxOption(value){};

  void init(Utils *utils, Text *text, Stats *stats)
  {
    this->utils = utils;
    this->text = text;
    this->stats = stats;
    option = 0;
  }

  void upDownMovement()
  {
    if (utils->arduboy->justPressed(UP_BUTTON))
    {
      if (option > 0)
      {
        option--;
      }
    }

    if (utils->arduboy->justPressed(DOWN_BUTTON))
    {
      if (option < maxOption)
      {
        option++;
      }
    }
  }

  bool okMovement()
  {
    return utils->arduboy->justPressed(B_BUTTON) || utils->arduboy->justPressed(RIGHT_BUTTON);
  }

  bool koMovement()
  {
    return utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(LEFT_BUTTON);
  }

  void displayMenuCursor(uint8_t x, uint8_t y)
  {
    text->printCommonLine(x, y + (SQUARE_SIZE * option), 25);
  }
};
