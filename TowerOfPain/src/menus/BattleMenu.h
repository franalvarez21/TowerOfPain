#pragma once

class BattleMenu : public Menu
{
protected:
  uint8_t menu;

public:
  BattleMenu() : Menu(3){};

  void refresh()
  {
    menu = 0;
    option = 0;
  }

  bool action(Utils *utils, Text *text, Stats *stats, Dungeon *dungeon, ArduboyTones *soundtones)
  {
    upDownMovement(utils);

    if (okMovement(utils))
    {
      if (option == 3)
      {
        switch (menu)
        {
        case 0:
          if (escapeAttempt(utils, text, stats, dungeon, soundtones))
          {
            utils->koBeep(soundtones);
          }
          else
          {
            utils->okBeep(soundtones);
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
        case 1:
          if (dungeon->monster.currentType < 3)
          {
            utils->koBeep(soundtones);
            text->printLog(55);
          }
          else
          {
            menu++;
          }
          break;
        case 2:
          if (useExplainAttempt(stats, text, dungeon))
          {
            utils->koBeep(soundtones);
          }
          else
          {
            utils->okBeep(soundtones);
            return false;
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
          if (useSpareAttempt(stats, text, dungeon))
          {
            utils->koBeep(soundtones);
          }
          else
          {
            utils->okBeep(soundtones);
            return false;
          }
          break;
        case 1:
          if (useRelicAttempt(stats, text, dungeon))
          {
            utils->koBeep(soundtones);
          }
          else
          {
            utils->okBeep(soundtones);
          }
          break;
        default:
          if (useApproachAttempt(stats, text, dungeon))
          {
            utils->koBeep(soundtones);
          }
          else
          {
            utils->okBeep(soundtones);
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
          attackAttempt(stats, text, dungeon);
          utils->okBeep(soundtones);
          break;
        case 1:
          if (usePotionAttempt(stats, text))
          {
            utils->koBeep(soundtones);
          }
          else
          {
            utils->okBeep(soundtones);
          }
          break;
        default:
          if (useThreatAttempt(stats, text, dungeon))
          {
            utils->koBeep(soundtones);
          }
          else
          {
            utils->okBeep(soundtones);
            return false;
          }
          break;
        }
      }
    }

    if (menu > 0 && koMovement(utils))
    {
      menu--;
    }

    if (dungeon->monster.life < 1)
    {
      utils->okBeep(soundtones);
      stats->counter.killed++;
      return false;
    }

    return true;
  }

  void eventDisplay(Utils *utils, Text *text, Dungeon *dungeon)
  {
    dungeon->monster.displayFrame(utils);
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
      text->printCommonLine(48, 20, 27);
      text->printCommonLine(48, 28, 28);
      text->printCommonLine(48, 36, 29);
      text->printCommonLine(48, 44, 15);
      break;
    }

    displayMenuCursor(text, 40, 20);
  }

private:
  bool useThreatAttempt(Stats *stats, Text *text, Dungeon *dungeon)
  {
    if (stats->getStatusText() == 0 && !dungeon->monster.canBeSpare())
    {
      switch (rand() % 7)
      {
      case 0: // "YELLS BACK";
        text->printLog(57);
        stats->hit();
        return true;
      case 1: // "ATTACKS, HP DOWN";
        stats->hit();
        text->printLog(58);
        return true;
      case 2: // "ATTACKS, DEF DOWN";
        stats->decDEF(1);
        stats->hit();
        text->printLog(59);
        return true;
      case 3: // "FAINTS";
        text->printLog(60);
        return false;
      case 4: // "AFRAID, DEF UP";
        stats->incDEF(1);
        text->printLog(61);
        return false;
      case 5: // "SCARE, DEF UP";
        stats->incDEF(1);
        text->printLog(62);
        return false;
      default: // "HITS AND RUNS";
        text->printLog(63);
        stats->hit();
        return false;
      }
    }
    text->printLog(56);
    return true;
  }

  bool useApproachAttempt(Stats *stats, Text *text, Dungeon *dungeon)
  {
    if (stats->getStatusText() == 1 && !dungeon->monster.canBeSpare())
    {
      switch (rand() % 7)
      {
      case 0: // "ATTACKS, STR DOWN";
        stats->decSTR(1);
        stats->hit();
        text->printLog(65);
        return true;
      case 1: // "IS AFRAID";
        text->printLog(66);
        return true;
      case 2: // "STEALS FROM YOU";
        if (!stats->discardItem(8))
        {
          stats->discardItem(7);
        }
        text->printLog(67);
        return true;
      case 3: // "GIVES YOU A POTION";
        stats->addItem(8);
        text->printLog(68);
        return false;
      case 4: // "GIVES A RELIC";
        stats->addItem(7);
        text->printLog(69);
        return false;
      case 5: // "HIT AND RUNS";
        text->printLog(70);
        stats->hit();
        return false;
      default: // "HIT AND ESCAPE";
        text->printLog(71);
        stats->hit();
        return false;
      }
    }
    text->printLog(64);
    return true;
  }

  bool useExplainAttempt(Stats *stats, Text *text, Dungeon *dungeon)
  {
    if (stats->getStatusText() == 2 && !dungeon->monster.canBeSpare())
    {
      switch (rand() % 7)
      {
      case 0: // "ATTACKS, DEF DOWN";
        stats->decDEF(1);
        stats->hit();
        text->printLog(73);
        return true;
      case 1: // "ATTACKS";
        stats->hit();
        text->printLog(74);
        return true;
      case 2: // "ACCEPTS, RELIC FOUND";
        stats->addItem(7);
        text->printLog(75);
        return false;
      case 3: // "NODS, GIVES POTION";
        stats->addItem(8);
        text->printLog(76);
        return false;
      case 4: // "LEAVES IN ANGER";
        text->printLog(77);
        stats->hit();
        return false;
      case 5: // "UNDERSTAND";
        text->printLog(78);
        return true;
      default: // "HIT AND RUNS";
        text->printLog(79);
        stats->hit();
        return false;
      }
    }
    text->printLog(72);
    return true;
  }

  bool useSpareAttempt(Stats *stats, Text *text, Dungeon *dungeon)
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

  bool useRelicAttempt(Stats *stats, Text *text, Dungeon *dungeon)
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

  void attackAttempt(Stats *stats, Text *text, Dungeon *dungeon)
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

    if (stats->getSTR() == 0)
    {
      text->printLog(20);
    }

    dungeon->monster.hitEnemy(stats->getSTR() + additionalDamage);
  }

  bool usePotionAttempt(Stats *stats, Text *text)
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

  bool escapeAttempt(Utils *utils, Text *text, Stats *stats, Dungeon *dungeon, ArduboyTones *soundtones)
  {
    if (!dungeon->monster.canBeSpare())
    {
      text->printLog(36);
      utils->koBeep(soundtones);
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
