#pragma once

class PauseMenu : public Menu
{
public:
  PauseMenu() : Menu(2){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action(Utils *utils, ArduboyTones *soundtones)
  {
    upDownMovement(utils);

    if (okMovement(utils))
    {
      if (option == 2)
      {
        return 1;
      }
      else if (option == 1)
      {
        utils->okBeep(soundtones);
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
          utils->okBeep(soundtones);
          utils->sound = true;
        }
      }
    }

    if (koMovement(utils))
    {
      return 1;
    }

    return 0;
  }

  void eventDisplay(Utils *utils, Text *text, Stats *stats)
  {
    if (utils->cycle <= 5)
    {
      utils->arduboy->drawBitmap(4, 4, Character::framePlayer1, 32, 48, WHITE);
    }
    else
    {
      utils->arduboy->drawBitmap(4, 4, Character::framePlayer2, 32, 48, WHITE);
    }

    if (stats->where(5) != ITEM_AMOUNT)
    {
      utils->arduboy->drawBitmap(8, 34, Character::frameShield, 8, 9, WHITE);
    }

    if (stats->where(4) != ITEM_AMOUNT)
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

    displayMenuCursor(text, 40, 20);
  }
};
