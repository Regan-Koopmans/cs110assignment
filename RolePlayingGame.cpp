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

