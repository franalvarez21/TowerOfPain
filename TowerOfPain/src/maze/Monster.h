
class Monster
{
public:
  size_t life;
  size_t currentType;

protected:
  Utils *utils;
  size_t maxLife;
  size_t previousType;
  const uint8_t *monster1;
  const uint8_t *monster2;
  const uint8_t *monsterFrame1;
  const uint8_t *monsterFrame2;
  const uint8_t *environment;

public:
  Monster() : currentType(0), previousType(0), life(0), maxLife(0){};

  void init(Utils *utils)
  {
    this->utils = utils;
  }

  void setLife()
  {
    life = (maxLife / 3) + rand() % ((maxLife + 1) - (maxLife / 3));
  }

  void hitEnemy(const uint8_t str)
  {
    life = life < str ? 0 : life - str;
  }

  bool canBeSpare()
  {
    return life < (maxLife * 0.80);
  }

  void refresh(const bool start)
  {
    currentType = start ? 0 : rand() % MAX_ENEMY_AMOUNT;
    if (previousType == currentType && !start)
    {
      currentType = currentType < MAX_ENEMY_AMOUNT ? currentType + 1 : currentType - 1;
    }
    previousType = currentType;

    switch (currentType)
    {
    case 0:
      monster1 = Character::slime_1;
      monster2 = Character::slime_2;
      monsterFrame1 = Character::frameSlime1;
      monsterFrame2 = Character::frameSlime2;
      maxLife = 10;
      environment = Map::map_environment_0;
      break;
    case 1:
      monster1 = Character::slime_1;
      monster2 = Character::slime_2;
      monsterFrame1 = Character::frameSlime3;
      monsterFrame2 = Character::frameSlime4;
      maxLife = 15;
      environment = Map::map_environment_1;
      break;
    case 2:
      monster1 = Character::eye_1;
      monster2 = Character::eye_2;
      monsterFrame1 = Character::frameEye1;
      monsterFrame2 = Character::frameEye2;
      maxLife = 20;
      environment = Map::map_environment_1;
      break;
    default:
      monster1 = Character::knight_1;
      monster2 = Character::knight_2;
      monsterFrame1 = Character::frameKnight1;
      monsterFrame2 = Character::frameKnight2;
      maxLife = 40;
      environment = Map::map_environment_2;
      break;
    }
  }

  void displayFrame()
  {
    if (utils->cycle <= 5)
    {
      utils->arduboy->drawBitmap(4, 4, monsterFrame1, 32, 48, WHITE);
    }
    else
    {
      utils->arduboy->drawBitmap(4, 4, monsterFrame2, 32, 48, WHITE);
    }
  }

  void displayIn(const size_t x, const size_t y)
  {
    displayImage(x, y, (utils->cycle <= 5) ? monster1 : monster2);
  }

  void displayEnvironmentIn(const size_t x, const size_t y)
  {
    displayImage(x, y, environment);
  }

private:
  void displayImage(const size_t x, const size_t y, const uint8_t *image)
  {
    utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, image, SQUARE_SIZE, SQUARE_SIZE, WHITE);
  }
};
