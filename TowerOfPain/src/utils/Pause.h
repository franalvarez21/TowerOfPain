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

  size_t action(Utils *utils)
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

    if (utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(B_BUTTON) || utils->arduboy->justPressed(LEFT_BUTTON) || utils->arduboy->justPressed(RIGHT_BUTTON))
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

    return 0;
  }

  void eventDisplay(Stats *stats, Text *text, bool sound, size_t cicle)
  {
    if (cicle <= 5)
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

    utils->tinyfont->setCursor(8, 45);
    text->printCommonLine(26);

    utils->tinyfont->setCursor(40, 8);
    text->printCommonLine(8);
    utils->tinyfont->setCursor(48, 20);
    if (sound)
    {
      text->printCommonLine(20);
    }
    else
    {
      text->printCommonLine(21);
    }
    utils->tinyfont->setCursor(48, 28);
    text->printCommonLine(22);
    utils->tinyfont->setCursor(48, 36);
    text->printCommonLine(15);

    switch (option)
    {
    case 0:
      utils->tinyfont->setCursor(40, 20);
      break;
    case 1:
      utils->tinyfont->setCursor(40, 28);
      break;
    case 2:
      utils->tinyfont->setCursor(40, 36);
      break;
    }

    text->printCommonLine(25);
  }
};
