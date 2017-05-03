#ifndef VOXELSENGINE_IGAMESTATE_HPP
#define VOXELSENGINE_IGAMESTATE_HPP

struct Game;

struct IGameState
{
    explicit IGameState(Game & game): game_(game) { }
    virtual void events(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;

protected:

    Game & game_;
};

#endif //VOXELSENGINE_IGAMESTATE_HPP
