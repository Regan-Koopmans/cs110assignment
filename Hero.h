#ifndef HERO_H
#define HERO_H

#include "Creature.h"

class Hero : public Creature
{
  public:
    Hero operator++();
    Hero operator+=(int inputHealth);
    Hero operator-(Creature inputCreature);
    Hero operator-=(int inputHealth);
};

#endif
