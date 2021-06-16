
class Cutscene
{
protected:
  uint8_t timer;
  bool gameOver;

public:
  void start(const bool gameOver)
  {
    timer = CUTSCENE_TIMER;
    this->gameOver = gameOver;
  }

  bool enabled()
  {
    return (timer == 0);
  }

  void eventDisplay(Utils *utils, const uint8_t monsterType, const size_t level)
  {
    printPlayerFrame(utils);

    if (level == MAX_LEVEL)
    {
      utils->texts.printStoryLine(40, 8, 53);
      utils->texts.printStoryLine(40, 16, 54);
      utils->texts.printStoryLine(40, 24, 42);
      utils->texts.printStoryLine(40, 32, 44);
      utils->texts.printValue(100, 32, level);
    }
    else if (gameOver)
    {
      printContinue(utils);

      utils->texts.printStoryLine(40, 8, 41);
      utils->texts.printStoryLine(40, 16, 43);
      utils->texts.printStoryLine(40, 24, 42);
      utils->texts.printStoryLine(40, 32, 44);
      utils->texts.printValue(100, 32, level);
    }
    else
    {
      printContinue(utils);

      switch (utils->stats.getStatusText())
      {
      case 0: // Strong
        utils->texts.printStoryLine(40, 8, 37);
        break;
      case 1: // Smart
        utils->texts.printStoryLine(40, 8, 38);
        break;
      case 2: // Wise
        utils->texts.printStoryLine(40, 8, 39);
        break;
      case 3: // Hopeful
        utils->texts.printStoryLine(40, 8, 40);
        break;
      }

      switch (monsterType)
      {
      case 0 ... 2: // Slime
        utils->texts.printStoryLine(40, 24, 45);
        break;
      case 3 ... 5: // Eyes
        utils->texts.printStoryLine(40, 24, 49);
        break;
      case 6: // Flowers
        utils->texts.printStoryLine(40, 24, 48);
        break;
      case 7 ... 8: // Careful
        utils->texts.printStoryLine(40, 24, 50);
        break;
      case 9: // Cold
        utils->texts.printStoryLine(40, 24, 46);
        break;
      case 10: // Go Fast
        utils->texts.printStoryLine(40, 24, 51);
        break;
      default: // Metal
        utils->texts.printStoryLine(40, 24, 47);
        break;
      }

      utils->texts.printStoryLine(40, 16, 42);
      utils->texts.printStoryLine(40, 32, 42);
    }
  }

private:
  void printContinue(Utils *utils)
  {
    if (enabled())
    {
      utils->texts.printCommonLine(80, 52, 25);
    }
    else
    {
      timer--;
    }
  }

  void printPlayerFrame(Utils *utils)
  {
    if (gameOver)
    {
      Arduboy2Base::drawBitmap(4, 4, Character::framePlayer3, 32, 48, WHITE);
    }
    else
    {
      if (utils->cycle <= 5)
      {
        Arduboy2Base::drawBitmap(4, 4, Character::framePlayer1, 32, 48, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(4, 4, Character::framePlayer2, 32, 48, WHITE);
      }
    }
  }
};
