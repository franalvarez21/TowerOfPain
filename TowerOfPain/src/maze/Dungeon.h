
#include "Monster.h"
#include "Cutscene.h"

class Dungeon
{
public:
  size_t level;
  Cutscene cutscene;
  Monster monster;

protected:
  Utils *utils;
  size_t map[SQUARE_AMOUNT_WEIGHT][SQUARE_AMOUNT_HEIGHT];
  size_t playerXPosition;
  size_t playerYPosition;
  size_t speedTick;
  bool justPressedLock;
  size_t lastCutscene;

public:
  void init(Utils *utils)
  {
    this->utils = utils;
    monster.init(utils);
    cutscene.init(utils);
  }

  void refresh()
  {
    level = 0;
    speedTick = 0;
    lastCutscene = 0;
    reset();
  }

  void cutsceneStart(size_t number)
  {
    monster.refresh(number);
    cutscene.start(number);
    lastCutscene = level;
  }

  bool cutsceneDone()
  {
    return lastCutscene == level;
  }

  size_t movePlayer()
  {
    size_t value = 0;

    if (pressed(utils, RIGHT_BUTTON))
    {
      value = map[playerXPosition + 1][playerYPosition];
      if (value == 1)
      {
        map[playerXPosition][playerYPosition] = 1;
        playerXPosition++;
        return 1;
      }
      else if (value > 1)
      {
        map[playerXPosition][playerYPosition] = 1;
        map[playerXPosition + 1][playerYPosition] = 1;
        playerXPosition++;
        return value;
      }
    }

    if (pressed(utils, LEFT_BUTTON))
    {
      value = map[playerXPosition - 1][playerYPosition];
      if (value == 1)
      {
        map[playerXPosition][playerYPosition] = 1;
        playerXPosition--;
        return 1;
      }
      else if (value > 1)
      {
        map[playerXPosition][playerYPosition] = 1;
        map[playerXPosition - 1][playerYPosition] = 1;
        playerXPosition--;
        return value;
      }
    }

    if (pressed(utils, DOWN_BUTTON))
    {
      value = map[playerXPosition][playerYPosition + 1];
      if (value == 1)
      {
        map[playerXPosition][playerYPosition] = 1;
        playerYPosition++;
        return 1;
      }
      else if (value > 1)
      {
        map[playerXPosition][playerYPosition] = 1;
        map[playerXPosition][playerYPosition + 1] = 1;
        playerYPosition++;
        return value;
      }
    }

    if (pressed(utils, UP_BUTTON))
    {
      value = map[playerXPosition][playerYPosition - 1];
      if (value == 1)
      {
        map[playerXPosition][playerYPosition] = 1;
        playerYPosition--;
        return 1;
      }
      else if (value > 1)
      {
        map[playerXPosition][playerYPosition] = 1;
        map[playerXPosition][playerYPosition - 1] = 1;
        playerYPosition--;
        return value;
      }
    }

    return 0;
  }

  bool pressed(Utils *utils, uint8_t button)
  {
    if (justPressedLock)
    {
      if (utils->arduboy->justPressed(button))
      {
        justPressedLock = false;
        return true;
      }
    }
    else
    {
      if (utils->arduboy->justPressed(button) || (utils->arduboy->pressed(button) && speedTick == 0))
      {
        speedTick = 2;
        return true;
      }
      else if (utils->arduboy->pressed(button) && speedTick > 0)
      {
        speedTick--;
      }
    }
    return false;
  }

  bool moveLeft(size_t key)
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

  bool moveRight(size_t key)
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

  bool moveTop(size_t key)
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

  bool moveDown(size_t key)
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

