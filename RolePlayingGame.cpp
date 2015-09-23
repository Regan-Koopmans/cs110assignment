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

for (usigned int y = 0; y < ; y++)
{
  for (unsigned int x = 0; x < ; x++)
  {
    cout <<;
  }
}

}

bool RolePlayingGame::heroIsDead()
{
  return hero.isDead();
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
  creatures = new Creature * [dungeon.worldRows];

  for (unsigned int x = 0; x < worldRows; x++)
  {
    creatures[x] = new Creature[dungeon.worldColumns];
    for (unsigned y = 0; y < worldColumns; y++)
    {
      creatures[x][y] = 0;
    }
  }

}

void RolePlayingGame::initializeMonsters(unsigned int seed, unsigned int numMon)
{
  do
  {
    if (numMon > 10)
    {
      cout << "Too many monsters requested. Minimum 9 allowed" << endl;
      cout << "Enter an integer from 0 to 9. How many monsters should be added: ";
      cin >> numMon;
    }
    if (numMon < 0)
    {
      cout << "Enter an integer from 0 to 9. How many monsters should be added: ";
      cin >> numMon;
    }
  } while (numMon < 0 || numMon > 10);

  do
  {
    RandomNumberGenerator ran( seed, this−>dungeon.getWorldRows() − 2 );
    row = ran.nextInt();
    RandomNumberGenerator ran2( seed , this−>dungeon.getWorldColumns() − 2 );
    col = ran2.nextInt();
  } while (maze[row][col] == 0);
}

void RolePlayingGame::initializeFirstAidKits(unsigned int seed, unsigned int numKits, unsigned int boost)
{
  do
  {
    if (numKits > 10)
    {
      cout << "Too many first aid kits requested. Maximum 9 allowed" << endl;
      cout << "Enter an integer from 0 to 9. How many potions should be added: ";
      cin >> numKits;
    }
    if (numKits < 0)
    {
      cout << "Enter an integer from 0 to ";
      cout << x << ". How many potions should be added: ";
      cin >> numKits;
    }
  } while (numKits < 0 || numKits > 10));
}

void RolePlayingGame::initializePotions(unsigned int seed, unsigned int numPotions)
{
  do
  {
    if (numPotions > 10)
    {
      cout << "Too many potions requested. Maximum 9 allowed" << endl;
      cout << "Enter an integer from 0 to 9. How many potions should be added: ";
      cin >> numPotions;
    }
    if (numPotions < 0)
    {
      cout << "Enter an integer from 0 to ";
      cout << x << ". How many potions should be added: ";
      cin >> numPotions;
    }
  } while (numMon);
}

void RolePlayingGame::initializeHero(unsigned int seed)
{
  hero = Creature;
  do
  {
    RandomNumberGenerator ran( seed, this−>dungeon.getWorldRows() − 2 );
    row = ran.nextInt();
    RandomNumberGenerator ran2( seed , this−>dungeon.getWorldColumns() − 2 );
    col = ran2.nextInt();
  } while (maze[row][col] == 0);

  maze[row][col] = hero;
  creatures[row][col] = &hero;
}
