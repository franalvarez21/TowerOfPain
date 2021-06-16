#pragma once

class BattleMenu : public Menu
{
protected:
  uint8_t menu;
  uint8_t feedbackCounter;

public:
  BattleMenu() : Menu(3){};

  void refresh()
  {
    menu = 0;
    option = 0;
    feedbackCounter = 0;
  }

  bool action(Utils *utils, Dungeon *dungeon)
  {
    upDownMovement();

    if (okMovement())
    {
      feedbackCounter = FEEDBACK_COUNTER;

      if (option == 3)
      {
        switch (menu)
        {
        case 0:
          if (escapeAttempt(utils, dungeon))
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
          feedbackCounter = 0;
          break;
        }
      }
      else if (option == 2)
      {
        switch (menu)
        {
        case 1:
          if (dungeon->monster.currentType < 3)
          {
            utils->koBeep();
            utils->texts.printLog(55);
          }
          else if (utils->stats.getStatusText() == 3 || dungeon->monster.canBeSpare())
          {
            utils->koBeep();
            utils->texts.printLog(72);
          }
          else
          {
            menu++;
            feedbackCounter = 0;
          }
          break;
        case 2:
          if (useExplainAttempt(utils, dungeon))
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
          menu++;
          feedbackCounter = 0;
          break;
        }
      }
      else if (option == 1)
      {
        switch (menu)
        {
        case 0:
          if (useSpareAttempt(utils, dungeon))
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
          if (useRelicAttempt(utils, dungeon))
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
          break;
        default:
          if (useApproachAttempt(utils, dungeon))
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
            return false;
          }
          break;
        }
      }
      else if (option == 0)
      {
        switch (menu)
        {
        case 0:
          attackAttempt(utils, dungeon);
          utils->okBeep();
          break;
        case 1:
          if (usePotionAttempt(utils))
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
          }
          break;
        default:
          if (useThreatAttempt(utils, dungeon))
          {
            utils->koBeep();
          }
          else
          {
            utils->okBeep();
            return false;
          }
          break;
        }
      }
    }

    if (menu > 0 && koMovement())
    {
      menu--;
      feedbackCounter = 0;
    }

    if (dungeon->monster.life < 1)
    {
      utils->okBeep();
      utils->stats.counter.killed++;
      return false;
    }

    return true;
  }

  void eventDisplay(Utils *utils, Dungeon *dungeon)
  {
    dungeon->monster.displayFrame(utils);
    utils->texts.printValue(7, 45, dungeon->monster.life);
    Arduboy2Base::drawBitmap(26, 43, Common::heart, SQUARE_SIZE, SQUARE_SIZE, WHITE);

    switch (menu)
    {
    case 0:
      utils->texts.printCommonLine(40, 8, 8);
      utils->texts.printCommonLine(51, 20, 9);
      utils->texts.printCommonLine(51, 28, 14);
      utils->texts.printCommonLine(51, 36, 11);
      utils->texts.printCommonLine(51, 44, 16);
      break;
    case 1:
      utils->texts.printCommonLine(40, 8, 11);
      utils->texts.printCommonLine(51, 20, 7);
      utils->texts.printCommonLine(51, 28, 13);
      utils->texts.printCommonLine(51, 36, 10);
      utils->texts.printCommonLine(51, 44, 15);
      break;
    default:
      utils->texts.printCommonLine(40, 8, 10);
      utils->texts.printCommonLine(51, 20, 26);
      utils->texts.printCommonLine(51, 28, 27);
      utils->texts.printCommonLine(51, 36, 28);
      utils->texts.printCommonLine(51, 44, 15);
      break;
    }

    if (feedbackCounter > 0 && !utils->soundFlag)
    {
      feedbackCounter--;
      displayFeedbackCursor(39, 18);
    }
    else
    {
      displayMenuCursor(utils, 43, 20);
    }
  }