  bool moveWalker(size_t key)
  {
    size_t can_continue = 10;
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

  void increaseLevel()
  {
    level++;
  }

  void moveEnemy(size_t x, size_t y, size_t i, size_t j)
  {
    map[x][y] = 1;
    if (!(i == playerXPosition && j == playerYPosition))
    {
      map[i][j] = 10;
    }
    else
    {
      map[i][j] = 11;
    }
  }

  void enemyChange()
  {
    for (size_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
    {
      for (size_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
      {
        if (map[i][j] == 9)
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

  size_t environmentChange()
  {
    size_t event = 0;

    enemyChange();

    for (size_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
    {
      for (size_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
      {
        if (map[i][j] > 9)
        {
          if (map[i][j] > 10)
          {
            event = 9;
          }
          map[i][j] = 9;
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

    lockPlayerBorders();

    spawnObjects();

    unlockPlayerBorders();
  }

  void clearPlayerPosition()
  {
    playerXPosition = 6;
    playerYPosition = 3;
  }

  void clearMap()
  {
    for (size_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
    {
      for (size_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
      {
        map[i][j] = 0;
      }
    }
  }

  void walkerCircle()
  {
    for (size_t i = 0; i < 35; i++)
    {
      if (!moveWalker(0))
      {
        moveWalker(1);
      }

      map[playerXPosition][playerYPosition] = 1;
    }

    clearPlayerPosition();
  }

  bool setItem(size_t item, size_t i, size_t j)
  {
    if (map[i][j] == 1 && map[i - 1][j] < 2 && map[i][j - 1] < 2 && map[i + 1][j] < 2 && map[i][j + 1] < 2)
    {
      map[i][j] = item;
      return true;
    }
    return false;
  }

  void spawnObjects()
  {
    if (level < MAX_LEVEL)
    {
      spawnObject(2);
      if (rand() % 2 == 0)
      {
        spawnObject(3 + (rand() % 6));
      }
      if (level > 0)
      {
        for (size_t i = 0; i < (1 + rand() % MAX_ENEMY_AMOUNT); i++)
        {
          spawnObject(9);
        }
      }
    }
  }

  bool spawnObject(size_t item)
  {
    switch (rand() % 4)
    {
    case 0:
      for (size_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
      {
        for (size_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
        {
          if (setItem(item, i, j))
          {
            return true;
          }
        }
      }
      return false;
    case 1:
      for (size_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
      {
        for (size_t j = SQUARE_AMOUNT_HEIGHT - 2; j > 0; j--)
        {
          if (setItem(item, i, j))
          {
            return true;
          }
        }
      }
      return false;
    case 2:
      for (size_t i = SQUARE_AMOUNT_WEIGHT - 2; i > 0; i--)
      {
        for (size_t j = SQUARE_AMOUNT_HEIGHT - 2; j > 0; j--)
        {
          if (setItem(item, i, j))
          {
            return true;
          }
        }
      }
      return false;
    case 3:
      for (size_t i = SQUARE_AMOUNT_WEIGHT - 2; i > 0; i--)
      {
        for (size_t j = 0; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
        {
          if (setItem(item, i, j))
          {
            return true;
          }
        }
      }
      return false;
    }
  }

  void canvas(size_t weight = SQUARE_AMOUNT_WEIGHT, size_t height = SQUARE_AMOUNT_HEIGHT)
  {
    utils->arduboy->drawBitmap(0, 0, Map::map_top_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    utils->arduboy->drawBitmap(SQUARE_SIZE * (weight - 2), 0, Map::map_top_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    utils->arduboy->drawBitmap(0, SQUARE_SIZE * (height - 2), Map::map_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    utils->arduboy->drawBitmap(SQUARE_SIZE * (weight - 2), SQUARE_SIZE * (height - 2), Map::map_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);

    for (size_t x = 1; x < weight - 2; x++)
    {
      utils->arduboy->drawBitmap(x * SQUARE_SIZE, 0, Map::map_top, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      utils->arduboy->drawBitmap(x * SQUARE_SIZE, SQUARE_SIZE * (height - 2), Map::map_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }

    for (size_t y = 1; y < height - 2; y++)
    {
      utils->arduboy->drawBitmap(0, y * SQUARE_SIZE, Map::map_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      utils->arduboy->drawBitmap(SQUARE_SIZE * (weight - 2), y * SQUARE_SIZE, Map::map_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void completeCanvas()
  {
    canvas(MAX_SQUARE_AMOUNT_WEIGHT, MAX_SQUARE_AMOUNT_HEIGHT);
  }

  void display()
  {
    displayPlayer();
    for (size_t x = 1; x < SQUARE_AMOUNT_WEIGHT - 1; x++)
    {
      for (size_t y = 1; y < SQUARE_AMOUNT_HEIGHT - 1; y++)
      {
        displayElements(x, y);
        displayMaze(x, y);
      }
    }
  }

  void displayPlayer()
  {
    if (utils->cycle <= 5)
    {
      utils->arduboy->drawBitmap(SQUARE_SIZE * playerXPosition - 4, SQUARE_SIZE * playerYPosition - 4, Character::player_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      utils->arduboy->drawBitmap(SQUARE_SIZE * playerXPosition - 4, SQUARE_SIZE * playerYPosition - 4, Character::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void displayElements(size_t x, size_t y)
  {
    if (!(x == playerXPosition && y == playerYPosition))
    {
      switch (map[x][y])
      {
      case 2:
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::door, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 3:
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::chest, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 4:
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::sword, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 5:
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::shield, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 6:
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::heart, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 7:
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::relic, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 8:
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Common::potion, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 9:
        monster.displayIn(x, y);
        break;
      default:
        break;
      }
    }
  }

  void displayMaze(size_t x, size_t y)
  {
    if (map[x][y] > 0)
    {
      if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] == 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_bottom_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] == 0 && map[x][y + 1] > 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] > 0 && map[x + 1][y] > 0 && map[x][y - 1] == 0 && map[x][y + 1] == 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_top_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (map[x - 1][y] == 0 && map[x + 1][y] == 0 && map[x][y - 1] > 0 && map[x][y + 1] > 0)
      {
        utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, Map::map_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
    }
    else
    {
      monster.displayEnvironmentIn(x, y);
    }
  }

  void lockPlayerBorders()
  {
    map[playerXPosition][playerYPosition] = 0;
    map[playerXPosition + 1][playerYPosition] = 0;
    map[playerXPosition - 1][playerYPosition] = 0;
    map[playerXPosition][playerYPosition + 1] = 0;
    map[playerXPosition][playerYPosition - 1] = 0;
    map[playerXPosition + 1][playerYPosition + 1] = 0;
    map[playerXPosition + 1][playerYPosition - 1] = 0;
    map[playerXPosition - 1][playerYPosition + 1] = 0;
    map[playerXPosition - 1][playerYPosition - 1] = 0;
  }

  void unlockPlayerBorders()
  {
    map[playerXPosition][playerYPosition] = 1;
    map[playerXPosition + 1][playerYPosition] = 1;
    map[playerXPosition - 1][playerYPosition] = 1;
    map[playerXPosition][playerYPosition + 1] = 1;
    map[playerXPosition][playerYPosition - 1] = 1;
    map[playerXPosition + 1][playerYPosition + 1] = 1;
    map[playerXPosition + 1][playerYPosition - 1] = 1;
    map[playerXPosition - 1][playerYPosition + 1] = 1;
    map[playerXPosition - 1][playerYPosition - 1] = 1;
  }
};