#include "PlayState.hpp"


PlayState::PlayState(Game & game)
: IGameState(game)
, windowPtr_(game_.getWindowRef())
, inputManager_(game_.getInputManager())
, world_(game_)
{
}

void PlayState::events(const float dt)
{
    if (inputManager_.getKeyState(GLFW_KEY_ESCAPE)) {
        windowPtr_->closeWindow();
    }
}

void PlayState::update(const float dt)
{
    world_.update(dt);
}

void PlayState::draw(const float dt)
{
    world_.draw(dt);
}
