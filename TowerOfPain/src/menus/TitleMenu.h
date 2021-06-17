#pragma once

class TitleMenu : public Menu
{
public:
  TitleMenu() : Menu(1){};

  bool action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
    {
      if (option == 1)
      {
        utils->changesoundFlag();
      }
      else if (option == 0)
      {
        utils->okBeep();
        return false;
      }
    }

    return true;
  }

  void eventDisplay(Utils *utils)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::logo, 70, 26, WHITE);

    if (utils->cycle <= 5)
    {
      Arduboy2Base::drawBitmap(109, 5, Title::orbs_1, 15, 29, WHITE);
      Arduboy2Base::drawBitmap(0, 22, Common::logo_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(109, 6, Title::orbs_1, 15, 29, WHITE);
      Arduboy2Base::drawBitmap(0, 22, Common::logo_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }

    utils->texts.printStoryLine(0, 60, 35);
    utils->texts.printCommonLine(102, 52, 17);
    utils->texts.printCommonLine(102, 60, 12);
    if (utils->soundFlag)
    {
      utils->texts.printCommonLine(78, 60, 18);
    }
    else
    {
      utils->texts.printCommonLine(75, 60, 19);
    }

    displayMenuCursor(utils, 94, 52);
  }
};
