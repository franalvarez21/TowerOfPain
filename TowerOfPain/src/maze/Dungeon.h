
#include "Monster.h"
#include "Cutscene.h"

class Dungeon
{
public:
  size_t level;
  size_t lastCutscene;
  bool keyNeeded;
  Cutscene cutscene;
  Monster monster;

protected:
  uint8_t map[SQUARE_AMOUNT_WEIGHT][SQUARE_AMOUNT_HEIGHT];
  uint8_t playerXPosition;
  uint8_t playerYPosition;
  uint8_t speedTick;
  bool justPressedLock;

public:
  void refresh()
  {
    level = 0;
    speedTick = 0;
    lastCutscene = 0;
    reset();
  }

  void cutsceneStart(const bool refresh, const bool start)
  {
    monster.refresh(refresh);
    cutscene.start(start);
    lastCutscene = level;
  }

  bool canContinue()
  {
    return !keyNeeded;
  }

  void keyFound()
  {
    keyNeeded = false;
  }

  bool cutsceneDone()
  {
    return lastCutscene == level;
  }

  uint8_t movePlayer()
  {
    validMap();

    if (pressed(RIGHT_BUTTON))
    {
      return move(1, 0);
    }

    if (pressed(LEFT_BUTTON))
    {
      return move(-1, 0);
    }

    if (pressed(DOWN_BUTTON))
    {
      return move(0, 1);
    }

    if (pressed(UP_BUTTON))
    {
      return move(0, -1);
    }

    return 0;
  }

  bool moveLeft(uint8_t key)
  {
    if (playerXPosition - 1 > 0)
    {
      if (map[playerXPosition - 1][playerYPosition] == key)
      {
        playerXPosition--;
        return true;
      }
    }
    return false;
  }

  bool moveRight(uint8_t key)
  {
    if (playerXPosition + 1 < SQUARE_AMOUNT_WEIGHT - 1)
    {
      if (map[playerXPosition + 1][playerYPosition] == key)
      {
        playerXPosition++;
        return true;
      }
    }
    return false;
  }

  bool moveTop(uint8_t key)
  {
    if (playerYPosition - 1 > 0)
    {
      if (map[playerXPosition][playerYPosition - 1] == key)
      {
        playerYPosition--;
        return true;
      }
    }
    return false;
  }

  bool moveDown(uint8_t key)
  {
    if (playerYPosition + 1 < SQUARE_AMOUNT_HEIGHT - 1)
    {
      if (map[playerXPosition][playerYPosition + 1] == key)
      {
        playerYPosition++;
        return true;
      }
    }
    return false;
  }

  bool moveWalker(uint8_t key)
  {
    uint8_t can_continue = 10;
    bool move = false;

    while (!move && can_continue > 0)
    {
      switch (rand() % 4)
      {
      case 0:
        move = moveTop(key);
        break;
      case 1:
        move = moveRight(key);
        break;
      case 2:
        move = moveDown(key);
        break;
      case 3:
        move = moveLeft(key);
        break;
      }
      can_continue--;
    }
    return move;
  }

