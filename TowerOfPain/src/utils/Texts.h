#pragma once

struct Texts
{
  Tinyfont tinyfont = Tinyfont(Arduboy2::sBuffer, Arduboy2::width(), Arduboy2::height());
  uint8_t log;
  bool mode = true;

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
    tinyfont.setCursor(x, y);
    tinyfont.print(strcpy_P(tBuffer, (char *)pgm_read_word(&(Commonlines::commonLines[line]))));
  }

  void printStoryLine(uint8_t x, uint8_t y, uint8_t line)
  {
    char tBuffer[30];
    tinyfont.setCursor(x, y);
    tinyfont.print(strcpy_P(tBuffer, (char *)pgm_read_word(&(Storylines::storyLines[line]))));
  }

  void printValue(uint8_t x, uint8_t y, size_t value)
  {
    tinyfont.setCursor(x, y);
    tinyfont.print(value);
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

  void printStats(Stats *stats)
  {
    stats->tick();
    if (stats->cycleAnimation > 0 && stats->cycleAnimation % 2 == 0)
    {
      if (stats->affectedItem != 0)
      {
        printMainSlotStats(107, 1, stats->getHP(), Common::heart);
      }

      if (stats->affectedItem != 1)
      {
        printMainSlotStats(107, 8, stats->getDEF(), Common::shield_1);
      }

      if (stats->affectedItem != 2)
      {
        printMainSlotStats(107, 15, stats->getSTR(), Common::strength);
      }
    }
    else
    {
      printMainSlotStats(107, 1, stats->getHP(), Common::heart);
      printMainSlotStats(107, 8, stats->getDEF(), Common::shield_1);
      printMainSlotStats(107, 15, stats->getSTR(), Common::strength);
    }
    printSlotStats(107, 24, stats);
  }

  void printMainSlotStats(int8_t x, uint8_t y, uint8_t amount, const uint8_t image[])
  {
    Arduboy2Base::drawBitmap(x, y, image, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    printCommonLine(x + 10, y + 1, 29);
    printValue(x + 16, y + 1, amount);
  }

  void printSlotStats(uint8_t x, uint8_t y, Stats *stats)
  {
    for (uint8_t i = 0; i < ITEM_AMOUNT; i++)
    {
      printIconStats(x, y + (i * 8), stats->slots[i].type);
      if (stats->slots[i].amount > 1)
      {
        printCommonLine(x + 10, y + (i * 8) + 2, 29);
        printValue(x + 16, y + (i * 8) + 2, stats->slots[i].amount);
      }
    }
  }

  void printIconStats(uint8_t x, uint8_t y, uint8_t item)
  {
    switch (item)
    {
    case 4:
      Arduboy2Base::drawBitmap(x, y, Common::sword, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 5:
      Arduboy2Base::drawBitmap(x, y, Common::shield_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 7:
      Arduboy2Base::drawBitmap(x, y, Common::relic, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 8:
      Arduboy2Base::drawBitmap(x, y, Common::potion, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    }
  }
};
