#pragma once

struct Item
{
  uint8_t amount;
  uint8_t type;

  void init()
  {
    amount = 0;
    type = 0;
  }

  void discardItem()
  {
    amount = max(amount - 1, 0);
    if (amount == 0)
    {
      type = 0;
    }
  }

  void appendItem(uint8_t type)
  {
    amount = min(amount + 1, 9);
    this->type = type;
  }
};

struct Stats
{
  uint8_t baseHp = 3;
  uint8_t baseStr = 1;
  uint8_t hp;
  uint8_t str;
  uint8_t def;
  Item slots[3];
  uint8_t status;

  void init()
  {
    hp = baseHp;
    str = baseStr;
    def = 0;
    slots[0].init();
    slots[1].init();
    slots[2].init();
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
    bool found = false;

    for (uint8_t x = 0; x < 3; x++)
    {
      if ((slots[x].type == item) && slots[x].amount < 8 && !found)
      {
        appendItem(x, item);
        found = true;
      }
    }

    if (!found)
    {
      for (uint8_t x = 0; x < 3; x++)
      {
        if ((slots[x].type == 0 || slots[x].type == item) && slots[x].amount < 8)
        {
          appendItem(x, item);
          return true;
        }
      }
    }
    return false;
  }

  bool discardItem(uint8_t item)
  {
    if (slots[2].type == item)
    {
      slots[2].discardItem();
      return true;
    }
    else if (slots[1].type == item)
    {
      slots[1].discardItem();
      return true;
    }
    else if (slots[0].type == item)
    {
      slots[0].discardItem();
      return true;
    }

    return false;
  }

  void appendItem(uint8_t x, uint8_t item)
  {
    slots[x].appendItem(item);

    if (item == 4)
    {
      incSTR(2);
    }
    else if (item == 5)
    {
      incDEF(1);
    }
  }

  uint8_t getStatusText()
  {
    switch (status)
    {
    default:
      return 30;
    }
  }

  bool hasShield()
  {
    if (slots[2].type == 5 || slots[1].type == 5 || slots[0].type == 5)
    {
      return true;
    }
    return false;
  }

  bool hasSword()
  {
    if (slots[2].type == 4 || slots[1].type == 4 || slots[0].type == 4)
    {
      return true;
    }
    return false;
  }
};
