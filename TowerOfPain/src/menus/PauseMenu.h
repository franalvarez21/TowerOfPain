#pragma once

class PauseMenu : public Menu
{
public:
  PauseMenu() : Menu(2){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
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
        utils->changesoundFlag();
      }
    }

    if (koMovement())
    {
      return 1;
    }

    return 0;
  }

  void eventDisplay(Utils *utils)
  {
    if (utils->cycle <= 5)
    {
      Arduboy2Base::drawBitmap(4, 4, Character::framePlayer1, 32, 48, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(4, 4, Character::framePlayer2, 32, 48, WHITE);
    }

    if (utils->stats.where(5) != ITEM_AMOUNT)
    {
      Arduboy2Base::drawBitmap(8, 34, Character::frameShield, 8, 9, WHITE);
    }

    if (utils->stats.where(4) != ITEM_AMOUNT)
    {
      Arduboy2Base::drawBitmap(28, 20, Character::frameSword, 4, 23, WHITE);
    }

    utils->texts.printCommonLine(40, 8, 8);
    if (utils->soundFlag)
    {
      utils->texts.printCommonLine(48, 20, 20);
    }
    else
    {
      utils->texts.printCommonLine(48, 20, 21);
    }
    utils->texts.printCommonLine(48, 28, 22);
    utils->texts.printCommonLine(48, 36, 15);

    displayMenuCursor(utils, 40, 20);
  }
};