private:
  bool useThreatAttempt(Utils *utils, Dungeon *dungeon)
  {
    if (utils->stats.getStatusText() == 0 && !dungeon->monster.canBeSpare())
    {
      switch (rand() % 7)
      {
      case 0: // "YELLS BACK";
        utils->texts.printLog(57);
        utils->stats.hit();
        return true;
      case 1: // "ATTACKS, HP DOWN";
        utils->stats.hit();
        utils->texts.printLog(58);
        return true;
      case 2: // "ATTACKS, DEF DOWN";
        utils->stats.decDEF(1);
        utils->stats.hit();
        utils->texts.printLog(59);
        return true;
      case 3: // "FAINTS";
        utils->texts.printLog(60);
        return false;
      case 4: // "AFRAID, DEF UP";
        utils->stats.incDEF(1);
        utils->texts.printLog(61);
        return false;
      case 5: // "SCARE, DEF UP";
        utils->stats.incDEF(1);
        utils->texts.printLog(62);
        return false;
      default: // "HITS AND RUNS";
        utils->texts.printLog(63);
        utils->stats.hit();
        return false;
      }
    }
    utils->texts.printLog(56);
    return true;
  }

  bool useApproachAttempt(Utils *utils, Dungeon *dungeon)
  {
    if (utils->stats.getStatusText() == 1 && !dungeon->monster.canBeSpare())
    {
      switch (rand() % 7)
      {
      case 0: // "ATTACKS, STR DOWN";
        utils->stats.decSTR(1);
        utils->stats.hit();
        utils->texts.printLog(65);
        return true;
      case 1: // "IS AFRAID";
        utils->texts.printLog(66);
        return true;
      case 2: // "STEALS FROM YOU";
        if (!utils->stats.discardItem(8))
        {
          utils->stats.discardItem(7);
        }
        utils->texts.printLog(67);
        return true;
      case 3: // "GIVES YOU A POTION";
        utils->stats.addItem(8);
        utils->texts.printLog(68);
        return false;
      case 4: // "GIVES A RELIC";
        utils->stats.addItem(7);
        utils->texts.printLog(69);
        return false;
      case 5: // "HIT AND RUNS";
        utils->texts.printLog(70);
        utils->stats.hit();
        return false;
      default: // "HIT AND ESCAPE";
        utils->texts.printLog(71);
        utils->stats.hit();
        return false;
      }
    }
    utils->texts.printLog(64);
    return true;
  }

  bool useExplainAttempt(Utils *utils, Dungeon *dungeon)
  {
    if (utils->stats.getStatusText() == 2 && !dungeon->monster.canBeSpare())
    {
      switch (rand() % 7)
      {
      case 0: // "ATTACKS, DEF DOWN";
        utils->stats.decDEF(1);
        utils->stats.hit();
        utils->texts.printLog(73);
        return true;
      case 1: // "ATTACKS";
        utils->stats.hit();
        utils->texts.printLog(74);
        return true;
      case 2: // "ACCEPTS, RELIC FOUND";
        utils->stats.addItem(7);
        utils->texts.printLog(75);
        return false;
      case 3: // "NODS, GIVES POTION";
        utils->stats.addItem(8);
        utils->texts.printLog(76);
        return false;
      case 4: // "LEAVES IN ANGER";
        utils->texts.printLog(77);
        utils->stats.hit();
        return false;
      case 5: // "UNDERSTAND";
        utils->texts.printLog(78);
        return true;
      default: // "HIT AND RUNS";
        utils->texts.printLog(79);
        utils->stats.hit();
        return false;
      }
    }
    utils->texts.printLog(72);
    return true;
  }

  bool useSpareAttempt(Utils *utils, Dungeon *dungeon)
  {
    if (!dungeon->monster.canBeSpare())
    {
      utils->texts.printLog(33);
    }
    else
    {
      if (rand() % 2 == 0)
      {
        utils->texts.printLog(29);
      }
      else if (rand() % 2 == 0)
      {
        utils->stats.hit();
        utils->texts.printLog(30);
      }
      else if (rand() % 2 == 0)
      {
        utils->texts.printLog(31);
        utils->stats.counter.spared++;
        return false;
      }
      else
      {
        utils->stats.addItem(8);
        utils->texts.printLog(32);
        utils->stats.counter.spared++;
        return false;
      }
    }
    return true;
  }

  bool useRelicAttempt(Utils *utils, Dungeon *dungeon)
  {
    if (utils->stats.discardItem(7))
    {
      if (rand() % 2 == 0)
      {
        dungeon->monster.life = 0;
        utils->texts.printLog(28);
      }
      else
      {
        utils->stats.incSTR(1);
        utils->texts.printLog(27);
      }

      utils->stats.counter.utils++;
      return false;
    }
    else
    {
      utils->texts.printLog(34);
      return true;
    }
  }

  void attackAttempt(Utils *utils, Dungeon *dungeon)
  {
    uint8_t additionalDamage = 0;
    uint8_t baseDamage = utils->stats.getSTR();

    if (rand() % 2 == 0)
    {
      utils->stats.hit();
      utils->texts.printLog(18);
    }
    else
    {
      utils->texts.printLog(19);
    }

    if (utils->stats.discardItem(4))
    {
      additionalDamage = 2;
    }

    if (utils->stats.getSTR() == 0)
    {
      utils->texts.printLog(20);
    }

    if (utils->stats.getStatusText() == 0)
    {
      utils->texts.printLog(80);
      baseDamage = utils->stats.getSTR() * ((rand() % 2) + 2);
    }

    dungeon->monster.hitEnemy(baseDamage + additionalDamage);
  }

  bool usePotionAttempt(Utils *utils)
  {
    if (utils->stats.discardItem(8))
    {
      if (rand() % 2 == 0)
      {
        utils->stats.incHP(1);
        utils->texts.printLog(17);
      }
      else
      {
        switch (rand() % 4)
        {
        case 0:
          utils->stats.incHP(2);
          utils->texts.printLog(23);
          break;
        case 1:
          utils->stats.incSTR(1);
          utils->texts.printLog(24);
          break;
        case 2:
          utils->stats.incDEF(1);
          utils->texts.printLog(25);
          break;
        case 3:
          utils->stats.incDEF(2);
          utils->texts.printLog(26);
          break;
        }
      }
      utils->stats.counter.utils++;
      return false;
    }
    else
    {
      utils->texts.printLog(16);
      return true;
    }
  }

  bool escapeAttempt(Utils *utils, Dungeon *dungeon)
  {
    if (!dungeon->monster.canBeSpare())
    {
      utils->texts.printLog(36);
      utils->koBeep();
      return true;
    }

    if (rand() % 5 > 0)
    {
      utils->texts.printLog(14);
      utils->stats.hit();
      return true;
    }

    utils->stats.counter.escaped++;
    utils->texts.printLog(15);
    return false;
  }
};
