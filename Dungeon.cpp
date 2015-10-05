#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "Dungeon.h"

using namespace std;

Dungeon::Dungeon()
{
  worldRows = 0;
  worldColumns = 0;
  maze = 0;
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
  maze = 0;
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
      cout << endl;
      cout << error;
      exit(0);
  }

  return (maze[row][col]);
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
      cout << endl;
      throw string("The file does not exist. Exiting the program.");

    }
  }
    catch (string error)
    {
      cout << error;
      exit(0);
    }

  //Determine rows and columns

  unsigned int rowRead,columnRead;

  inputFile >> rowRead;

  inputFile >> columnRead;

  if (maze || ( worldRows != rowRead || worldColumns != columnRead ))
  {
    for (unsigned int x = 0; x < worldRows; x++)
    {
      delete maze[x];
    }
    delete [] maze;



    worldRows = rowRead;
    worldColumns = columnRead;

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


  //inputFile.close();
  //inputFile.open(fileName.c_str());
  char inputChar;
  inputFile.get(inputChar);

  unsigned int x, y;
  x = 0;
  y = 0;


  while ( x < worldRows)
  {
    y = 0;
    while ( y < worldColumns)
    {
      inputFile.get(inputChar);

        if (inputChar == 'T' || inputChar == '*' || inputChar == ' ')
        {

          maze[x][y] = inputChar;
          y++;
        }
        else
        {
          if (y+1 == worldColumns - 2)
          {
            x++;
            y = 0;

            maze[x][y] = inputChar;

          }
          else
          {
            x++;
            y = 0;
          }
        }

        if (x >= worldRows || y > worldColumns)
        {
          return;
        }
    }
    x++;
  }


}
