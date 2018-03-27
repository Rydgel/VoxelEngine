#ifndef VOXELSENGINE_GAME_HPP
#define VOXELSENGINE_GAME_HPP

#include <stack>
#include <optional>
#include "graphics/Window.hpp"
#include "graphics/Timer.hpp"

struct IGameState;

using WindowPtr = std::shared_ptr<Window>;
using GameStatePtr = std::shared_ptr<IGameState>;
using GameStateStack = std::stack<GameStatePtr>;
using MaybeGameState = std::optional<GameStatePtr>;

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
    WindowPtr getWindow();
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
