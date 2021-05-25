#pragma once

struct Actions
{
  bool evaluateAction(Events *events, Text *text, Stats *stats, Dungeon *dungeon, size_t action)
  {
    switch (action)
    {
    case 1:
      if (dungeon->environmentChange() == 9)
      {
        text->printLog(8);
        action = 9;
      }
      break;
    case 2:
      dungeon->increaseLevel();
      text->printLevel();
      dungeon->reset();
      break;
    case 3:
      randomItem(text, stats);
      break;
    case 4:
      if (stats->addItem(4))
      {
        text->printLog(2);
      }
      else
      {
        text->printLog(3);
      }
      break;
    case 5:
      if (stats->addItem(5))
      {
        text->printLog(4);
      }
      else
      {
        text->printLog(3);
      }
      break;
    case 6:
      stats->incHP(1);
      text->printLog(5);
      break;
    case 7:
      if (stats->addItem(7))
      {
        text->printLog(6);
      }
      else
      {
        text->printLog(3);
      }
      break;
    case 8:
      if (stats->addItem(8))
      {
        text->printLog(7);
      }
      else
      {
        text->printLog(3);
      }
      break;
    case 9:
      text->printLog(8);
      break;
    default:
      break;
    }

    return (action == 9);
  }

  void randomItem(Text *text, Stats *stats)
  {
    text->printLog(9);
    switch (rand() % 4)
    {
    case 0:
      if (stats->addItem(4))
      {
        text->printLog(10);
      }
      break;
    case 1:
      if (stats->addItem(5))
      {
        text->printLog(11);
      }
      break;
    case 2:
      if (stats->addItem(7))
      {
        text->printLog(12);
      }
      break;
    case 3:
      if (stats->addItem(8))
      {
        text->printLog(13);
      }
      break;
    }
  }
};
