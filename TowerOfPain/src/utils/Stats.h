#pragma once

struct Stats
{
  uint8_t baseHp = 3;
  uint8_t baseStr = 1;
  uint8_t hp;
  uint8_t str;
  uint8_t def;
  uint8_t slots[3];
  uint8_t status;

  void init()
  {
    hp = baseHp;
    str = baseStr;
    def = 0;
    slots[0] = 0;
    slots[1] = 0;
    slots[2] = 0;
    status = 0;
  }

  void incHP(uint8_t val)
  {
    hp = min(hp + val, 9);
  }

  void decHP(uint8_t val)
  {
    hp = max(hp - val, 0);
  }

  void incSTR(uint8_t val)
  {
    str = min(str + val, 9);
  }

  void decSTR(uint8_t val)
  {
    str = max(str - val, 0);
  }

  void incDEF(uint8_t val)
  {
    def = min(def + val, 9);
  }

  void decDEF(uint8_t val)
  {
    def = max(def - val, 0);
  }

  uint8_t getHP()
  {
    return hp;
  }

  uint8_t getSTR()
  {
    return str;
  }

  uint8_t getDEF()
  {
    return def;
  }

  bool hit()
  {
    if (discardItem(5))
    {
      decDEF(1);
      return false;
    }

    decHP(1);
    if (hp <= 0)
    {
      return true;
    }
    return false;
  }

  bool addItem(uint8_t item)
  {
    for (uint8_t x = 0; x < 3; x++)
    {
      if (slots[x] == 0)
      {
        appendItem(x, item);
        return true;
      }
    }
    return false;
  }

  bool discardItem(uint8_t item)
  {
    if (slots[2] == item)
    {
      slots[2] = 0;
      return true;
    }
    else if (slots[1] == item)
    {
      slots[1] = 0;
      return true;
    }
    else if (slots[0] == item)
    {
      slots[0] = 0;
      return true;
    }

    return false;
  }

  void appendItem(uint8_t x, uint8_t item)
  {
    slots[x] = item;

    if (item == 4)
    {
      incSTR(2);
    }
    else if (item == 5)
    {
      incDEF(1);
    }
  }

  uint8_t getSlotText(uint8_t x)
  {
    switch (slots[x])
    {
    case 4:
      return 4;
    case 5:
      return 5;
    case 7:
      return 6;
    case 8:
      return 7;
    default:
      return 0;
    }
  }

  uint8_t getStatusText()
  {
    switch (status)
    {
    default:
      return 0;
    }
  }

  bool hasShield()
  {
    if (slots[2] == 5 || slots[1] == 5 || slots[0] == 5)
    {
      return true;
    }
    return false;
  }

  bool hasSword()
  {
    if (slots[2] == 4 || slots[1] == 4 || slots[0] == 4)
    {
      return true;
    }
    return false;
  }
};
