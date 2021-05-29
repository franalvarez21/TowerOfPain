#pragma once

class TitleMenu : public Menu
{
protected:
  bool about;

public:
  TitleMenu() : Menu(2), about(false){};

  bool action()
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

  void eventDisplay()
  {
    utils->arduboy->drawBitmap(0, 0, Title::logo, 128, 32, WHITE);
    utils->arduboy->drawBitmap(120, 32, Title::options, 8, 32, WHITE);

    if (about)
    {
      text->printStoryLine(38, 60, 35);
    }
    else
    {
      text->printCommonLine(98, 44, 17);
      text->printCommonLine(98, 52, 12);
      if (utils->sound)
      {
        text->printCommonLine(77, 52, 18);
      }
      else
      {
        text->printCommonLine(72, 52, 19);
      }
      text->printCommonLine(98, 60, 23);

      displayMenuCursor(90, 44);
    }

    text->printCommonLine(0, 60, 24);
  }
};