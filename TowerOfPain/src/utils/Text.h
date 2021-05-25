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

  void printCommonLine(size_t x, size_t y, uint8_t line)
  {
    char tBuffer[10];
    tinyfont->setCursor(x, y);
    tinyfont->print(strcpy_P(tBuffer, (char *)pgm_read_word(&(Commonlines::commonLines[line]))));
  }

  void printStoryLine(size_t x, size_t y, uint8_t line)
  {
    char tBuffer[30];
    tinyfont->setCursor(x, y);
    tinyfont->print(strcpy_P(tBuffer, (char *)pgm_read_word(&(Storylines::storyLines[line]))));
  }

  void printValue(size_t x, size_t y, size_t value)
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
      printValue(100, 60, level);
    }
  }

  void printStats(Stats *stats)
  {
    printValue(92, 2, stats->getHP());
    printValue(92, 10, stats->getSTR());
    printValue(92, 18, stats->getDEF());

    printCommonLine(100, 2, 1);
    printCommonLine(100, 10, 2);
    printCommonLine(100, 18, 3);

    printCommonLine(92, 26, stats->getSlotText(0));
    printCommonLine(92, 34, stats->getSlotText(1));
    printCommonLine(92, 42, stats->getSlotText(2));

    printCommonLine(92, 50, stats->getStatusText());
  }
};
