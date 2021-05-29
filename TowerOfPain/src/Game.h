#pragma once

#define MAX_SQUARE_AMOUNT_WEIGHT 17
#define MAX_SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_AMOUNT_WEIGHT 13
#define SQUARE_AMOUNT_HEIGHT 8
#define MAX_LEVEL 999
#define SQUARE_SIZE 8
#define ITEM_AMOUNT 4
#define MAX_ENEMY_AMOUNT 3
#define CUTSCENE_TIMER 10
#define WALKER_CYCLES 50

#include "utils/Utils.h"

class Game
{
public:
  void setup(void);
  void loop(void);
  void restart(void);
  void mainMenuTick(void);
  void mainPauseTick(void);
  void mainGameTick(void);
  void mainGameBattleTick(void);
  void mainCutsceneTick(void);
};
