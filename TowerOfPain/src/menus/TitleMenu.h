#pragma once

class TitleMenu : public Menu
{
protected:
  bool about;

public:
  TitleMenu() : Menu(2), about(false){};

  bool action(Utils *utils)
  {
    if (!about)
    {
      upDownMovement();

      if (okMovement())
      {
        if (option == 2)
        {
          utils->okBeep();
          about = true;
        }
        else if (option == 1)
        {
          utils->changesoundFlag();
        }
        else if (option == 0)
        {
          utils->okBeep();
          return false;
        }
      }
    }
    else
    {
      if (okMovement() || koMovement())
      {
        about = false;
      }
    }

    return true;
  }

  void eventDisplay(Utils *utils)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::logo, 128, 32, WHITE);
    Arduboy2Base::drawBitmap(120, 32, Title::options, 8, 32, WHITE);
    Arduboy2Base::drawBitmap(0, 42, Title::player, 17, 22, WHITE);

    if (utils->cycle <= 5)
    {
      Arduboy2Base::drawBitmap(0, 22, Common::logo_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(0, 22, Common::logo_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }

    if (about)
    {
      utils->texts.printStoryLine(63, 60, 35);
    }
    else
    {
      utils->texts.printCommonLine(98, 44, 17);
      utils->texts.printCommonLine(98, 52, 12);
      if (utils->soundFlag)
      {
        utils->texts.printCommonLine(77, 52, 18);
      }
      else
      {
        utils->texts.printCommonLine(72, 52, 19);
      }
      utils->texts.printCommonLine(98, 60, 23);

      displayMenuCursor(utils, 90, 44);
    }
  }
};
