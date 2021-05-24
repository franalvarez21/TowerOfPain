#pragma once

struct Text
{
  Utils *utils;
  uint8_t log;
  bool mode = true;

  void init(Utils *utils)
  {
    this->utils = utils;
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

  void printCommonLine(uint8_t line)
  {
    char tBuffer[10];
    utils->tinyfont->print(strcpy_P(tBuffer, (char *)pgm_read_word(&(Commonlines::commonLines[line]))));
  }

  void printStoryLine(uint8_t line)
  {
    char tBuffer[30];
    utils->tinyfont->print(strcpy_P(tBuffer, (char *)pgm_read_word(&(Storylines::storyLines[line]))));
  }

  void print(size_t level)
  {
    if (mode)
    {
      utils->tinyfont->setCursor(0, 60);
      printStoryLine(log);
    }
    else
    {
      utils->tinyfont->setCursor(0, 60);
      printStoryLine(0);
      utils->tinyfont->setCursor(100, 60);
      utils->tinyfont->print(level);
    }
  }

  void printStats(Stats *stats)
  {
    utils->tinyfont->setCursor(92, 2);
    utils->tinyfont->print(stats->getHP());
    utils->tinyfont->setCursor(92, 10);
    utils->tinyfont->print(stats->getSTR());
    utils->tinyfont->setCursor(92, 18);
    utils->tinyfont->print(stats->getDEF());

    utils->tinyfont->setCursor(100, 2);
    printCommonLine(1);
    utils->tinyfont->setCursor(100, 10);
    printCommonLine(2);
    utils->tinyfont->setCursor(100, 18);
    printCommonLine(3);

    utils->tinyfont->setCursor(92, 26);
    printCommonLine(stats->getSlotText(0));
    utils->tinyfont->setCursor(92, 34);
    printCommonLine(stats->getSlotText(1));
    utils->tinyfont->setCursor(92, 42);
    printCommonLine(stats->getSlotText(2));

    utils->tinyfont->setCursor(92, 50);
    printCommonLine(stats->getStatusText());
  }
};
