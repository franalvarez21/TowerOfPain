#pragma once

struct Pause
{
  Utils *utils;
  size_t option;
  bool use;

  void init(Utils *utils)
  {
    this->utils = utils;
    option = 2;
    use = false;
  }

  size_t action()
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
      if (option < 2)
      {
        option++;
      }
    }

    if (utils->arduboy->justPressed(B_BUTTON) || utils->arduboy->justPressed(RIGHT_BUTTON))
    {
      if (option == 2)
      {
        return 1;
      }
      else if (option == 1)
      {
        utils->okBeep();
        return 2;
      }
      else if (option == 0)
      {
        if (utils->sound)
        {
          utils->arduboy->audio.off();
          utils->sound = false;
        }
        else
        {
          utils->arduboy->audio.on();
          utils->okBeep();
          utils->sound = true;
        }
      }
    }

    if (utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(LEFT_BUTTON))
    {
      return 1;
    }

    return 0;
  }

  void eventDisplay(Stats *stats, Text *text)
  {
    if (utils->cycle <= 5)
    {
      utils->arduboy->drawBitmap(4, 4, Character::framePlayer1, 32, 48, WHITE);
    }
    else
    {
      utils->arduboy->drawBitmap(4, 4, Character::framePlayer2, 32, 48, WHITE);
    }

    if (stats->hasShield())
    {
      utils->arduboy->drawBitmap(8, 34, Character::frameShield, 8, 9, WHITE);
    }

    if (stats->hasSword())
    {
      utils->arduboy->drawBitmap(28, 20, Character::frameSword, 4, 23, WHITE);
    }

    text->printCommonLine(40, 8, 8);
    if (utils->sound)
    {
      text->printCommonLine(48, 20, 20);
    }
    else
    {
      text->printCommonLine(48, 20, 21);
    }
    text->printCommonLine(48, 28, 22);
    text->printCommonLine(48, 36, 15);

    switch (option)
    {
    case 0:
      text->printCommonLine(40, 20, 25);
      break;
    case 1:
      text->printCommonLine(40, 28, 25);
      break;
    case 2:
      text->printCommonLine(40, 36, 25);
      break;
    }
  }
};
