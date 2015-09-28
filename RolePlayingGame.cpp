#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "RandomNumberGenerator.h"
#include "Dungeon.h"
#include "RolePlayingGame.h"
#include "Hero.h"

using namespace std;

int confusion = 1;

RolePlayingGame::RolePlayingGame(unsigned int seed, unsigned int nrMon,
  unsigned int nrKits, unsigned int nrPotions, unsigned int boost,
  unsigned int maxHealth)
{
    //initialize the dungeon to be empty
    this->dungeon.readInMaze("test2.txt");

    initializeCreatures();

    initializeHero(seed);

    initializeMonsters(seed, nrMon);

    initializePotions(seed, nrPotions);

    initializeFirstAidKits(seed, nrKits, boost);

    this->maxHealth = maxHealth;
}

RolePlayingGame::~RolePlayingGame()
{
//  delete [] monsters;
  delete monsters;
//  monsters = 0;
}

bool RolePlayingGame::moveHero(const char direction)
{

  RandomNumberGenerator ran(1, this->dungeon.getWorldRows());
  RandomNumberGenerator ran2(1, this->dungeon.getWorldColumns());

  unsigned int row,col;

  unsigned int newX = locateCreature(&hero).at(0);
  unsigned int oldX = locateCreature(&hero).at(0);
  unsigned int newY = locateCreature(&hero).at(1);
  unsigned int oldY = locateCreature(&hero).at(1);

  switch(direction)
  {
    case 'w':
            if (newX > 0)
              newX -= confusion;

    break;

    case 's':
      if ( newY < dungeon.getWorldColumns() -1)
        newY += confusion;

    break;

    case 'a':
    if ( newY > 0)
      newY -= confusion;
    break;

    case 'z':
    if ( newX < dungeon.getWorldRows() -1)
      newX += confusion;
    break;

    case 'W':
        if ( newX > 0)
          newX -= confusion;
    break;

    case 'Z':
      if ( newX < dungeon.getWorldRows() -1)
        newX += confusion;
    break;

    case 'A':
    if ( newY > 0)
      newY -= confusion;
    break;

    case 'S':
      if ( newY < dungeon.getWorldColumns() -1)
        newY += confusion;
    break;

  };

  // if trying to an empty space.

  if (dungeon.getMazeSquare(newX,newY) == ' ' &&
  creatures[newX][newY] != creatures[oldX][oldY] && creatures[newX][newY] == 0)
  {
    creatures[newX][newY] = creatures[oldX][oldY];
    creatures[oldX][oldY] = 0;
    return true;
  }
  else
  {
    if (creatures[newX][newY] == 0)
    {
      cout << endl;
      switch(dungeon.getMazeSquare(newX,newY))
      {

        case '*': cout << "Ouch! I cannot walk over obstacles!" << endl;
                  break;

        case 'T': cout << "Ouch! I cannot walk over traps! I am hurt!" << endl;
                  creatures[newX][newY] = creatures[oldX][oldY];
                  creatures[oldX][oldY] = 0;
                hero.setHealth(hero.getHealth() - 1);
                break;
      };
      return true;
    }
    else if (newX == oldX && newY == oldY)
    {
      return true;
    }
    else //is a "creature"
    {
     bool monster = false;
     bool potion = false;
     bool firstAidKit = false;

     for (unsigned int x = 0; x < nrMonsters; x++)
      {
       if (creatures[newX][newY] == &monsters[x])
       {
         monster = true;
       }

       if (x < nrPotions)
        if (creatures[newX][newY] == &potions[x])
          potion = true;

      if (x < nrFirstAidKits)
        if (creatures[newX][newY] == &firstAidKits[x])
          firstAidKit = true;

       if (monster || potion || firstAidKit)
        break;
     }

     if (monster)
     {
       hero.attackEnemy(*creatures[newX][newY]);
       return true;
     }
     else if (potion)
     {
       if (creatures[newX][newY]->getHealth() != 0)
       {
         cout << "Oh dear, I am dizzy, the world is spinning..." << endl;
         confusion = -1;
       }
       else
       {
          cout << "I suddenly have some perspective!" << endl;
          confusion = 1;
       }
       do
       {

         row = ran.nextInt();
         col = ran2.nextInt();

       } while (creatures[row][col] != 0 || dungeon.getMazeSquare(row,col) != ' ');


       creatures[row][col] = creatures[newX][newY];

       creatures[newX][newY] = creatures[oldX][oldY];
       creatures[oldX][oldY] = 0;
     }
     else
     {
       if (hero.getHealth() + creatures[newX][newY]->getHealth() <= (maxHealth))
       {
         hero.setHealth(hero.getHealth() + creatures[newX][newY]->getHealth());
         cout << "Health increased! New health = ";
         cout << hero.getHealth() << endl;
       }
       else
       {
         cout << "Wasted kit! Health cannot be increased with boost." << endl;
         cout << "Went over maximum health. Current health = ";
         cout << hero.getHealth() << endl;
       }

       creatures[newX][newY] = creatures[oldX][oldY];
       creatures[oldX][oldY] = 0;


     }

    }
  }
  return false;
}

