
#include "Game.h"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

size_t onStage;
size_t action;

Utils utils;

Stats stats;
Text text;
Dungeon dungeon;
Events events;
Menu menu;
Pause pause;
Cutscene cutscene;

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
  menu.init(&utils);
  events.init(&utils);
  cutscene.init(&utils);
  restart();
}

void Game::restart(void)
{
  dungeon.init(&utils);
  pause.init(&utils);
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
  menu.eventDisplay(&text);
  if (!menu.action())
  {
    utils.music = false;
    restart();
    text.printLog(1);
    cutscene.number = 0;
    onStage = 4;
  }
}

void Game::mainPauseTick(void)
{
  pause.eventDisplay(&stats, &text);
  size_t option = pause.action();

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
  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
  {
    onStage = 1;
  }
  else
  {
    action = dungeon.movePlayer();

    if (action > 0 && actions.evaluateAction(&events, &text, &stats, &dungeon, action))
    {
      events.refresh(dungeon.level);
      onStage = 3;
    }

    dungeon.display();
    action = 0;
  }

  text.print(dungeon.level);
  text.printStats(&stats, &utils);

  dungeon.canvas();
}

void Game::mainGameBattleTick(void)
{
  events.eventDisplay(&text);
  if (!events.action(&stats, &text))
  {
    onStage = 2;
  }

  if (stats.getHP() < 1)
  {
    utils.koBeep();
    restart();
    cutscene.number = 1;
    onStage = 4;
  }

  text.print(dungeon.level);
  text.printStats(&stats, &utils);

  dungeon.canvas();
}

void Game::mainCutsceneTick(void)
{
  cutscene.eventDisplay(&stats, &text);
  if (!cutscene.action())
  {
    onStage = 2;
  }

  dungeon.completeCanvas();
}
