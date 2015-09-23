#include "RandomNumberGenerator.h"
#include "RolePlayingGame.h"

using namespace std;

RolePlayingGame::RolePlayingGame(unsigned int seed, unsigned int nrMon,
        unsigned int nrKits, unsigned int boost, unsigned int mhealth)
{
    //initialize the dungeon to be empty
    this->dungeon.readInMaze("mazeExample.txt");

    initializeCreatures();

    initializeHero(seed);

    initializeMonsters(seed, nrMon);

    initializeFirstAidKits(seed, nrKits, boost);

    this->maxHealth = mhealth;
}

bool RolePlayingGame::moveHero(const char direction)
{
  switch(direction)
  {
    case 'w':;
    break;
    case 's':;
    break;
    case 'a':;
    break;
    case 'd':;
    break;
    case 'W':;
    break;
    case 'S':;
    break;
    case 'A':;
    break;
    case 'D':;
    break;
  };
}

void RolePlayingGame::printBoard()
{

}

bool RolePlayingGame::heroIsDead()
{

}

bool RolePlayingGame::allMonstersDead()
{

}

void RolePlayingGame::removeDeadMonsters()
{

}

unsigned int RolePlayingGame::getNrMonsters()
{
  return nrMonsters;
}

void RolePlayingGame::setNrMonsters(unsigned int n)
{
  nrMonsters = n;
}

unsigned int RolePlayingGame::getNrFirstAidKits()
{
  return nrFirstAidKits;
}

void RolePlayingGame::setNrFirstAidKits(unsigned int f)
{
  nrFirstAidKits = f;
}

unsigned int RolePlayingGame::getNrPotions()
{
  return nrPotions;
}

void RolePlayingGame::setNrPotions(unsigned int p)
{
  nrPotions = p;
}

void RolePlayingGame::initializeCreatures()
{

}

void RolePlayingGame::initializeMonsters(unsigned int seed, unsigned int numMon)
{

}

void RolePlayingGame::initializeFirstAidKits(unsigned int seed, unsigned int numKits, unsigned int boost)
{

}

void RolePlayingGame::initializePotions(unsigned int seed, unsigned int numPotions)
{

}

void RolePlayingGame::initializeHero(unsigned int seed)
{
  RandomNumberGenerator ran( seed, this−>dungeon.getWorldRows() − 2 );
  row = ran.nextInt();
  RandomNumberGenerator ran2( seed , this−>dungeon.getWorldColumns() − 2 );
  col = ran2.nextInt();
}