void RolePlayingGame::printBoard()
{
//int monsterCount = 0;
for (unsigned int x = 0; x < dungeon.getWorldRows(); x++)
{
  for (unsigned int y = 0; y < dungeon.getWorldColumns(); y++)
  {
    if (creatures[x][y] != 0)
    {
      if (creatures[x][y] == &hero)
      {
        cout << "H";
      }
      else
      {

        bool firstAidKit = false;
        bool potion = false;

        for (unsigned int i = 0; i < nrFirstAidKits; i++)
        {
          if (creatures[x][y] == &firstAidKits[i])
          {
            firstAidKit = true;
          }

        }

        for (unsigned int i = 0; i < nrPotions; i++)
        {
          if (creatures[x][y] == &potions[i])
          {
            potion = true;
          }
        }

        if (firstAidKit)
        {
          cout << "+";
        }
        else if (potion)
        {
          if (creatures[x][y]->getHealth())
            cout << "P";
          else
            cout << "R";
        }
        else
        {
          for (unsigned int i = 0; i < nrMonsters; i++)
          {
            if (creatures[x][y] == &monsters[i])
            {
              cout << i;
            }
          }
        //  cout << monsterCount;
        //++monsterCount;
        }
      }

    }
    else
    {
      cout << dungeon.getMazeSquare(x,y);
    }
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
  return (nrMonsters == 0);
}

void RolePlayingGame::removeDeadMonsters()
{
  for (unsigned int x = 0; x < nrMonsters; x++)
  {
    if (monsters[x].isDead())
    {
      vector<int> location = locateCreature(&monsters[x]);
      creatures[location.at(0)][location.at(1)] = 0;
      //--nrMonsters;
    }
  }
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

  nrMonsters = numMon;
  cout << "Monsters to be entered " << nrMonsters << endl;
  monsters = new Creature[nrMonsters];

  //Placing the monsters
  srand(time(NULL));
  RandomNumberGenerator ran(seed, this->dungeon.getWorldRows());
  RandomNumberGenerator ran2(seed, this->dungeon.getWorldColumns());

  for (unsigned int everyMonster = 0; everyMonster < nrMonsters; everyMonster++)
  {

    do
    {

      row = ran.nextInt();

      col = ran2.nextInt();

    } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns())
     || (dungeon.getMazeSquare(row,col) != ' '));

    monsters[everyMonster] = Creature();
    cout << row << " " << col << endl;
    creatures[row][col] = &monsters[everyMonster];
  }
}

void RolePlayingGame::initializeFirstAidKits(unsigned int seed,
  unsigned int numKits, unsigned int boost)
{
  unsigned int x = nrMonsters/2;
  unsigned row,col;
  do
  {
    if (numKits > x)
    {
      cout << "Too many first aid kits requested.";
      cout << " Maximum " << x << " allowed" << endl;
      cout << "Enter an integer from 0 to ";
      cout << x << ". How many kits should be added: ";
      cin >> numKits;
    }
    if (numKits < 0)
    {
      cout << "Enter an integer from 0 to ";
      cout << x << ". How many kits should be added: ";
      cin >> numKits;
    }
  } while (numKits < 0 || numKits > x);
  nrFirstAidKits =  numKits;

  RandomNumberGenerator ran(seed, this->dungeon.getWorldRows());
  RandomNumberGenerator ran2(seed, this->dungeon.getWorldColumns());

  firstAidKits = new Creature[nrFirstAidKits];

  for (unsigned int x = 0; x < nrFirstAidKits; x++)
  {
    do
    {
      row = ran.nextInt();
      col = ran.nextInt();

    } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns())
    || (dungeon.getMazeSquare(row,col) != ' '));
    firstAidKits[x] = Creature();
    firstAidKits[x].setHealth(boost);
    creatures[row][col] = &firstAidKits[x];
  }
}


void RolePlayingGame::initializePotions(unsigned int seed, unsigned int numPotions)
{
  srand(time(NULL));

  unsigned int x = nrMonsters/2;
  unsigned row,col;
  do
  {
    if (numPotions > x)
    {
      cout << "Too many potions requested.";
      cout << " Maximum " << x << " allowed" << endl;
      cout << "Enter an integer from 0 to ";
      cout << x << ". How many potions should be added: ";
      cin >> numPotions;
    }
    if (numPotions < 0)
    {
      cout << "Enter an integer from 0 to ";
      cout << x << ". How many potions should be added: ";
      cin >> numPotions;
    }
  } while (numPotions < 0 || numPotions > x);


  nrPotions =  numPotions;

  potions = new Creature[nrPotions];

  RandomNumberGenerator ran(seed, this->dungeon.getWorldRows());
  RandomNumberGenerator ran2(seed, this->dungeon.getWorldColumns());

  for (unsigned int x = 0; x < nrPotions; x++)
  {
    do
    {
      row = ran.nextInt();
      col = ran2.nextInt();

    } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns())
    || (dungeon.getMazeSquare(row,col) != ' '));
    potions[x] = Creature();
    if (x % 2)
    {
      potions[x].setHealth(0);
    }
    creatures[row][col] = &potions[x];
  }

}

void RolePlayingGame::initializeHero(unsigned int seed)
{
  hero = Creature();
  unsigned int row,col;
  RandomNumberGenerator ran(seed, this->dungeon.getWorldRows() -2);
  RandomNumberGenerator ran2(seed, this->dungeon.getWorldColumns() -2);
  do
  {
    //row = rand() % dungeon.getWorldRows();
    row = ran.nextInt();
    //col = rand() % dungeon.getWorldColumns();
    col = ran2.nextInt();
  } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns())
  || (dungeon.getMazeSquare(row,col) != ' '));
  creatures[row][col] = &hero;
}

vector<int> RolePlayingGame::locateCreature(Creature* creature)
{
  vector<int> result;
  for (unsigned int x = 0; x < dungeon.getWorldRows(); x++)
    for (unsigned int y = 0; y < dungeon.getWorldColumns(); y++)
      if (creatures[x][y] == creature)
      {
        result.push_back(x);
        result.push_back(y);
      }
return result;
}
