#pragma once

struct Player
{
  Utils *utils;

  void init(Utils *utils)
  {
    this->utils = utils;
  }

  size_t move(Dungeon *dungeon)
  {
    size_t value = 0;

    if (utils->arduboy->justPressed(RIGHT_BUTTON))
    {
      value = dungeon->map[dungeon->playerXPosition + 1][dungeon->playerYPosition];
      if (value == 1)
      {
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition] = 1;
        dungeon->playerXPosition++;
        return 1;
      }
      else if (value > 1)
      {
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition] = 1;
        dungeon->map[dungeon->playerXPosition + 1][dungeon->playerYPosition] = 1;
        dungeon->playerXPosition++;
        return value;
      }
    }

    if (utils->arduboy->justPressed(LEFT_BUTTON))
    {
      value = dungeon->map[dungeon->playerXPosition - 1][dungeon->playerYPosition];
      if (value == 1)
      {
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition] = 1;
        dungeon->playerXPosition--;
        return 1;
      }
      else if (value > 1)
      {
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition] = 1;
        dungeon->map[dungeon->playerXPosition - 1][dungeon->playerYPosition] = 1;
        dungeon->playerXPosition--;
        return value;
      }
    }

    if (utils->arduboy->justPressed(DOWN_BUTTON))
    {
      value = dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition + 1];
      if (value == 1)
      {
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition] = 1;
        dungeon->playerYPosition++;
        return 1;
      }
      else if (value > 1)
      {
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition] = 1;
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition + 1] = 1;
        dungeon->playerYPosition++;
        return value;
      }
    }

    if (utils->arduboy->justPressed(UP_BUTTON))
    {
      value = dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition - 1];
      if (value == 1)
      {
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition] = 1;
        dungeon->playerYPosition--;
        return 1;
      }
      else if (value > 1)
      {
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition] = 1;
        dungeon->map[dungeon->playerXPosition][dungeon->playerYPosition - 1] = 1;
        dungeon->playerYPosition--;
        return value;
      }
    }

    return 0;
  }

  bool abCheck()
  {
    if (utils->arduboy->justPressed(A_BUTTON) || utils->arduboy->justPressed(B_BUTTON))
    {
      return true;
    }
    return false;
  }
};
