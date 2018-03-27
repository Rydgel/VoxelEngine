#ifndef VOXELSENGINE_PLAYSTATE_HPP
#define VOXELSENGINE_PLAYSTATE_HPP

#include "graphics/models/World.hpp"
#include "Game.hpp"
#include "IGameState.hpp"

struct PlayState : public IGameState
{
    explicit PlayState(Game & game);
    void events(float dt) override;
    void update(float dt) override;
    void draw(float dt) override;

private:

    WindowPtr windowPtr_;
    InputManager & inputManager_;
    World world_;
};


#endif //VOXELSENGINE_PLAYSTATE_HPP