  uint8_t environmentChange(Utils *utils)
  {
    uint8_t event = 0;

    enemyChange(utils);

    for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
    {
      for (uint8_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
      {
        if (map[i][j] > ENEMY_NUMBER_ACTION)
        {
          if (map[i][j] > ENEMY_NUMBER_ACTION + 1)
          {
            event = ENEMY_NUMBER_ACTION;
          }
          map[i][j] = ENEMY_NUMBER_ACTION;
        }
      }
    }

    return event;
  }

  void reset()
  {
    justPressedLock = true;

    clearMap();
    clearPlayerPosition();

    map[playerXPosition][playerYPosition] = 1;

    walkerCircle();

    playerBorders(0);

    spawnObjects();

    playerBorders(1);
  }

  void canvas(uint8_t weight = SQUARE_AMOUNT_WEIGHT, uint8_t height = SQUARE_AMOUNT_HEIGHT)
  {
    Arduboy2Base::drawBitmap(0, 0, Map::map_top_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (weight - 2), 0, Map::map_top_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(0, SQUARE_SIZE * (height - 2), Map::map_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (weight - 2), SQUARE_SIZE * (height - 2), Map::map_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);

    for (uint8_t x = 1; x < weight - 2; x++)
    {
      Arduboy2Base::drawBitmap(x * SQUARE_SIZE, 0, Map::map_top, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      Arduboy2Base::drawBitmap(x * SQUARE_SIZE, SQUARE_SIZE * (height - 2), Map::map_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }

    for (uint8_t y = 1; y < height - 2; y++)
    {
      Arduboy2Base::drawBitmap(0, y * SQUARE_SIZE, Map::map_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (weight - 2), y * SQUARE_SIZE, Map::map_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void completeCanvas()
  {
    canvas(MAX_SQUARE_AMOUNT_WEIGHT, MAX_SQUARE_AMOUNT_HEIGHT);
  }

  void display(Utils *utils)
  {
    displayPlayer(utils);
    for (uint8_t x = 1; x < SQUARE_AMOUNT_WEIGHT - 1; x++)
    {
      for (uint8_t y = 1; y < SQUARE_AMOUNT_HEIGHT - 1; y++)
      {
        displayElements(utils, x, y);
        displayMaze(x, y);
      }
    }
  }

private:
  bool pressed(uint8_t button)
  {
    if (justPressedLock)
    {
      if (Arduboy2Base::justPressed(button))
      {
        justPressedLock = false;
        return true;
      }
    }
    else
    {
      if (Arduboy2Base::justPressed(button) || (Arduboy2Base::pressed(button) && speedTick == 0))
      {
        speedTick = 2;
        return true;
      }
      else if (Arduboy2Base::pressed(button) && speedTick > 0)
      {
        speedTick--;
      }
    }
    return false;
  }

  void moveEnemy(uint8_t x, uint8_t y, uint8_t i, uint8_t j)
  {
    map[x][y] = 1;
    if (!(i == playerXPosition && j == playerYPosition))
    {
      map[i][j] = ENEMY_NUMBER_ACTION + 1;
    }
    else
    {
      map[i][j] = ENEMY_NUMBER_ACTION + 2;
    }
  }

  void enemyChange(Utils *utils)
  {
    for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
    {
      for (uint8_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
      {
        if (map[i][j] == ENEMY_NUMBER_ACTION)
        {
          if (utils->sizeTypeAbs(playerXPosition, i) < 4 && utils->sizeTypeAbs(playerYPosition, j) < 4 && (rand() % 4 < 3))
          {
            if (playerXPosition < i && map[i - 1][j] == 1)
            {
              moveEnemy(i, j, i - 1, j);
            }
            else if (playerXPosition > i && map[i + 1][j] == 1)
            {
              moveEnemy(i, j, i + 1, j);
            }
            else if (playerYPosition < j && map[i][j - 1] == 1)
            {
              moveEnemy(i, j, i, j - 1);
            }
            else if (playerYPosition > j && map[i][j + 1] == 1)
            {
              moveEnemy(i, j, i, j + 1);
            }
          }
          else
          {
            switch (rand() % 4)
            {
            case 0:
              if (map[i - 1][j] == 1)
              {
                moveEnemy(i, j, i - 1, j);
              }
              break;
            case 1:
              if (map[i + 1][j] == 1)
              {
                moveEnemy(i, j, i + 1, j);
              }
              break;
            case 2:
              if (map[i][j - 1] == 1)
              {
                moveEnemy(i, j, i, j - 1);
              }
              break;
            case 3:
              if (map[i][j + 1] == 1)
              {
                moveEnemy(i, j, i, j + 1);
              }
              break;
            }
          }
        }
      }
    }
  }

  void validMap()
  {
    for (uint8_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
    {
      map[i][0] = 0;
      map[i][SQUARE_AMOUNT_HEIGHT - 1] = 0;
    }
    for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
    {
      map[0][j] = 0;
      map[SQUARE_AMOUNT_WEIGHT - 1][j] = 0;
    }
  }

  void clearPlayerPosition()
  {
    playerXPosition = 6;
    playerYPosition = 3;
  }

  void clearMap()
  {
    for (uint8_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
    {
      for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
      {
        map[i][j] = 0;
      }
    }
  }

  void walkerCircle()
  {
    for (uint8_t i = 0; i < WALKER_CYCLES; i++)
    {
      if (!moveWalker(0))
      {
        moveWalker(1);
      }

      map[playerXPosition][playerYPosition] = 1;
    }

    clearPlayerPosition();
  }

  void spawnObjects()
  {
    keyNeeded = false;
    if (level < MAX_LEVEL)
    {
      spawnObject(2);
      if (rand() % 2 == 0)
      {
        spawnObject(3 + (rand() % 6));
      }
      if (level > 0)
      {
        for (uint8_t i = 0; i < (1 + rand() % MAX_ENEMY_AMOUNT); i++)
        {
          spawnObject(ENEMY_NUMBER_ACTION);
        }

        if (rand() % 3 == 0)
        {
          if (spawnObject(9))
          {
            keyNeeded = true;
          }
        }
      }
    }
  }

  bool spawnObject(uint8_t item)
  {
    switch (rand() % 4)
    {
    case 0:
      for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
      {
        for (uint8_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 1:
      for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
      {
        for (uint8_t j = SQUARE_AMOUNT_HEIGHT - 2; j > 0; j--)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 2:
      for (uint8_t i = SQUARE_AMOUNT_WEIGHT - 2; i > 0; i--)
      {
        for (uint8_t j = SQUARE_AMOUNT_HEIGHT - 2; j > 0; j--)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 3:
      for (uint8_t i = SQUARE_AMOUNT_WEIGHT - 2; i > 0; i--)
      {
        for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    }

    return false;
  }

  bool canSetItem(uint8_t i, uint8_t j)
  {
    return (map[i][j] == 1 && map[i - 1][j] < 2 && map[i][j - 1] < 2 && map[i + 1][j] < 2 && map[i][j + 1] < 2);
  }

  void displayPlayer(Utils *utils)
  {
    if (utils->cycle <= 5)
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition - 4, SQUARE_SIZE * playerYPosition - 4, MiniCharacter::player_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition - 4, SQUARE_SIZE * playerYPosition - 4, MiniCharacter::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void displayElements(Utils *utils, uint8_t x, uint8_t y)
  {
    if (!(x == playerXPosition && y == playerYPosition))
    {
      switch (map[x][y])
      {
      case 2:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::door, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 3:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::chest, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 4:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::sword, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 5:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::shield_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 6:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::heart, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 7:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::relic, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 8:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::potion, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 9:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::key, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 10:
        monster.displayIn(utils, x, y);
        break;
      }
    }
  }

  void displayMaze(uint8_t x, uint8_t y)
  {
    validMap();
    if (map[x][y] > 0)
    {
      if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_bottom_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
    }
    else
    {
      monster.displayEnvironmentIn(x, y);
    }
    validMap();
  }

  void playerBorders(uint8_t value)
  {
    for (uint8_t x = 0; x < 3; x++)
    {
      for (uint8_t y = 0; y < 3; y++)
      {
        map[playerXPosition + (1 - x)][playerYPosition + (1 - y)] = value;
      }
    }
  }

  uint8_t move(const int extX, const int extY)
  {
    uint8_t value = map[playerXPosition + extX][playerYPosition + extY];
    if (value > 0)
    {
      if (map[playerXPosition][playerYPosition] > 2)
      {
        map[playerXPosition][playerYPosition] = 1;
      }
      playerXPosition += extX;
      playerYPosition += extY;
      if (value > 2)
      {
        map[playerXPosition][playerYPosition] = 1;
      }
      return value;
    }
    return 0;
  }
};
