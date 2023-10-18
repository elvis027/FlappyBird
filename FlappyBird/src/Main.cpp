#include "Game/Game.h"

int main(int argc, char* argv[])
{
    Game* game= new Game();

    game->GamePlay();

    delete game;

    return 0;
}
