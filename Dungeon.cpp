#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "Dungeon.h"

using namespace std;

Dungeon::Dungeon()
{

}

Dungeon::Dungeon(unsigned int rows, unsigned int col)
{
  worldRows = rows;
  worldColumns = col;
}

Dungeon::Dungeon(string fileName)
{
  worldRows = -1;
  worldColumns = -1;
  readInMaze(fileName);
}

Dungeon::~Dungeon()
{
  for (unsigned int x = 0; x < worldRows; x++)
  {
    delete [] maze[x];
  }
  delete [] maze;
}

char Dungeon::getMazeSquare(unsigned int row, unsigned int col) const
{
  try
  {
    if (row > worldRows || col > worldColumns)
    {
      throw string("Invalid cell in dungeon. Exiting the game.");
    }
  }
  catch (string error)
  {
      cout << error << endl;
      exit(0);
  }

  return maze[row][col];
}

unsigned int Dungeon::getWorldRows() const
{
  return worldRows;
}

void Dungeon::setWorldRows(unsigned int r)
{
  worldRows = r;
}

unsigned int Dungeon::getWorldColumns() const
{
  return worldColumns;
}

void Dungeon::setWorldColumns(unsigned int c)
{
  worldColumns = c;
}

void Dungeon::readInMaze(string fileName)
{
  ifstream inputFile(fileName.c_str());
  try
  {
    if (!inputFile.good())
    {
      throw string("The file does not exist. Exiting the program.");

    }
  }
    catch (string error)
    {
      cout << error << endl;
      exit(0);
    }

  int y = 0;
  int x = 0;
  char oneTile;

  while(!inputFile.eof())
  {
    inputFile >> oneTile;

    if (oneTile == '\n')
    {
      x = 0;
      y++;
      inputFile >> oneTile;
      maze[x][y] = oneTile;
    }
    else
    {
      x++;
      maze[x][y] = oneTile;
    }
  }

  worldRows = x;
  worldRows = y;

}
