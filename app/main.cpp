#include <iostream>
#include <states/PlayState.hpp>
#include <Game.hpp>

int main(int argc, char **argv)
{
    Game game;
    game.pushState(std::make_unique<PlayState>(game));
    game.gameLoop();
}