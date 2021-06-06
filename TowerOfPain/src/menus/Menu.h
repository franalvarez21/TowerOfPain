#pragma once

#include "../Game.h"

class Menu
{
protected:
  uint8_t option;
  uint8_t maxOption;

public:
  Menu(uint8_t value = 4) : maxOption(value), option(0){};

  void upDownMovement(Utils *utils)
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

  bool okMovement(Utils *utils)
  {
    return utils->arduboy->justPressed(B_BUTTON) || utils->arduboy->justPressed(RIGHT_BUTTON);
  }

  bool koMovement(Utils *utils)
  {
    return utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(LEFT_BUTTON);
  }

  void displayMenuCursor(Text *text, uint8_t x, uint8_t y)
  {
    text->printCommonLine(x, y + (SQUARE_SIZE * option), 24);
  }
};
