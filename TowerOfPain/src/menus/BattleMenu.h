#pragma once

class BattleMenu : public Menu
{
protected:
  size_t menu;
  Dungeon *dungeon;

public:
  BattleMenu() : Menu(3){};

  void setup(Dungeon *dungeon)
  {
    this->dungeon = dungeon;
  }

  void refresh()
  {
    menu = 0;
    option = 0;
    dungeon->monster.setLife();
  }

  bool action()
  {
    upDownMovement();

    if (okMovement())
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
          if (dungeon->monster.currentType == 0)
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

    if (menu > 0 && koMovement())
    {
      menu--;
    }

    if (dungeon->monster.life < 1)
    {
      utils->okBeep();
      stats->counter.killed++;
      return false;
    }

    return true;
  }

  void eventDisplay()
  {
    dungeon->monster.displayFrame();
    text->printValue(7, 45, dungeon->monster.life);
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

private:
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
    if (!dungeon->monster.canBeSpare())
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
        dungeon->monster.life = 0;
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

    dungeon->monster.hitEnemy(stats->getSTR() + additionalDamage);
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
    if (!dungeon->monster.canBeSpare())
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
};
