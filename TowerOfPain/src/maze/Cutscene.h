
class Cutscene
{
protected:
  Utils *utils;
  size_t timer;
  bool gameOver;

public:
  void init(Utils *utils)
  {
    this->utils = utils;
  }

  void start(const bool gameOver)
  {
    timer = CUTSCENE_TIMER;
    this->gameOver = gameOver;
  }

  bool enabled()
  {
    return (timer == 0);
  }

  void eventDisplay(Stats *stats, Text *text, const size_t monsterType, const size_t level)
  {
    printContinue(text);
    printPlayerFrame();

    if (gameOver)
    {
      text->printStoryLine(40, 8, 41);
      text->printStoryLine(40, 16, 43);
      text->printStoryLine(40, 24, 42);
      text->printStoryLine(40, 32, 44);
      text->printValue(100, 32, level);
    }
    else
    {
      switch (stats->getStatusText())
      {
      case 0: // Strong
        text->printStoryLine(40, 8, 37);
        break;
      case 1: //Resourceful
        text->printStoryLine(40, 8, 38);
        break;
      case 2: // Wise
        text->printStoryLine(40, 8, 39);
        break;
      case 3: // Hopeful
        text->printStoryLine(40, 8, 40);
        break;
      }

      switch (monsterType)
      {
      case 0 ... 1: // Slime
        text->printStoryLine(40, 24, 45);
        break;
      case 3: // Metal
        text->printStoryLine(40, 24, 47);
        break;
      default: // Cold
        text->printStoryLine(40, 24, 46);
        break;
      }

      text->printStoryLine(40, 16, 42);
      text->printStoryLine(40, 32, 42);
    }
  }

private:
  void printContinue(Text *text)
  {
    if (enabled())
    {
      text->printCommonLine(80, 52, 28);
    }
    else
    {
      timer--;
    }
  }

  void printPlayerFrame()
  {
    if (gameOver)
    {
      utils->arduboy->drawBitmap(4, 4, Character::framePlayer3, 32, 48, WHITE);
    }
    else
    {
      if (utils->cycle <= 5)
      {
        utils->arduboy->drawBitmap(4, 4, Character::framePlayer1, 32, 48, WHITE);
      }
      else
      {
        utils->arduboy->drawBitmap(4, 4, Character::framePlayer2, 32, 48, WHITE);
      }
    }
  }
};
