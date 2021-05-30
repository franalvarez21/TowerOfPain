
#include "Game.h"

#include "maze/Dungeon.h"
#include "maze/Actions.h"

#include "menus/Menu.h"
#include "menus/BattleMenu.h"
#include "menus/TitleMenu.h"
#include "menus/PauseMenu.h"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

uint8_t onStage;
uint8_t action;

Utils utils;

Stats stats;
Text text;
Dungeon dungeon;

BattleMenu battleMenu;
TitleMenu titleMenu;
PauseMenu pauseMenu;

Actions actions;

void Game::setup(void)
{
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  arduboy.systemButtons();
  arduboy.waitNoButtons();
  arduboy.audio.off();
  Serial.begin(9600);

  utils.init(&arduboy);
  text.init(&tinyfont);
  restart();
}

void Game::restart(void)
{
  dungeon.refresh();
  stats.init();
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

  utils.tick(&sound);

  arduboy.display();
}

void Game::mainMenuTick(void)
{
  // force some level of randomness at the start
  rand() % analogRead(0);
  utils.music = 2;
  titleMenu.eventDisplay(&utils, &text);
  if (!titleMenu.action(&utils, &sound))
  {
    restart();
    text.printLog(1);
    dungeon.cutsceneStart(true, false);
    onStage = 4;
    utils.lullaby = 0;
  }
}

void Game::mainPauseTick()
{
  pauseMenu.eventDisplay(&utils, &text, &stats);
  switch (pauseMenu.action(&utils, &sound))
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
    text.print(dungeon.level);
    text.printStats(&stats, &utils);
    dungeon.canvas(&utils);
    break;
  }
}

void Game::mainGameTick(void)
{
  if (arduboy.justPressed(A_BUTTON))
  {
    pauseMenu.refresh();
    onStage = 1;
    utils.lullaby = 0;
  }
  else
  {
    action = dungeon.movePlayer(&utils);

    if (action > 0 && actions.evaluateAction(&utils, &text, &stats, &dungeon, action, &sound))
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

  text.print(dungeon.level);
  text.printStats(&stats, &utils);

  dungeon.canvas(&utils);
}

void Game::mainGameBattleTick(void)
{
  utils.music = 1;
  battleMenu.eventDisplay(&utils, &text, &dungeon);
  if (!battleMenu.action(&utils, &text, &stats, &dungeon, &sound))
  {
    onStage = 2;
    utils.lullaby = 0;
  }

  if (stats.getHP() < 1)
  {
    restart();
    utils.koBeep(&sound);
    text.printLog(1);
    dungeon.cutsceneStart(true, true);
    onStage = 4;
    utils.lullaby = 0;
  }
  else
  {
    text.print(dungeon.level);
    text.printStats(&stats, &utils);
  }

  dungeon.canvas(&utils);
}

void Game::mainCutsceneTick(void)
{
  dungeon.cutscene.eventDisplay(&utils, &stats, &text, dungeon.monster.currentType, stats.getMaxLevelReached());
  if (dungeon.cutscene.enabled() && (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON) || arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)))
  {
    onStage = 2;
    utils.lullaby = 0;
  }

  dungeon.completeCanvas(&utils);
}

void Game::mainLastCutsceneTick(void)
{
  utils.music = 3;
  dungeon.cutscene.eventDisplay(&utils, &stats, &text, dungeon.monster.currentType, stats.getMaxLevelReached());
  dungeon.completeCanvas(&utils);
}
