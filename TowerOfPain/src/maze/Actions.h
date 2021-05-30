
class Actions
{
public:
  bool evaluateAction(Utils *utils, Text *text, Stats *stats, Dungeon *dungeon, uint8_t action, ArduboyTones *soundtones)
  {
    switch (action)
    {
    case 1:
      if (dungeon->environmentChange(utils) == ENEMY_NUMBER_ACTION)
      {
        text->printLog(8);
        return true;
      }
      break;
    case 2:
      if (dungeon->canContinue())
      {
        dungeon->increaseLevel();
        dungeon->reset();
        text->printLevel();
        stats->incMaxLevelReached(dungeon->level);
      }
      else
      {
        utils->subtleKoBeep(soundtones);
      }
      break;
    case 3:
      if (randomItem(text, stats))
      {
        utils->subtleOkBeep(soundtones);
      }
      else
      {
        utils->subtleKoBeep(soundtones);
      }
      break;
    case 4:
      if (stats->addItem(4))
      {
        text->printLog(2);
        utils->subtleOkBeep(soundtones);
      }
      else
      {
        text->printLog(3);
        utils->subtleKoBeep(soundtones);
      }
      break;
    case 5:
      if (stats->addItem(5))
      {
        text->printLog(4);
        utils->subtleOkBeep(soundtones);
      }
      else
      {
        text->printLog(3);
        utils->subtleKoBeep(soundtones);
      }
      break;
    case 6:
      stats->incHP(1);
      text->printLog(5);
      utils->subtleOkBeep(soundtones);
      break;
    case 7:
      if (stats->addItem(7))
      {
        text->printLog(6);
        utils->subtleOkBeep(soundtones);
      }
      else
      {
        text->printLog(3);
        utils->subtleKoBeep(soundtones);
      }
      break;
    case 8:
      if (stats->addItem(8))
      {
        text->printLog(7);
        utils->subtleOkBeep(soundtones);
      }
      else
      {
        text->printLog(3);
        utils->subtleKoBeep(soundtones);
      }
      break;
    case 9:
      dungeon->keyFound();
      text->printLog(52);
      utils->subtleOkBeep(soundtones);
      break;
    case 10:
      text->printLog(8);
      break;
    default:
      break;
    }

    return (action == ENEMY_NUMBER_ACTION);
  }

private:
  bool randomItem(Text *text, Stats *stats)
  {
    text->printLog(9);
    switch (rand() % 4)
    {
    case 0:
      if (stats->addItem(4))
      {
        text->printLog(10);
        return true;
      }
      break;
    case 1:
      if (stats->addItem(5))
      {
        text->printLog(11);
        return true;
      }
      break;
    case 2:
      if (stats->addItem(7))
      {
        text->printLog(12);
        return true;
      }
      break;
    case 3:
      if (stats->addItem(8))
      {
        text->printLog(13);
        return true;
      }
      break;
    }
    return false;
  }
};
