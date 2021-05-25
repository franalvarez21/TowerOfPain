#pragma once

struct Cutscene
{
  Utils *utils;
  size_t option;

  void init(Utils *utils)
  {
    this->utils = utils;
    option = 0;
  }

  bool action()
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
      if (option < 1)
      {
        option++;
      }
    }

    if (utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(B_BUTTON) || utils->arduboy->justPressed(LEFT_BUTTON) || utils->arduboy->justPressed(RIGHT_BUTTON))
    {
      if (option == 1)
      {
        return false;
      }
      else if (option == 0)
      {
        return false;
      }
    }

    return true;
  }

  void eventDisplay(Stats *stats, Text *text)
  {
    if (utils->cicle <= 5)
    {
      utils->arduboy->drawBitmap(4, 4, Character::framePlayer1, 32, 48, WHITE);
    }
    else
    {
      utils->arduboy->drawBitmap(4, 4, Character::framePlayer2, 32, 48, WHITE);
    }

    text->printCommonLine(8, 45, 26);
    text->printCommonLine(48, 36, 27);
    text->printCommonLine(48, 44, 28);

    switch (option)
    {
    case 0:
      text->printCommonLine(40, 36, 25);
      break;
    case 1:
      text->printCommonLine(40, 44, 25);
      break;
    }
  }
};
