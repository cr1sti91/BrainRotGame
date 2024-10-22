#include "game.h"

int main()
{
    Game* game = new Game(width, height, gameName, frameLimit);  

    game->run(); 

    delete game; 

    return 0; 
}