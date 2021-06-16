
class Monster
{
public:
  uint8_t life;
  uint8_t currentType;
  uint16_t effectDamage;

protected:
  uint8_t maxLife;
  uint8_t previousType;
  const uint8_t *monster1;
  const uint8_t *monster2;
  const uint8_t *monsterFrame1;
  const uint8_t *monsterFrame2;
  const uint8_t *environment;

public:
  Monster() : currentType(0), previousType(0), life(0), maxLife(0), effectDamage(0){};

  void setLife()
  {
    effectDamage = 0;
    life = (maxLife / 3) + rand() % ((maxLife + 1) - (maxLife / 3));
  }

  void hitEnemy(const uint8_t str)
  {
    life = life < str ? 0 : life - str;
    effectDamage = 10;
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
      SetMonster(MiniCharacter::slime_1, MiniCharacter::slime_2, Character::frameSlime1, Character::frameSlime2, 5, Map::map_environment_0);
      break;
    case 1:
      SetMonster(MiniCharacter::slime_1, MiniCharacter::slime_2, Character::frameSlime3, Character::frameSlime4, 10, Map::map_environment_1);
      break;
    case 2:
      SetMonster(MiniCharacter::slime_1, MiniCharacter::slime_2, Character::frameSlime5, Character::frameSlime6, 12, Map::map_environment_0);
      break;
    case 3:
      SetMonster(MiniCharacter::eye_1, MiniCharacter::eye_2, Character::frameEye1, Character::frameEye2, 15, Map::map_environment_1);
      break;
    case 4:
      SetMonster(MiniCharacter::eye_3, MiniCharacter::eye_4, Character::frameEye3, Character::frameEye4, 15, Map::map_environment_2);
      break;
    case 5:
      SetMonster(MiniCharacter::eye_5, MiniCharacter::eye_6, Character::frameEye5, Character::frameEye6, 20, Map::map_environment_2);
      break;
    case 6:
      SetMonster(MiniCharacter::flower_1, MiniCharacter::flower_2, Character::frameFlower1, Character::frameFlower2, 12, Map::map_environment_3);
      break;
    case 7:
      SetMonster(MiniCharacter::lancer_1, MiniCharacter::lancer_2, Character::frameLancer1, Character::frameLancer2, 15, Map::map_environment_3);
      break;
    case 8:
      SetMonster(MiniCharacter::centaur_1, MiniCharacter::centaur_2, Character::frameCentaur1, Character::frameCentaur2, 20, Map::map_environment_4);
      break;
    case 9:
      SetMonster(MiniCharacter::mage_1, MiniCharacter::mage_2, Character::frameMage1, Character::frameMage2, 22, Map::map_environment_4);
      break;
    case 10:
      SetMonster(MiniCharacter::rabbit_1, MiniCharacter::rabbit_2, Character::frameRabbit1, Character::frameRabbit2, 30, Map::map_environment_5);
      break;
    case 11:
      SetMonster(MiniCharacter::knight_1, MiniCharacter::knight_2, Character::frameKnight1, Character::frameKnight2, 25, Map::map_environment_6);
      break;
    case 12:
      SetMonster(MiniCharacter::axe_1, MiniCharacter::axe_2, Character::frameAxe1, Character::frameAxe2, 25, Map::map_environment_7);
      break;
    case 13:
      SetMonster(MiniCharacter::knife_1, MiniCharacter::knife_2, Character::frameKnife1, Character::frameKnife2, 22, Map::map_environment_7);
      break;
    default:
      SetMonster(MiniCharacter::shield_1, MiniCharacter::shield_2, Character::frameShield1, Character::frameShield2, 35, Map::map_environment_6);
      break;
    }
  }

  void SetMonster(uint8_t *monster1, uint8_t *monster2, uint8_t *monsterFrame1, uint8_t *monsterFrame2, uint8_t maxLife, uint8_t *environment)
  {
    this->monster1 = monster1;
    this->monster2 = monster2;
    this->monsterFrame1 = monsterFrame1;
    this->monsterFrame2 = monsterFrame2;
    this->maxLife = maxLife;
    this->environment = environment;
  }

  void displayFrame(Utils *utils)
  {
    if (effectDamage > 0)
    {
      effectDamage--;
    }

    if (utils->cycle <= 5)
    {
      Arduboy2Base::drawBitmap(4, 4, monsterFrame1, 32, 48, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(4, 4, monsterFrame2, 32, 48, WHITE);
    }
  }

  void displayIn(Utils *utils, const uint8_t x, const uint8_t y)
  {
    displayImage(x, y, (utils->cycle <= 5) ? monster1 : monster2);
  }

  void displayEnvironmentIn(const uint8_t x, const uint8_t y)
  {
    displayImage(x, y, environment);
  }

private:
  void displayImage(const uint8_t x, const uint8_t y, const uint8_t *image)
  {
    Arduboy2Base::drawBitmap(SQUARE_SIZE * x - 4, SQUARE_SIZE * y - 4, image, SQUARE_SIZE, SQUARE_SIZE, WHITE);
  }
};
