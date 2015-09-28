#include "Hero.h"

Hero Hero::operator++()
{
  setHealth(getHealth() + 1);
  return *this;
}

Hero Hero::operator+=(int inputHealth)
{
  setHealth(getHealth() + inputHealth);
  return *this;
}

Hero Hero::operator-(Creature inputCreature)
{
  Hero temp;
  temp.setHealth(this->getHealth() - inputCreature.getHealth());
  return temp;
}

Hero Hero::operator-=(int inputHealth)
{
  setHealth(getHealth() - inputHealth);
  return *this;
}
