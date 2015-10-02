#ifndef CREATURE_H
#define	CREATURE_H

class Creature
{
public:
    Creature();
    void attackEnemy(Creature& defender);
    bool isDead();
    void setHealth(unsigned int h);
    unsigned int getHealth() const;
private:
    unsigned int attack;
    unsigned int defense;
    unsigned int health;
};

#endif	//CREATURE_H 

