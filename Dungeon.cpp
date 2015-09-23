#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Dungeon.h"

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
  readInMaze(fileName);
}

Dungeon::~Dungeon()
{
  for (int x = 0; x < worldRows; x++)
  {
    delete [] map[x];
  }
  delete [] map;
}

char Dungeon::getMazeSquare(unsigned int row, unsigned int col)
{
  if (row > worldRows || col > worldColumns)
  {
    cout << "Invalid cell in dungeon. Exiting the game." << endl;
    exit(0);
  }
  return maze[row][col];
}

unsigned int Dungeon::getWorldRows()
{
  return worldRows;
}

void Dungeon::setWorldRows(unsigned int r)
{
  worldRows = r;
}

unsigned int Dungeon::getWorldColumns()
{
  return worldColumns;
}

void Dungeon::setWorldColumns(unsigned int c)
{
  worldColumns = c;
}

void Dungeon::readInMaze(string fileName)
{
  ifstream inputFile(fileName);
  if (!inputFile.good())
  {
    cout << "The file does not exist. Exiting the program." << endl;
    exit(0);
  }
}
