#pragma once

struct Counter
{
  size_t killed;
  size_t escaped;
  size_t utils;
  size_t spared;

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
  size_t maxLevel = 0;
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

  void incMaxLevelReached(size_t val)
  {
    maxLevel = min(max(val, maxLevel), MAX_LEVEL);
  }

  size_t getMaxLevelReached()
  {
    return min(maxLevel, MAX_LEVEL);
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
    return min(hp, 9);
  }

  uint8_t getSTR()
  {
    return min(str, 9);
  }

  uint8_t getDEF()
  {
    return min(def, 9);
  }

  bool hit()
  {
    if (discardItem(5))
    {
      return false;
    }

    if (def > 0)
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
      if ((slots[x].type == item) && slots[x].amount < 9 && !found)
      {
        slots[x].appendItem(item);
        found = true;
      }
    }

    if (!found)
    {
      for (uint8_t x = 0; x < ITEM_AMOUNT; x++)
      {
        if ((slots[x].type == 0 || slots[x].type == item) && slots[x].amount < 9)
        {
          slots[x].appendItem(item);
          return true;
        }
      }
    }
    return found;
  }

  bool discardItem(uint8_t item)
  {
    uint8_t x = where(item);
    if (x != ITEM_AMOUNT)
    {
      slots[x].discardItem();
      return true;
    }
    return false;
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

  uint8_t where(uint8_t item)
  {
    for (uint8_t x = 0; x < ITEM_AMOUNT; x++)
    {
      if (slots[x].type == item)
      {
        return x;
      }
    }
    return ITEM_AMOUNT;
  }
};
