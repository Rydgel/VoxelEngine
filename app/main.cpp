#include <iostream>
#include <states/PlayState.hpp>
#include <Game.hpp>

int main()
{
    Game game;
    game.pushState(std::make_shared<PlayState>(game));
    game.gameLoop();
}