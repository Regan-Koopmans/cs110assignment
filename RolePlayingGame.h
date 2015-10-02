#ifndef ROLEPLAYINGGAME_H
#define	ROLEPLAYINGGAME_H

#include "Creature.h"
#include "Dungeon.h"
#include <vector>

class RolePlayingGame
{
public:
    RolePlayingGame(unsigned int seed, unsigned int nrMon, unsigned int nrKits, unsigned int nrPotions, unsigned int boost, unsigned int maxHealth);
    ~RolePlayingGame();
    
    bool moveHero(const char direction);
    void printBoard();
    bool heroIsDead();
    bool allMonstersDead();
    void removeDeadMonsters();
    
    unsigned int getNrMonsters() const;
    void setNrMonsters(unsigned int n);
    unsigned int getNrFirstAidKits() const;
    void setNrFirstAidKits(unsigned int f);
    unsigned int getNrPotions() const;
    void setNrPotions(unsigned int p);
    
private:
    void initializeCreatures();
    void initializeMonsters(unsigned int seed, unsigned int numMon);
    void initializeFirstAidKits(unsigned int seed, unsigned int numKits, unsigned int boost);
    void initializePotions(unsigned int seed, unsigned int numPotions);
    void initializeHero(unsigned int seed);
    
    vector<int> locateCreature(Creature* creature);
    
    Dungeon dungeon;
    Creature hero;
    Creature* monsters; 
    Creature* firstAidKits;
    Creature* potions;
    Creature*** creatures; 
    unsigned int nrMonsters;
    unsigned int nrPotions;
    unsigned int nrFirstAidKits;
    unsigned int healthBoost;
    unsigned int maxHealth;
};

#endif	//ROLEPLAYINGGAME_H 

