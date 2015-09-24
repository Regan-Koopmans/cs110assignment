#include <iostream>
#include <vector>

#include "RandomNumberGenerator.h"
#include "Dungeon.h"
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
  vector<int> heroLocation = findLocation(hero);
  int newX;
  int newY;

  switch(direction)
  {
    case 'w': newX;
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

  if ( == 0)
  {

  }
  else
  {
    if (dungeon.getMazeSquare[newX][newY] == "P")
    {
      cout << endl;
      cout << "Oh dear, I am dizzy, the world is spinning..." << endl;

    } else if (dungeon.getMazeSquare[newX][newY] == "R")
    {
      cout << endl;
      cout << "I suddently have some perspective!"
    }
    else if (dungeon.getMazeSquare[newX][newY] == "*")
    {
      cout << endl;
      cout << "Ouch! I cannot walk over obstacles!" << endl;
    }
    else if (dungeon.getMazeSquare[newX][newY] == "T")
    {
      cout << endl;
      cout << "Ouch! I cannot walk over traps! I am hurt!" << endl;
      hero.setHealth(hero.getHealth() - 1);
    }


  }

}

void RolePlayingGame::printBoard()
{

for (unsigned int x = 0; y < ; y++)
{
  for (unsigned int y = 0; x < ; x++)
  {
    cout << dungeon.getMazeSquare(x,y);
  }
  cout << endl;
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

  for (int everyMonster = 0; everyMonster < numMon; x++)
  {
    do
    {
      RandomNumberGenerator ran( seed, this−>dungeon.getWorldRows() − 2 );
      row = ran.nextInt();
      RandomNumberGenerator ran2( seed , this−>dungeon.getWorldColumns() − 2 );
      col = ran2.nextInt();
    } while (dungeon.getMazeSquare(row,col) != ' ');

    monsters[everyMonster] = new Monster;
    creatures[row][col] = monsters[everyMonster];
  }
}

void RolePlayingGame::initializeFirstAidKits(unsigned int seed, unsigned int numKits, unsigned int boost)
{
  unsigned int x = nrMonsters/2;
  do
  {
    if (numKits >= x)
    {
      cout << "Too many first aid kits requested."
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
  int row,col;
  do
  {
    RandomNumberGenerator ran( seed, dungeon.getWorldRows() − 2 );
    row = ran.nextInt();
    RandomNumberGenerator ran2( seed , dungeon.getWorldColumns() − 2 );
    col = ran2.nextInt();
  } while (maze[row][col] == 0);

  dungeon.maze[row][col] = 'H';
  creatures[row][col] = &hero;
}

vector<int> locateCreature(Creature* creature)
{
for (int x = 0; x < dungeon.getWorldRows(); x++)
  for (int y = 0; y < dungeon.getWorldColumns(); y++)
    if (creatures[x][y] == creature)
    {
      vector<int> result;
      result.push_back(x);
      result.push_back(y);
    }
return result;
}
