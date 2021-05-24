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

  bool action(Utils *utils)
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

  void eventDisplay(Utils *utils, Text *text)
  {
    utils->arduboy->drawBitmap(0, 0, Title::logo, 128, 32, WHITE);
    utils->arduboy->drawBitmap(120, 32, Title::options, 8, 32, WHITE);

    if (about)
    {
      utils->tinyfont->setCursor(38, 60);
      text->printStoryLine(35);
    }
    else
    {
      utils->tinyfont->setCursor(98, 44);
      text->printCommonLine(17);
      utils->tinyfont->setCursor(98, 52);
      text->printCommonLine(12);
      if (utils->sound)
      {
        utils->tinyfont->setCursor(77, 52);
        text->printCommonLine(18);
      }
      else
      {
        utils->tinyfont->setCursor(72, 52);
        text->printCommonLine(19);
      }
      utils->tinyfont->setCursor(98, 60);
      text->printCommonLine(23);

      switch (option)
      {
      case 0:
        utils->tinyfont->setCursor(90, 44);
        break;
      case 1:
        utils->tinyfont->setCursor(90, 52);
        break;
      case 2:
        utils->tinyfont->setCursor(90, 60);
        break;
      }

      text->printCommonLine(25);
    }

    utils->tinyfont->setCursor(0, 60);
    text->printCommonLine(24);
  }
};
