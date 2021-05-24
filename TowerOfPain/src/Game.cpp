
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
Player player;
Events events;
Menu menu;
Pause pause;

Actions actions;

void Game::setup(void)
{
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  arduboy.systemButtons();
  Serial.begin(9600);

  utils.init(&arduboy, &tinyfont, &sound);
  text.init(&utils);
  menu.init(&utils);
  events.init(&utils);
  player.init(&utils);
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
  default:
    break;
  }

  arduboy.display();
}

void Game::mainMenuTick(void)
{
  menu.eventDisplay(&utils, &text);
  if (!menu.action(&utils))
  {
    restart();
    text.printLog(1);
    onStage = 2;
  }
}

void Game::mainPauseTick(void)
{
  pause.eventDisplay(&stats, &text, utils.sound, utils.cicle);
  size_t option = pause.action(&utils);

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
    text.printStats(&stats);
    dungeon.canvas();
    break;
  }
}

void Game::mainGameTick(void)
{
  if (player.abCheck())
  {
    onStage = 1;
  }
  else
  {
    action = player.move(&dungeon);

    if (action > 0 && actions.evaluateAction(&events, &text, &stats, &dungeon, action))
    {
      onStage = 3;
    }

    dungeon.display(utils.cicle);
    action = 0;
  }

  text.print(dungeon.level);
  text.printStats(&stats);

  dungeon.canvas();
}

void Game::mainGameBattleTick(void)
{
  events.eventDisplay(&text, utils.cicle);
  if (!events.action(&stats, &text, &utils))
  {
    onStage = 2;
  }

  if (stats.getHP() < 1)
  {
    utils.koBeep();
    text.printLog(22);
    restart();
    onStage = 2;
  }

  text.print(dungeon.level);
  text.printStats(&stats);

  dungeon.canvas();
}
