#ifndef DUNGEON_H
#define	DUNGEON_H

#include <string>

using namespace std;

class Dungeon
{
public:
    Dungeon();
    Dungeon(unsigned int rows, unsigned int col);
    Dungeon(string fileName);
    ~Dungeon();
    
    char getMazeSquare(unsigned int row, unsigned int col) const;
    unsigned int getWorldRows() const;
    void setWorldRows(unsigned int r);
    unsigned int getWorldColumns() const;
    void setWorldColumns(unsigned int c);
    
    void readInMaze(string fileName);
    
private:
    unsigned int worldRows;
    unsigned int worldColumns;
    char** maze;
};

#endif	//DUNGEON_H 

