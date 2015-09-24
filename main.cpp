#include <iostream>
#include <vector>
#include "RandomNumberGenerator.h"
#include "RolePlayingGame.h"

using namespace std;

int main() {

    //RandomNumberGenerator rndGen = RandomNumberGenerator(15,20);

    RolePlayingGame game((unsigned int)20, (unsigned int)10, (unsigned int)5, (unsigned int)8, (unsigned int)30, (unsigned int)30);  //change values here to test
    bool gameOver = false;

    do
    {
        game.printBoard();

        //get the next move
        char move;
        cout << "Use W, A, S or Z to move:" << endl;
        cin >> move;

        //check if move is valid
        if (game.moveHero(move))
        {
            //if the hero is dead
            if (game.heroIsDead())
            {
                cout << "You have died!" << endl;
                gameOver = true;
            }
            else
            {
                //remove the dead monsters from the game
                game.removeDeadMonsters();
                //if all the monsters are dead
                if (game.allMonstersDead())
                {
                    cout << "Dungeon cleared!" << endl;
                    gameOver = true;
                }
            }
        }

    }
    while (!gameOver);

    return 0;
}
