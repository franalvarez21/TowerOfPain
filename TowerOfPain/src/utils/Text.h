#pragma once

struct Text
{
  Tinyfont *tinyfont;
  uint8_t log;
  bool mode = true;

  void init(Tinyfont *tinyfont)
  {
    this->tinyfont = tinyfont;
  }

  void printLog(uint8_t pos)
  {
    log = pos;
    mode = true;
  }

  void printLevel()
  {
    mode = false;
  }

  void printCommonLine(uint8_t x, uint8_t y, uint8_t line)
  {
    char tBuffer[10];
    tinyfont->setCursor(x, y);
    tinyfont->print(strcpy_P(tBuffer, (char *)pgm_read_word(&(Commonlines::commonLines[line]))));
  }

  void printStoryLine(uint8_t x, uint8_t y, uint8_t line)
  {
    char tBuffer[30];
    tinyfont->setCursor(x, y);
    tinyfont->print(strcpy_P(tBuffer, (char *)pgm_read_word(&(Storylines::storyLines[line]))));
  }

  void printValue(uint8_t x, uint8_t y, size_t value)
  {
    tinyfont->setCursor(x, y);
    tinyfont->print(value);
  }

  void print(size_t level)
  {
    if (mode)
    {
      printStoryLine(0, 60, log);
    }
    else
    {
      printStoryLine(0, 60, 0);
      printValue(60, 60, level);
    }
  }

  void printStats(Stats *stats, Utils *utils)
  {
    stats->giveFeedback(utils);

    printValue(100, 2, stats->getHP());
    printValue(100, 9, stats->getSTR());
    printValue(100, 16, stats->getDEF());

    printCommonLine(108, 2, 1);
    printCommonLine(108, 9, 2);
    printCommonLine(108, 16, 3);

    printSlotStats(utils, 99, 24, &stats->slots[0]);
    printSlotStats(utils, 99, 32, &stats->slots[1]);
    printSlotStats(utils, 99, 40, &stats->slots[2]);
    printSlotStats(utils, 99, 48, &stats->slots[3]);
  }

  void printSlotStats(Utils *utils, uint8_t x, uint8_t y, Item *item)
  {
    printIconStats(utils, x, y, item->type);
    if (item->amount > 1)
    {
      printCommonLine(x + 10, y + 2, 30);
      printValue(x + 16, y + 2, item->amount);
    }
  }

  void printIconStats(Utils *utils, uint8_t x, uint8_t y, uint8_t item)
  {
    switch (item)
    {
    case 4:
      utils->arduboy->drawBitmap(x, y, Common::sword, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 5:
      utils->arduboy->drawBitmap(x, y, Common::shield, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 7:
      utils->arduboy->drawBitmap(x, y, Common::relic, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 8:
      utils->arduboy->drawBitmap(x, y, Common::potion, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    }
  }
};
