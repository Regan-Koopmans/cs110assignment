#include "Creature.h"
#include <ctime>
#include <iostream>
#include <stdlib.h>

using namespace std;

Creature::Creature():attack(0), defense(0), health(0)
{
    for (unsigned int index=0; index <3; index++)
    {
        attack = attack + (rand()%34);
        defense = defense + (rand()%34);
        health = health + (rand()%10);
    }
}

void Creature::attackEnemy(Creature& defender)
{
    //generate numbers between 1 and 100
    unsigned int attack1 = (rand()%100)+1;
    unsigned int defense1 = (rand()%100)+1;

    unsigned int attack2 = (rand()%100)+1;
    unsigned int defense2 = (rand()%100)+1;

    //did the attacker (hero) hit the enemy?
    if ((attack > attack1) && (defense1 > defender.defense))
    {
        --defender.health;
        cout << "Monster has been hit!" << endl;
    }
    else
    {
        cout << "Monster missed!" << endl;
    }

    //did the monster hit the hero?
    if ((defender.attack > attack2) && (defense2 > defense))
    {
        --health;
        cout << "Hero has been hit!" << endl;
    }
    else
    {
        cout << "Hero missed!" << endl;
    }

    cout << "Hero health: " << health << endl;
    cout << "Monster health: " << defender.health << endl;
}

bool Creature::isDead()
{
    return (health <= 0);
}

void Creature::setHealth(unsigned int h)
{
    health = h;
}

unsigned int Creature::getHealth() const
{
    return health;
}
