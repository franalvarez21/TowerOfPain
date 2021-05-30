
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

  utils.tick(&sound);

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
  default:
    mainCutsceneTick();
    break;
  }

  arduboy.display();
}

void Game::mainMenuTick(void)
{
  utils.music = true;
  titleMenu.eventDisplay(&utils, &text);
  if (!titleMenu.action(&utils, &sound))
  {
    restart();
    utils.music = false;
    text.printLog(1);
    dungeon.cutsceneStart(true, false);
    onStage = 4;
  }
}

void Game::mainPauseTick()
{
  pauseMenu.eventDisplay(&utils, &text, &stats);
  switch (pauseMenu.action(&utils, &sound))
  {
  case 1:
    onStage = 2;
    break;
  case 2:
    onStage = 0;
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
  }
  else
  {
    action = dungeon.movePlayer(&utils);

    if (action > 0 && actions.evaluateAction(&utils, &text, &stats, &dungeon, action))
    {
      battleMenu.refresh();
      dungeon.monster.setLife();
      onStage = 3;
    }

    if (dungeon.level > 0 && dungeon.level % 10 == 0 && !dungeon.cutsceneDone())
    {
      dungeon.cutsceneStart(false, false);
      onStage = 4;
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
  battleMenu.eventDisplay(&utils, &text, &dungeon);
  if (!battleMenu.action(&utils, &text, &stats, &dungeon, &sound))
  {
    onStage = 2;
  }

  if (stats.getHP() < 1)
  {
    restart();
    utils.koBeep(&sound);
    text.printLog(1);
    dungeon.cutsceneStart(true, true);
    onStage = 4;
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
  }

  dungeon.completeCanvas(&utils);
}
