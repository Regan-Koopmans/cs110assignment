#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <vector>

#include "RandomNumberGenerator.h"
#include "Dungeon.h"
#include "RolePlayingGame.h"
#include "Hero.h"

using namespace std;

int confusion = 1;

// RolePlayingGame::RolePlayingGame(unsigned int seed, unsigned int nrMon,
//   unsigned int nrKits, unsigned int nrPotions, unsigned int boost,
//   unsigned int maxHealth)
// {
//     //initialize the dungeon to be empty
//
//     this->dungeon.readInMaze("mazeExample.txt");
//
//
//
//     initializeCreatures();
//
//     initializeHero(seed);
// 
//
//
//     initializeMonsters(seed, nrMon);
//
//
//
//     initializePotions(seed, nrPotions);
//
//
//
//     initializeFirstAidKits(seed, nrKits, boost);
//
//
//     this->maxHealth = maxHealth;
// }

RolePlayingGame::~RolePlayingGame()
{
//  delete [] monsters;
  delete monsters;
//  monsters = 0;
}

bool RolePlayingGame::moveHero(const char direction)
{

  RandomNumberGenerator ran(1, (this->dungeon.getWorldRows()-2)*1000);
  RandomNumberGenerator ran2(1, (this->dungeon.getWorldColumns()-2)*1000);

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

         row = (ran.nextInt())/1000;
         col = (ran2.nextInt())/1000;

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
      if (location.size() == 2)
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
  int inputNumber = (int)numMon;

  do
  {
    try
    {
      if (inputNumber < 1)
        throw string("Enter an integer from 1 to 10. How many monsters should be added: ");

      if (inputNumber > 10)
        throw string("Too many monsters requested. Maximum 10 allowed.\nHow many monsters should be added: ");
    }
    catch (string error)
    {
      cout << endl;
      cout << error;
      cin >> inputNumber;
    }
  } while (inputNumber < 1 || inputNumber > 10);

  nrMonsters = (unsigned int)inputNumber;
  monsters = new Creature[nrMonsters];

  //Placing the monsters
  RandomNumberGenerator ran(seed, (this->dungeon.getWorldRows()-2)*1000);
  RandomNumberGenerator ran2(seed, (this->dungeon.getWorldColumns()-2)*1000);

  for (unsigned int everyMonster = 0; everyMonster < nrMonsters; everyMonster++)
  {
    do
    {

      row = (ran.nextInt())/1000;

      col = (ran2.nextInt())/1000;

    } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns())
     || (dungeon.getMazeSquare(row,col) != ' ') || creatures[row][col] != 0);

    monsters[everyMonster] = Creature();
    creatures[row][col] = &monsters[everyMonster];
  }
}

void RolePlayingGame::initializeFirstAidKits(unsigned int seed,
  unsigned int numKits, unsigned int boost)
{
  int inputNumber = numKits;
  unsigned int x = nrMonsters/2;
  stringstream ss;
  ss << x;
  unsigned row,col;
  do
  {
    try
    {
      if ((unsigned int)inputNumber > x)
      {
          string errorString = "Too many first aid kits requested. Maximum ";

          errorString.append(ss.str());
          errorString += " allowed.";
          errorString += "\nEnter an integer from 0 to ";
          errorString.append(ss.str());
          errorString += ". How many kits should be added: ";
          throw errorString;
      }

      if (inputNumber < 0)
      {
        string errorString = "Enter an integer from 0 to ";
        errorString.append(ss.str());
        errorString += ". How many kits should be added: ";
        throw errorString;
      }


    }
    catch (string error)
    {
      cout << endl;
      cout << error;
      cin >> inputNumber;
    }
  } while (inputNumber < 0 || (unsigned int)inputNumber > x);
  nrFirstAidKits =  inputNumber;

  RandomNumberGenerator ran(seed, (this->dungeon.getWorldRows()-2)*1000);
  RandomNumberGenerator ran2(seed, (this->dungeon.getWorldColumns()-2)*1000);

  firstAidKits = new Creature[nrFirstAidKits];

  for (unsigned int x = 0; x < nrFirstAidKits; x++)
  {
    do
    {
      row = (ran.nextInt())/1000;
      col = (ran.nextInt())/1000;

    } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns())
    || (dungeon.getMazeSquare(row,col) != ' ') || creatures[row][col] != 0);
    firstAidKits[x] = Creature();
    firstAidKits[x].setHealth(boost);
    creatures[row][col] = &firstAidKits[x];
  }
}


void RolePlayingGame::initializePotions(unsigned int seed, unsigned int numPotions)
{

  int x = nrMonsters/2;
  stringstream ss;
  ss << x;
  int inputNumber = numPotions;
  do
  {
  try
  {
    if (inputNumber > x)
    {
        string errorString = "Too many potions requested. Maximum ";

        errorString.append(ss.str());
        errorString += " allowed.";
        errorString += "\nEnter an integer from 0 to ";
        errorString.append(ss.str());
        errorString += ". How many potions should be added: ";
        throw errorString;
    }

    if (inputNumber < 0)
    {
      string errorString = "Enter an integer from 0 to ";
      errorString.append(ss.str());
      errorString += ". How many potions should be added: ";
      throw errorString;
    }

  }
  catch (string error)
  {
    cout << endl;
    cout << error;
    cin >> inputNumber;
  }
  } while (inputNumber < 0 || inputNumber > x);

  nrPotions = inputNumber;
  nrPotions = (unsigned int)inputNumber;

  potions = new Creature[nrPotions];

  unsigned int row,col;

  RandomNumberGenerator ran(seed, (this->dungeon.getWorldRows()-2)*1000);
  RandomNumberGenerator ran2(seed, (this->dungeon.getWorldColumns()-2)*1000);

  for (unsigned int x = 0; x < nrPotions; x++)
  {
    do
    {
      row = (ran.nextInt())/1000;
      col = (ran2.nextInt())/1000;

    } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns())
    || (dungeon.getMazeSquare(row,col) != ' ') || creatures[row][col] != 0);
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
  RandomNumberGenerator ran(seed, (this->dungeon.getWorldRows() -2)*1000);
  RandomNumberGenerator ran2(seed, (this->dungeon.getWorldColumns() -2)*1000);

  do
  {
    row = (ran.nextInt())/1000;
    col = (ran2.nextInt())/1000;

  } while ((row >= dungeon.getWorldRows() || col >= dungeon.getWorldColumns())
  || (dungeon.getMazeSquare(row,col) != ' ') || creatures[row][col] != 0);

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
