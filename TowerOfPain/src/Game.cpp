
#include "Game.h"

#include "maze/Dungeon.h"
#include "maze/Actions.h"

#include "menus/Menu.h"
#include "menus/BattleMenu.h"
#include "menus/TitleMenu.h"
#include "menus/PauseMenu.h"

uint8_t onStage;
uint8_t action;

Utils utils;

Dungeon dungeon;

BattleMenu battleMenu;
TitleMenu titleMenu;
PauseMenu pauseMenu;

Actions actions;

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

void Game::setup(void)
{
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  arduboy.systemButtons();
  arduboy.waitNoButtons();
  arduboy.audio.off();
  restart();
}

void Game::restart(void)
{
  dungeon.refresh();
  utils.stats.init();
  action = 0;
}

void Game::loop(void)
{
  if (!(arduboy.nextFrame()))
  {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();
  utils.music = 0;

  switch (onStage)
  {
  case 0:
    mainMenuTick();
    break;
  case 1:
    mainPauseTick();
    break;
  case 2:
    mainGameTick();
    break;
  case 3:
    mainGameBattleTick();
    break;
  case 4:
    mainCutsceneTick();
    break;
  default:
    mainLastCutsceneTick();
    break;
  }

  utils.tick();

  arduboy.display();
}

void Game::mainMenuTick(void)
{
  // force some level of randomness at the start
  rand() % analogRead(0);
  utils.music = 2;
  titleMenu.eventDisplay(&utils);
  if (!titleMenu.action(&utils))
  {
    restart();
    utils.texts.printLog(1);
    dungeon.cutsceneStart(true, false);
    onStage = 4;
    utils.lullaby = 0;
  }
}

void Game::mainPauseTick()
{
  pauseMenu.eventDisplay(&utils);
  switch (pauseMenu.action(&utils))
  {
  case 1:
    onStage = 2;
    utils.lullaby = 0;
    break;
  case 2:
    onStage = 0;
    utils.lullaby = 0;
    break;
  default:
    utils.texts.print(dungeon.level);
    utils.texts.printStats(&utils.stats);
    dungeon.canvas();
    break;
  }
}

void Game::mainGameTick(void)
{
  if (Arduboy2Base::justPressed(A_BUTTON))
  {
    pauseMenu.refresh();
    onStage = 1;
    utils.lullaby = 0;
  }
  else
  {
    action = dungeon.movePlayer();

    if (action > 0 && actions.evaluateAction(&utils, &dungeon, action))
    {
      battleMenu.refresh();
      dungeon.monster.setLife();
      onStage = 3;
      utils.lullaby = 0;
    }

    if (dungeon.level == MAX_LEVEL)
    {
      dungeon.cutsceneStart(false, false);
      onStage = 5;
      utils.lullaby = 0;
    }
    else if (dungeon.level > 0 && dungeon.level % CHANGE_LEVEL_AT == 0 && !dungeon.cutsceneDone())
    {
      dungeon.cutsceneStart(false, false);
      onStage = 4;
      utils.lullaby = 0;
    }
    else
    {
      dungeon.display(&utils);
    }

    action = 0;
  }

  utils.texts.print(dungeon.level);
  utils.texts.printStats(&utils.stats);

  dungeon.canvas();
}

void Game::mainGameBattleTick(void)
{
  utils.music = 1;
  battleMenu.eventDisplay(&utils, &dungeon);
  if (!battleMenu.action(&utils, &dungeon))
  {
    onStage = 2;
    utils.lullaby = 0;
  }

  if (utils.stats.getHP() < 1)
  {
    restart();
    utils.koBeep();
    utils.texts.printLog(1);
    dungeon.cutsceneStart(true, true);
    onStage = 4;
    utils.lullaby = 0;
  }
  else
  {
    utils.texts.print(dungeon.level);
    utils.texts.printStats(&utils.stats);
  }

  dungeon.canvas();
}

void Game::mainCutsceneTick(void)
{
  dungeon.cutscene.eventDisplay(&utils, dungeon.monster.currentType, utils.stats.getMaxLevelReached());
  if (dungeon.cutscene.enabled() && (Arduboy2Base::justPressed(A_BUTTON) || Arduboy2Base::justPressed(B_BUTTON) || Arduboy2Base::justPressed(LEFT_BUTTON) || Arduboy2Base::justPressed(RIGHT_BUTTON)))
  {
    onStage = 2;
    utils.lullaby = 0;
  }

  dungeon.completeCanvas();
}

void Game::mainLastCutsceneTick(void)
{
  utils.music = 3;
  dungeon.cutscene.eventDisplay(&utils, dungeon.monster.currentType, utils.stats.getMaxLevelReached());
  dungeon.completeCanvas();
}
