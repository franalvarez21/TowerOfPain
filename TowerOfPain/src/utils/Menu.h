#pragma once

struct Menu
{
  Utils *utils;
  size_t option;
  bool about;

  void init(Utils *utils)
  {
    this->utils = utils;
    option = 0;
    about = false;
  }

  bool action()
  {
    if (!about)
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
      if (utils->arduboy->justPressed(B_BUTTON) || utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(LEFT_BUTTON) || utils->arduboy->justPressed(RIGHT_BUTTON) || utils->arduboy->justPressed(UP_BUTTON) || utils->arduboy->justPressed(DOWN_BUTTON))
      {
        about = false;
      }
    }

    return true;
  }

  void eventDisplay(Text *text)
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

      switch (option)
      {
      case 0:
        text->printCommonLine(90, 44, 25);
        break;
      case 1:
        text->printCommonLine(90, 52, 25);
        break;
      case 2:
        text->printCommonLine(90, 60, 25);
        break;
      }
    }

    text->printCommonLine(0, 60, 24);
  }
};
