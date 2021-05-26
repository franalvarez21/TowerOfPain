#pragma once

struct Counter
{
  uint8_t killed;
  uint8_t escaped;
  uint8_t utils;
  uint8_t spared;

  void init()
  {
    killed = 0;
    escaped = 0;
    utils = 0;
    spared = 0;
  }
};

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
  uint8_t hp;
  uint8_t str;
  uint8_t def;
  Item slots[ITEM_AMOUNT];
  Counter counter;

  void init()
  {
    hp = 9;
    str = 1;
    def = 0;
    counter.init();
    for (uint8_t i = 0; i < ITEM_AMOUNT - 1; i++)
    {
      slots[i].init();
    }
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
    if (discardItem(5) || def > 0)
    {
      decDEF(1);
      return false;
    }

    decHP(1);
    return (hp <= 0);
  }

  bool addItem(uint8_t item)
  {
    bool found = false;

    for (uint8_t x = 0; x < ITEM_AMOUNT; x++)
    {
      if ((slots[x].type == item) && slots[x].amount < 8 && !found)
      {
        appendItem(x, item);
        found = true;
      }
    }

    if (!found)
    {
      for (uint8_t x = 0; x < ITEM_AMOUNT; x++)
      {
        if ((slots[x].type == 0 || slots[x].type == item) && slots[x].amount < 8)
        {
          appendItem(x, item);
          return true;
        }
      }
    }
    return found;
  }

  bool discardItem(uint8_t item)
  {
    for (uint8_t x = 0; x < ITEM_AMOUNT; x++)
    {
      if (slots[x].type == item)
      {
        slots[x].discardItem();
        return true;
      }
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
    if (counter.killed > counter.spared + counter.escaped)
    {
      return 0;
    }
    else if (counter.utils > counter.spared + counter.escaped)
    {
      return 1;
    }
    else if (counter.spared > counter.killed + counter.escaped)
    {
      return 2;
    }
    return 3;
  }

  bool hasShield()
  {
    for (uint8_t x = 0; x < ITEM_AMOUNT; x++)
    {
      if (slots[x].type == 5)
      {
        return true;
      }
    }
    return false;
  }

  bool hasSword()
  {
    for (uint8_t x = 0; x < ITEM_AMOUNT; x++)
    {
      if (slots[x].type == 4)
      {
        return true;
      }
    }
    return false;
  }
};
