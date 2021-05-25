#pragma once

struct Events
{
  Utils *utils;
  size_t option;
  size_t battleEnemyLife;
  size_t currentLevel;
  bool use;

  void init(Utils *utils)
  {
    this->utils = utils;
  }

  void refresh(size_t level)
  {
    option = 0;
    currentLevel = level;
    battleEnemyLife = (rand() % 2 == 0) ? (rand() % (1 + currentLevel)) + 1 : 1;
    use = false;
  }

  bool action(Stats *stats, Text *text, Utils *utils)
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
      if (option < 3)
      {
        option++;
      }
    }

    if (utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(B_BUTTON) || utils->arduboy->justPressed(LEFT_BUTTON) || utils->arduboy->justPressed(RIGHT_BUTTON))
    {
      if (option == 3)
      {
        if (!escapeAttempt(text, stats))
        {
          utils->okBeep();
          return false;
        }
      }
      else if (option == 2)
      {
        if (use)
        {
          if (useSpareAttempt(text, stats))
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
            return false;
          }
        }
        else
        {
          use = true;
        }
      }
      else if (option == 1)
      {
        if (use)
        {
          if (useRelicAttempt(text, stats))
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
        }
        else
        {
          defendAttempt(text, stats);
          utils->okBeep();
        }
      }
      else if (option == 0)
      {
        if (use)
        {
          if (usePotionAttempt(text, stats))
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
        }
        else
        {
          utils->okBeep();
          attackAttempt(text, stats);
        }
      }
    }

    if (battleEnemyLife < 1)
    {
      utils->okBeep();
      return false;
    }

    return true;
  }

  bool useSpareAttempt(Text *text, Stats *stats)
  {
    if (battleEnemyLife > (currentLevel / 2 + 1))
    {
      text->printLog(33);
    }
    else
    {
      if (rand() % 2 == 0)
      {
        text->printLog(29);
      }
      else if (rand() % 2 == 0)
      {
        stats->hit();
        text->printLog(30);
      }
      else if (rand() % 2 == 0)
      {
        text->printLog(31);
        return false;
      }
      else
      {
        stats->addItem(8);
        text->printLog(32);
        return false;
      }
    }
    return true;
  }

  bool useRelicAttempt(Text *text, Stats *stats)
  {
    if (stats->discardItem(7))
    {
      if (rand() % 2 == 0)
      {
        battleEnemyLife = 0;
        text->printLog(28);
        return false;
      }
      else
      {
        stats->incSTR(2);
        text->printLog(27);
        return false;
      }
    }
    else
    {
      text->printLog(34);
      return true;
    }
  }

  void attackAttempt(Text *text, Stats *stats)
  {
    if (rand() % 2 == 0)
    {
      stats->hit();
      text->printLog(18);
    }
    else
    {
      text->printLog(19);
    }

    if (stats->discardItem(4))
    {
      stats->decSTR(2);
    }

    if (battleEnemyLife < stats->getSTR())
    {
      battleEnemyLife = 0;
    }
    else
    {
      battleEnemyLife = battleEnemyLife - stats->getSTR();
    }
  }

  void defendAttempt(Text *text, Stats *stats)
  {
    if (rand() % 2 == 0)
    {
      text->printLog(20);
    }
    else
    {
      text->printLog(21);
    }
  }

  bool usePotionAttempt(Text *text, Stats *stats)
  {
    if (stats->discardItem(8))
    {
      if (rand() % 2 == 0)
      {
        stats->incHP(1);
        text->printLog(17);
      }
      else
      {
        switch (rand() % 5)
        {
        case 0:
          stats->incHP(5);
          text->printLog(23);
          break;
        case 1:
          battleEnemyLife = 0;
          text->printLog(24);
          break;
        case 2:
          stats->baseStr++;
          stats->incSTR(1);
          text->printLog(25);
          break;
        case 3:
          stats->baseHp++;
          stats->incHP(1);
          text->printLog(26);
          break;
        }
      }
      return false;
    }
    else
    {
      text->printLog(16);
      return true;
    }
  }

  bool escapeAttempt(Text *text, Stats *stats)
  {
    if (use)
    {
      option = 2;
      use = false;
      return true;
    }

    if (battleEnemyLife > (currentLevel / 2 + 1))
    {
      text->printLog(36);
      utils->koBeep();
      return true;
    }

    if (rand() % 4 > 0)
    {
      text->printLog(14);
      stats->hit();
      return true;
    }

    text->printLog(15);
    return false;
  }

  void eventDisplay(Text *text, size_t cicle)
  {
    if (battleEnemyLife > (currentLevel / 2 + 1))
    {
      if (cicle <= 5)
      {
        utils->arduboy->drawBitmap(4, 4, Character::frameSlime3, 32, 48, WHITE);
      }
      else
      {
        utils->arduboy->drawBitmap(4, 4, Character::frameSlime4, 32, 48, WHITE);
      }
    }
    else
    {
      if (cicle <= 5)
      {
        utils->arduboy->drawBitmap(4, 4, Character::frameSlime1, 32, 48, WHITE);
      }
      else
      {
        utils->arduboy->drawBitmap(4, 4, Character::frameSlime2, 32, 48, WHITE);
      }
    }

    text->printValue(7, 45, battleEnemyLife);
    text->printCommonLine(24, 45, 1);

    if (use)
    {
      text->printCommonLine(40, 8, 11);
      text->printCommonLine(48, 20, 7);
      text->printCommonLine(48, 28, 13);
      text->printCommonLine(48, 36, 14);
      text->printCommonLine(48, 44, 15);
    }
    else
    {
      text->printCommonLine(40, 8, 8);
      text->printCommonLine(48, 20, 9);
      text->printCommonLine(48, 28, 10);
      text->printCommonLine(48, 36, 11);
      text->printCommonLine(48, 44, 16);
    }

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
    case 3:
      text->printCommonLine(40, 44, 25);
      break;
    }
  }
};
