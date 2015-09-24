#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "RandomNumberGenerator.h"
#include "Dungeon.h"
#include "RolePlayingGame.h"

using namespace std;

RolePlayingGame::RolePlayingGame(unsigned int seed, unsigned int nrMon, unsigned int nrKits, unsigned int nrPotions, unsigned int boost, unsigned int maxHealth)
{
    //initialize the dungeon to be empty
    this->dungeon.readInMaze("mazeExample.txt");

    initializeCreatures();

    initializeHero(seed);

    initializeMonsters(seed, nrMon);

    initializeFirstAidKits(seed, nrKits, boost);

    this->maxHealth = maxHealth;
}

RolePlayingGame::~RolePlayingGame()
{

}

bool RolePlayingGame::moveHero(const char direction)
{
  vector<int> heroLocation = locateCreature(&hero);
  int newX = heroLocation[0];
  int newY = heroLocation[1];

  switch(direction)
  {
    case 'w': newX++;

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

  if (dungeon.getMazeSquare(newX,newY) == ' ')
  {

    return true;
  }
  else
  {
    if (dungeon.getMazeSquare(newX,newY) == 'P')
    {
      cout << endl;
      cout << "Oh dear, I am dizzy, the world is spinning..." << endl;

    } else if (dungeon.getMazeSquare(newX,newY) == 'R')
    {
      cout << endl;
      cout << "I suddently have some perspective!" << endl;
    }
    else if (dungeon.getMazeSquare(newX,newY) == '*')
    {
      cout << endl;
      cout << "Ouch! I cannot walk over obstacles!" << endl;
    }
    else if (dungeon.getMazeSquare(newX,newY) == 'T')
    {
      cout << endl;
      cout << "Ouch! I cannot walk over traps! I am hurt!" << endl;
      hero.setHealth(hero.getHealth() - 1);
    }
    else
    {

    }
    return false;
  }

}

void RolePlayingGame::printBoard()
{
int monsterCount = 0;
for (unsigned int x = 0; x < dungeon.getWorldRows(); x++)
{
  for (unsigned int y = 0; y < dungeon.getWorldColumns(); y++)
  {
    if ((dungeon.getMazeSquare(x,y) == ' ' || dungeon.getMazeSquare(x,y) == '*') && creatures[x][y] != 0)
    {
      cout << dungeon.getMazeSquare(x,y);
    }
    else
    {
      cout << "@";
    }
  }
  cout << monsterCount;
  monsterCount++;
}
}

bool RolePlayingGame::heroIsDead()
{
  return hero.isDead();
}

bool RolePlayingGame::allMonstersDead()
{
  return (nrMonsters > 0);
}

void RolePlayingGame::removeDeadMonsters()
{

}

unsigned int RolePlayingGame::getNrMonsters() const
{
  return nrMonsters;
}

void RolePlayingGame::setNrMonsters(unsigned int n)
{
  nrMonsters = n;
}

unsigned int RolePlayingGame::getNrFirstAidKits() const
{
  return nrFirstAidKits;
}

void RolePlayingGame::setNrFirstAidKits(unsigned int f)
{
  nrFirstAidKits = f;
}

unsigned int RolePlayingGame::getNrPotions() const
{
  return nrPotions;
}

void RolePlayingGame::setNrPotions(unsigned int p)
{
  nrPotions = 2*p;
}

void RolePlayingGame::initializeCreatures()
{
  creatures = new Creature ** [dungeon.getWorldRows()];

  for (unsigned int x = 0; x < dungeon.getWorldRows(); x++)
  {
    creatures[x] = new Creature * [dungeon.getWorldColumns()];
    for (unsigned y = 0; y < dungeon.getWorldColumns(); y++)
    {
      creatures[x][y] = 0;
    }
  }

}

void RolePlayingGame::initializeMonsters(unsigned int seed, unsigned int numMon)
{
  unsigned int row,col;

  do
  {
    if (numMon > 9)
    {
      cout << "Too many monsters requested. Maximum 9 allowed" << endl;
      cout << "Enter an integer from 0 to 9. How many monsters should be added: ";
      cin >> numMon;
    }
    if (numMon < 0)
    {
      cout << "Enter an integer from 0 to 9. How many monsters should be added: ";
      cin >> numMon;
    }
  } while (numMon < 0 || numMon > 9);

  monsters = new Creature[numMon];

  //Placing the monsters

  for (unsigned int everyMonster = 0; everyMonster < numMon; everyMonster++)
  {
    srand(time(NULL));
    do
    {
      RandomNumberGenerator ran(seed, this->dungeon.getWorldRows());
      row = rand() % dungeon.getWorldRows();
      RandomNumberGenerator ran2(seed, this->dungeon.getWorldColumns());
      col = rand() % dungeon.getWorldColumns();

    } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns()) || (dungeon.getMazeSquare(row,col) != ' '));

    monsters[everyMonster] = Creature();
    creatures[row][col] = &monsters[everyMonster];
  }
}

void RolePlayingGame::initializeFirstAidKits(unsigned int seed, unsigned int numKits, unsigned int boost)
{
  unsigned int x = nrMonsters/2;
  do
  {
    if (numKits >= x)
    {
      cout << "Too many first aid kits requested.";
      cout << " Maximum " << x << " allowed" << endl;
      cout << "Enter an integer from 0 to ";
      cout << x << ". How many potions should be added: ";
      cin >> numKits;
    }
    if (numKits < 0)
    {
      cout << "Enter an integer from 0 to ";
      cout << x << ". How many potions should be added: ";
      cin >> numKits;
    }
  } while (numKits < 0 || numKits >= x);

  firstAidKits = new Creature[numKits];
}

void RolePlayingGame::initializePotions(unsigned int seed, unsigned int numPotions)
{
  unsigned int x = nrMonsters/2;

  do
  {
    if (numPotions >= x)
    {
      cout << "Too many potions requested. Maximum 9 allowed" << endl;
      cout << "Enter an integer from " << x;
      cout << " to 9. How many potions should be added: ";
      cin >> numPotions;
    }
    if (numPotions < 0)
    {
      cout << "Enter an integer from " << x;
      cout << " to 9. How many potions should be added: ";
      cin >> numPotions;
    }
  } while (numPotions < 0 || numPotions >= x);

  potions = new Creature[numPotions];
}

void RolePlayingGame::initializeHero(unsigned int seed)
{
  hero = Creature();
  unsigned int row,col;
  do
  {
    RandomNumberGenerator ran(seed, this->dungeon.getWorldRows() -2);
    row = rand() % dungeon.getWorldRows();
    RandomNumberGenerator ran2(seed, this->dungeon.getWorldColumns() -2);
    col = rand() % dungeon.getWorldColumns();

  } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns()) || (dungeon.getMazeSquare(row,col) != ' '));

  //dungeon.getMazeSquare(row,col) = 'H';
  creatures[row][col] = &hero;
}

vector<int> RolePlayingGame::locateCreature(Creature* creature)
{
  vector<int> result;
  for (unsigned int x = 0; x < dungeon.getWorldRows(); x++)
    for (unsigned int y = 0; y < dungeon.getWorldColumns(); y++)
      if (creatures[x][y] == creature)
      {
        vector<int> result;
        result.push_back(x);
        result.push_back(y);
      }
return result;
}
