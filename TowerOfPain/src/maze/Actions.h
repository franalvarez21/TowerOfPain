
class Actions
{
public:
  bool evaluateAction(Utils *utils, Dungeon *dungeon, uint8_t action)
  {
    switch (action)
    {
    case 1:
      if (dungeon->environmentChange(utils) == ENEMY_NUMBER_ACTION)
      {
        utils->texts.printLog(8);
        return true;
      }
      break;
    case 2:
      if (dungeon->canContinue())
      {
        dungeon->level++;
        dungeon->reset();
        utils->texts.printLevel();
        utils->stats.incMaxLevelReached(dungeon->level);
      }
      else
      {
        utils->texts.printLog(21);
        utils->subtleKoBeep();
      }
      break;
    case 3:
      if (randomItem(utils))
      {
        utils->subtleOkBeep();
      }
      else
      {
        utils->subtleKoBeep();
      }
      break;
    case 4:
      if (utils->stats.addItem(4))
      {
        utils->texts.printLog(2);
        utils->subtleOkBeep();
      }
      else
      {
        utils->texts.printLog(3);
        utils->subtleKoBeep();
      }
      break;
    case 5:
      if (utils->stats.addItem(5))
      {
        utils->texts.printLog(4);
        utils->subtleOkBeep();
      }
      else
      {
        utils->texts.printLog(3);
        utils->subtleKoBeep();
      }
      break;
    case 6:
      utils->stats.incHP(1);
      utils->texts.printLog(5);
      utils->subtleOkBeep();
      break;
    case 7:
      if (utils->stats.addItem(7))
      {
        utils->texts.printLog(6);
        utils->subtleOkBeep();
      }
      else
      {
        utils->texts.printLog(3);
        utils->subtleKoBeep();
      }
      break;
    case 8:
      if (utils->stats.addItem(8))
      {
        utils->texts.printLog(7);
        utils->subtleOkBeep();
      }
      else
      {
        utils->texts.printLog(3);
        utils->subtleKoBeep();
      }
      break;
    case 9:
      dungeon->keyFound();
      utils->texts.printLog(52);
      utils->subtleOkBeep();
      break;
    case 10:
      utils->texts.printLog(8);
      break;
    default:
      break;
    }

    return (action == ENEMY_NUMBER_ACTION);
  }

private:
  bool randomItem(Utils *utils)
  {
    utils->texts.printLog(9);
    switch (rand() % 4)
    {
    case 0:
      if (utils->stats.addItem(4))
      {
        utils->texts.printLog(10);
        return true;
      }
      break;
    case 1:
      if (utils->stats.addItem(5))
      {
        utils->texts.printLog(11);
        return true;
      }
      break;
    case 2:
      if (utils->stats.addItem(7))
      {
        utils->texts.printLog(12);
        return true;
      }
      break;
    case 3:
      if (utils->stats.addItem(8))
      {
        utils->texts.printLog(13);
        return true;
      }
      break;
    }
    return false;
  }
};
