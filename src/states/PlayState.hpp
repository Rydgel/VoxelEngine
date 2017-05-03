#ifndef VOXELSENGINE_PLAYSTATE_HPP
#define VOXELSENGINE_PLAYSTATE_HPP

#include <graphics/voxels/World.hpp>
#include <Game.hpp>
#include "IGameState.hpp"

struct PlayState : public IGameState
{
    explicit PlayState(Game & game);
    virtual void events(float dt);
    virtual void update(float dt);
    virtual void draw(float dt);

private:

    WindowPtr & windowPtr_;
    InputManager & inputManager_;
    World world_;
};


#endif //VOXELSENGINE_PLAYSTATE_HPP
