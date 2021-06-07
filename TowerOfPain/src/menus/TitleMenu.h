#pragma once

class TitleMenu : public Menu
{
protected:
  bool about;

public:
  TitleMenu() : Menu(2), about(false){};

  bool action(Utils *utils, ArduboyTones *soundtones)
  {
    if (!about)
    {
      upDownMovement(utils);

      if (okMovement(utils))
      {
        if (option == 2)
        {
          utils->okBeep(soundtones);
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
            utils->okBeep(soundtones);
            utils->sound = true;
            utils->lullaby = 0;
          }
        }
        else if (option == 0)
        {
          utils->okBeep(soundtones);
          return false;
        }
      }
    }
    else
    {
      if (okMovement(utils) || koMovement(utils))
      {
        about = false;
      }
    }

    return true;
  }

  void eventDisplay(Utils *utils, Text *text)
  {
    utils->arduboy->drawBitmap(0, 0, Title::logo, 128, 32, WHITE);
    utils->arduboy->drawBitmap(120, 32, Title::options, 8, 32, WHITE);
    utils->arduboy->drawBitmap(0, 42, Title::player, 17, 22, WHITE);

    if (utils->cycle <= 5)
    {
      utils->arduboy->drawBitmap(0, 22, Common::logo_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      utils->arduboy->drawBitmap(0, 22, Common::logo_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }

    if (about)
    {
      text->printStoryLine(63, 60, 35);
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

      displayMenuCursor(text, 90, 44);
    }
  }
};
