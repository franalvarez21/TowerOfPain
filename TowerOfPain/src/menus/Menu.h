#pragma once

#include "../Game.h"

class Menu
{
protected:
  uint8_t option;
  uint8_t maxOption;

public:
  Menu(uint8_t value = 4) : maxOption(value), option(0){};

  void upDownMovement()
  {
    if (Arduboy2Base::justPressed(UP_BUTTON))
    {
      if (option > 0)
      {
        option--;
      }
    }

    if (Arduboy2Base::justPressed(DOWN_BUTTON))
    {
      if (option < maxOption)
      {
        option++;
      }
    }
  }

  bool okMovement()
  {
    return Arduboy2Base::justPressed(B_BUTTON) || Arduboy2Base::justPressed(RIGHT_BUTTON);
  }

  bool koMovement()
  {
    return Arduboy2Base::justPressed(A_BUTTON) || Arduboy2Base::justPressed(LEFT_BUTTON);
  }

  void displayMenuCursor(Utils *utils, uint8_t x, uint8_t y)
  {
    utils->texts.printCommonLine(x, y + (SQUARE_SIZE * option), 24);
  }

  void displayFeedbackCursor(uint8_t x, uint8_t y)
  {
    Arduboy2Base::drawBitmap(x, y + (SQUARE_SIZE * option), Common::update_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
  }
};
