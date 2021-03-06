#pragma once

#define MAX_SQUARE_AMOUNT_WEIGHT 17
#define MAX_SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_AMOUNT_WEIGHT 14
#define SQUARE_AMOUNT_HEIGHT 8
#define MAX_LEVEL 999
#define CHANGE_LEVEL_AT 15
#define SQUARE_SIZE 8
#define ITEM_AMOUNT 4
#define MAX_ENEMY_AMOUNT 3
#define ENEMY_AMOUNT 15
#define ENEMY_NUMBER_ACTION 10
#define CUTSCENE_TIMER 15
#define WALKER_CYCLES 50
#define FEEDBACK_COUNTER 5

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
  void mainLastCutsceneTick(void);
};
