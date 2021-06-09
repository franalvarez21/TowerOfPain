
class Monster
{
public:
  uint8_t life;
  uint8_t currentType;

protected:
  uint8_t maxLife;
  uint8_t previousType;
  const uint8_t *monster1;
  const uint8_t *monster2;
  const uint8_t *monsterFrame1;
  const uint8_t *monsterFrame2;
  const uint8_t *environment;

public:
  Monster() : currentType(0), previousType(0), life(0), maxLife(0){};

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
    return life < (maxLife * 0.75);
  }

  void refresh(const bool start)
  {
    currentType = start ? 0 : rand() % ENEMY_AMOUNT;
    if (previousType == currentType && !start)
    {
      if (currentType == 0)
      {
        currentType = ENEMY_AMOUNT - 1;
      }
      else if (currentType == (ENEMY_AMOUNT - 1))
      {
        currentType = 0;
      }
      else
      {
        currentType = currentType + 1;
      }
    }
    previousType = currentType;

    switch (currentType)
    {
    case 0:
      monster1 = MiniCharacter::slime_1;
      monster2 = MiniCharacter::slime_2;
      monsterFrame1 = Character::frameSlime1;
      monsterFrame2 = Character::frameSlime2;
      maxLife = 5;
      environment = Map::map_environment_0;
      break;
    case 1:
      monster1 = MiniCharacter::slime_1;
      monster2 = MiniCharacter::slime_2;
      monsterFrame1 = Character::frameSlime3;
      monsterFrame2 = Character::frameSlime4;
      maxLife = 10;
      environment = Map::map_environment_1;
      break;
    case 2:
      monster1 = MiniCharacter::slime_1;
      monster2 = MiniCharacter::slime_2;
      monsterFrame1 = Character::frameSlime5;
      monsterFrame2 = Character::frameSlime6;
      maxLife = 12;
      environment = Map::map_environment_0;
      break;
    case 3:
      monster1 = MiniCharacter::eye_1;
      monster2 = MiniCharacter::eye_2;
      monsterFrame1 = Character::frameEye1;
      monsterFrame2 = Character::frameEye2;
      maxLife = 15;
      environment = Map::map_environment_1;
      break;
    case 4:
      monster1 = MiniCharacter::eye_3;
      monster2 = MiniCharacter::eye_4;
      monsterFrame1 = Character::frameEye3;
      monsterFrame2 = Character::frameEye4;
      maxLife = 15;
      environment = Map::map_environment_2;
      break;
    case 5:
      monster1 = MiniCharacter::eye_5;
      monster2 = MiniCharacter::eye_6;
      monsterFrame1 = Character::frameEye5;
      monsterFrame2 = Character::frameEye6;
      maxLife = 20;
      environment = Map::map_environment_2;
      break;
    case 6:
      monster1 = MiniCharacter::flower_1;
      monster2 = MiniCharacter::flower_2;
      monsterFrame1 = Character::frameFlower1;
      monsterFrame2 = Character::frameFlower2;
      maxLife = 12;
      environment = Map::map_environment_3;
      break;
    case 7:
      monster1 = MiniCharacter::lancer_1;
      monster2 = MiniCharacter::lancer_2;
      monsterFrame1 = Character::frameLancer1;
      monsterFrame2 = Character::frameLancer2;
      maxLife = 15;
      environment = Map::map_environment_3;
      break;
    case 8:
      monster1 = MiniCharacter::centaur_1;
      monster2 = MiniCharacter::centaur_2;
      monsterFrame1 = Character::frameCentaur1;
      monsterFrame2 = Character::frameCentaur2;
      maxLife = 20;
      environment = Map::map_environment_4;
      break;
    case 9:
      monster1 = MiniCharacter::mage_1;
      monster2 = MiniCharacter::mage_2;
      monsterFrame1 = Character::frameMage1;
      monsterFrame2 = Character::frameMage2;
      maxLife = 22;
      environment = Map::map_environment_4;
      break;
    case 10:
      monster1 = MiniCharacter::rabbit_1;
      monster2 = MiniCharacter::rabbit_2;
      monsterFrame1 = Character::frameRabbit1;
      monsterFrame2 = Character::frameRabbit2;
      maxLife = 30;
      environment = Map::map_environment_5;
      break;
    case 11:
      monster1 = MiniCharacter::knight_1;
      monster2 = MiniCharacter::knight_2;
      monsterFrame1 = Character::frameKnight1;
      monsterFrame2 = Character::frameKnight2;
      maxLife = 25;
      environment = Map::map_environment_6;
      break;
    case 12:
      monster1 = MiniCharacter::axe_1;
      monster2 = MiniCharacter::axe_2;
      monsterFrame1 = Character::frameAxe1;
      monsterFrame2 = Character::frameAxe2;
      maxLife = 25;
      environment = Map::map_environment_7;
      break;
    case 13:
      monster1 = MiniCharacter::knife_1;
      monster2 = MiniCharacter::knife_2;
      monsterFrame1 = Character::frameKnife1;
      monsterFrame2 = Character::frameKnife2;
      maxLife = 22;
      environment = Map::map_environment_7;
      break;
    default:
      monster1 = MiniCharacter::shield_1;
      monster2 = MiniCharacter::shield_2;
      monsterFrame1 = Character::frameShield1;
      monsterFrame2 = Character::frameShield2;
      maxLife = 35;
      environment = Map::map_environment_6;
      break;
    }
  }

  void displayFrame(Utils *utils)
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

  void displayIn(Utils *utils, const uint8_t x, const uint8_t y)
  {
    displayImage(utils, x, y, (utils->cycle <= 5) ? monster1 : monster2);
  }

  void displayEnvironmentIn(Utils *utils, const uint8_t x, const uint8_t y)
  {
    displayImage(utils, x, y, environment);
  }

private:
  void displayImage(Utils *utils, const uint8_t x, const uint8_t y, const uint8_t *image)
  {
    utils->arduboy->drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, image, SQUARE_SIZE, SQUARE_SIZE, WHITE);
  }
};
