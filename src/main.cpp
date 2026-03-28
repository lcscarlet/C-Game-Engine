#include <iostream>
#include <SDL.h>
#include "game.h"

int main(int argc, char* argv[]) {
    Game game;

    game.Initialize();

    game.Run();

    game.Destroy();

    return 0;
}