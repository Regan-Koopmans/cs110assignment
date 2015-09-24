#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
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
  maze = new char * [worldRows];
  for (unsigned int x = 0; x < worldRows; x++)
  {
    maze[x] = new char[worldColumns];
    for (unsigned int y = 0; y < worldColumns; y++)
    {
      maze[x][y] = ' ';
    }
  }
}

Dungeon::Dungeon(string fileName)
{
  worldRows = 0;
  worldColumns = 0;
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
    if (row >= worldRows || col >= worldColumns)
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
  ifstream inputFile;
  inputFile.open(fileName.c_str());
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

  //Determine rows and columns

  inputFile >> worldRows;

  inputFile >> worldColumns;


  //allocate the maze.

  maze = new char * [worldRows];
  for (unsigned int x = 0; x < worldRows; x++)
  {
    maze[x] = new char[worldColumns];
    for (unsigned int y = 0; y < worldColumns; y++)
    {
      maze[x][y] = ' ';
    }
  }


  for (unsigned int x = 0; x < worldRows; x++)
  {
    for (unsigned int y = 0; y < worldColumns; y++)
    {
      inputFile.get(maze[x][y]);
    //  cout << maze[x][y];
    }
  }

}
