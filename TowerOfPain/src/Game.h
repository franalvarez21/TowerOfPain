#pragma once

#define MAX_SQUARE_AMOUNT_WEIGHT 12
#define MAX_SQUARE_AMOUNT_HEIGHT 8
#define SQUARE_SIZE 8

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <Tinyfont.h>

#include "const/Map.h"
#include "const/Common.h"
#include "const/Character.h"
#include "const/Lines.h"
#include "const/Title.h"

#include "utils/Utils.h"
#include "utils/Stats.h"
#include "utils/Text.h"
#include "utils/Menu.h"
#include "utils/Pause.h"
#include "utils/Events.h"
#include "utils/Dungeon.h"
#include "utils/Player.h"
#include "utils/Actions.h"

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
};
