#include <iostream>
#include "RolePlayingGame.h"

using namespace std;

int main() {
    RolePlayingGame game(20, 10, 5, 5, 8, 30);  //change values here to test
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



