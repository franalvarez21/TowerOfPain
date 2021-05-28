
#include "Menu.cpp"

class BattleMenu : public Menu
{
protected:
  size_t menu;
  size_t battleEnemyLife;
  size_t currentLevel;

public:
  BattleMenu() : Menu(3){};

  void refresh(size_t level)
  {
    menu = 0;
    option = 0;
    currentLevel = level;
    battleEnemyLife = getRandomLevel();
  }

  bool action()
  {
    upDownMovement();

    if (utils->arduboy->justPressed(B_BUTTON) || utils->arduboy->justPressed(RIGHT_BUTTON))
    {
      if (option == 3)
      {
        switch (menu)
        {
        case 0:
          if (escapeAttempt())
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
            return false;
          }
          break;
        default:
          menu--;
          break;
        }
      }
      else if (option == 2)
      {
        switch (menu)
        {
        case 2:
          if (useExplainAttempt())
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
          break;
        case 1:
          if (currentLevel < 50)
          {
            utils->koBeep();
            text->printLog(69);
          }
          else
          {
            menu++;
          }
          break;
        default:
          menu++;
          break;
        }
      }
      else if (option == 1)
      {
        switch (menu)
        {
        case 0:
          if (useSpareAttempt())
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
            return false;
          }
          break;
        case 1:
          if (useRelicAttempt())
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
          break;
        default:
          if (useApproachAttempt())
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
          break;
        }
      }
      else if (option == 0)
      {
        switch (menu)
        {
        case 0:
          attackAttempt();
          utils->okBeep();
          break;
        case 1:
          if (usePotionAttempt())
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
          break;
        default:
          if (useThreatAttempt())
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
          break;
        }
      }
    }

    if (menu > 0 && (utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(LEFT_BUTTON)))
    {
      menu--;
    }

    if (battleEnemyLife < 1)
    {
      utils->okBeep();
      stats->counter.killed++;
      return false;
    }

    return true;
  }

  bool useThreatAttempt()
  {
    return true;
  }

  bool useApproachAttempt()
  {
    return true;
  }

  bool useExplainAttempt()
  {
    return true;
  }

  bool useSpareAttempt()
  {
    if (spareHardCondition())
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
        stats->counter.spared++;
        return false;
      }
      else
      {
        stats->addItem(8);
        text->printLog(32);
        stats->counter.spared++;
        return false;
      }
    }
    return true;
  }

  bool useRelicAttempt()
  {
    if (stats->discardItem(7))
    {
      if (rand() % 2 == 0)
      {
        battleEnemyLife = 0;
        text->printLog(28);
      }
      else
      {
        stats->incSTR(1);
        text->printLog(27);
      }

      stats->counter.utils++;
      return false;
    }
    else
    {
      text->printLog(34);
      return true;
    }
  }

  void attackAttempt()
  {
    uint8_t additionalDamage = 0;

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
      additionalDamage = 2;
    }

    hitEnemy(stats->getSTR() + additionalDamage);
  }

  bool usePotionAttempt()
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
        switch (rand() % 4)
        {
        case 0:
          stats->incHP(2);
          text->printLog(23);
          break;
        case 1:
          stats->incSTR(1);
          text->printLog(24);
          break;
        case 2:
          stats->incDEF(1);
          text->printLog(25);
          break;
        case 3:
          stats->incDEF(2);
          text->printLog(26);
          break;
        }
      }
      stats->counter.utils++;
      return false;
    }
    else
    {
      text->printLog(16);
      return true;
    }
  }

  bool escapeAttempt()
  {
    if (spareHardCondition())
    {
      text->printLog(36);
      utils->koBeep();
      return true;
    }

    if (rand() % 5 > 0)
    {
      text->printLog(14);
      stats->hit();
      return true;
    }

    stats->counter.escaped++;
    text->printLog(15);
    return false;
  }

  void eventDisplay()
  {

    if (currentLevel < 50)
    {
      if (spareHardCondition())
      {
        if (utils->cycle <= 5)
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
        if (utils->cycle <= 5)
        {
          utils->arduboy->drawBitmap(4, 4, Character::frameSlime1, 32, 48, WHITE);
        }
        else
        {
          utils->arduboy->drawBitmap(4, 4, Character::frameSlime2, 32, 48, WHITE);
        }
      }
    }
    else if (currentLevel < 100)
    {
      if (utils->cycle <= 5)
      {
        utils->arduboy->drawBitmap(4, 4, Character::frameEye1, 32, 48, WHITE);
      }
      else
      {
        utils->arduboy->drawBitmap(4, 4, Character::frameEye2, 32, 48, WHITE);
      }
    }
    else
    {
      if (utils->cycle <= 5)
      {
        utils->arduboy->drawBitmap(4, 4, Character::frameKnight1, 32, 48, WHITE);
      }
      else
      {
        utils->arduboy->drawBitmap(4, 4, Character::frameKnight2, 32, 48, WHITE);
      }
    }

    text->printValue(7, 45, battleEnemyLife);
    text->printCommonLine(24, 45, 1);

    switch (menu)
    {
    case 0:
      text->printCommonLine(40, 8, 8);
      text->printCommonLine(48, 20, 9);
      text->printCommonLine(48, 28, 14);
      text->printCommonLine(48, 36, 11);
      text->printCommonLine(48, 44, 16);
      break;
    case 1:
      text->printCommonLine(40, 8, 11);
      text->printCommonLine(48, 20, 7);
      text->printCommonLine(48, 28, 13);
      text->printCommonLine(48, 36, 10);
      text->printCommonLine(48, 44, 15);
      break;
    default:
      text->printCommonLine(40, 8, 10);
      text->printCommonLine(48, 20, 30);
      text->printCommonLine(48, 28, 31);
      text->printCommonLine(48, 36, 32);
      text->printCommonLine(48, 44, 15);
      break;
    }

    displayMenuCursor(40, 20);
  }

  size_t getRandomLevel()
  {
    if (currentLevel < 50)
    {
      return (rand() % (min(currentLevel, 19) + 1)) + 1;
    }

    if (currentLevel < 100)
    {
      return (rand() % (min(currentLevel, 49) + 1)) + 1;
    }

    return (rand() % (min(currentLevel, 98) + 1)) + 1;
  }

  bool spareHardCondition()
  {
    return battleEnemyLife > (currentLevel / 2 + 1);
  }

  void hitEnemy(uint8_t str)
  {
    if (battleEnemyLife < str)
    {
      battleEnemyLife = 0;
    }
    else
    {
      battleEnemyLife = battleEnemyLife - str;
    }
  }
};
