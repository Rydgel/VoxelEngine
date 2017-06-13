#ifndef VOXELSENGINE_GAME_HPP
#define VOXELSENGINE_GAME_HPP

#include <graphics/Window.hpp>
#include <graphics/Timer.hpp>
#include <stack>
#include <experimental/optional>

struct IGameState;

namespace boost = std::experimental;

using WindowPtr = std::unique_ptr<Window>;
using GameStatePtr = std::shared_ptr<IGameState>;
using GameStateStack = std::stack<GameStatePtr>;
using MaybeGameState = boost::optional<GameStatePtr>;

struct Game
{
    explicit Game();
    ~Game();
    Game(const Game & game) = delete;
    Game & operator=(Game & game) = delete;
    Game(Game && game) noexcept = delete;
    Game & operator=(Game && game) noexcept = delete;

    void pushState(GameStatePtr state);
    void popState();
    void changeState(GameStatePtr state);
    MaybeGameState peekState();
    void gameLoop();
    WindowPtr & getWindowRef();
    InputManager & getInputManager();

private:

    const int windowWidth_ = 1200;
    const int windowHeight_ = 800;
    const char * windowTitle_ = "Voxels!";

    WindowPtr windowPtr_;
    InputManager inputManager_;
    Timer timer_ {};
    GameStateStack states_;
};


#endif //VOXELSENGINE_GAME_HPP
