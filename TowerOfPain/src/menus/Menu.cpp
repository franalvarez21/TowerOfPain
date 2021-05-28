
#include "../Game.h"

#ifndef menudeclaration
#define menudeclaration

class Menu
{
protected:
  Utils *utils;
  Text *text;
  Stats *stats;
  size_t option;
  size_t maxOption;

public:
  Menu(size_t value = 4) : maxOption(value){};

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

  void displayMenuCursor(size_t x, size_t y)
  {
    text->printCommonLine(x, y + (SQUARE_SIZE * option), 25);
  }
};

#endif
