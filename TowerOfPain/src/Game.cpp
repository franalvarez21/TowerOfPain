
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

size_t onStage;
size_t action;

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

  utils.init(&arduboy, &sound);
  text.init(&tinyfont);
  dungeon.init(&utils);
  titleMenu.init(&utils, &text, &stats);
  battleMenu.init(&utils, &text, &stats);
  pauseMenu.init(&utils, &text, &stats);
  battleMenu.setup(&dungeon);
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

  utils.tick();

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
    break;
  }

  arduboy.display();
}

void Game::mainMenuTick(void)
{
  utils.music = true;
  titleMenu.eventDisplay();
  if (!titleMenu.action())
  {
    restart();
    utils.music = false;
    text.printLog(1);
    dungeon.cutsceneStart(true, false);
    onStage = 4;
  }
}

void Game::mainPauseTick(void)
{
  pauseMenu.eventDisplay();
  size_t option = pauseMenu.action();

  switch (option)
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
    dungeon.canvas();
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
    action = dungeon.movePlayer();

    if (action > 0 && actions.evaluateAction(&text, &stats, &dungeon, action))
    {
      battleMenu.refresh();
      onStage = 3;
    }

    if (dungeon.level > 0 && dungeon.level % 10 == 0 && !dungeon.cutsceneDone())
    {
      dungeon.cutsceneStart(false, false);
      onStage = 4;
    }
    else
    {
      dungeon.display();
    }

    action = 0;
  }

  text.print(dungeon.level);
  text.printStats(&stats, &utils);

  dungeon.canvas();
}

void Game::mainGameBattleTick(void)
{
  battleMenu.eventDisplay();
  if (!battleMenu.action())
  {
    onStage = 2;
  }

  if (stats.getHP() < 1)
  {
    restart();
    utils.koBeep();
    text.printLog(1);
    dungeon.cutsceneStart(true, true);
    onStage = 4;
  }
  else
  {
    text.print(dungeon.level);
    text.printStats(&stats, &utils);
  }

  dungeon.canvas();
}

void Game::mainCutsceneTick(void)
{
  dungeon.cutscene.eventDisplay(&stats, &text, dungeon.monster.currentType, stats.getMaxLevelReached());
  if (dungeon.cutscene.enabled() && (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON) || arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)))
  {
    onStage = 2;
  }

  dungeon.completeCanvas();
}
