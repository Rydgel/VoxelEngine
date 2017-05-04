#include <sstream>
#include <imgui.h>
#include <graphics/gui/imgui_impl_glfw_gl3.h>
#include "states/IGameState.hpp"
#include "Game.hpp"

Game::Game()
{
    windowPtr_ = std::make_unique<Window>(inputManager_, windowWidth_, windowHeight_, windowTitle_);
    timer_.init();
}

Game::~Game()
{
    while (!states_.empty())
        popState();
    windowPtr_->closeWindow();
}

InputManager & Game::getInputManager()
{
    return inputManager_;
}

void Game::pushState(GameStatePtr state)
{
    states_.push(std::move(state));
}

void Game::popState()
{
    states_.pop();
}

void Game::changeState(GameStatePtr state)
{
    if (!states_.empty())
        popState();
    pushState(std::move(state));
}

boost::optional<GameStatePtr &> Game::peekState()
{
    if (states_.empty())
        return boost::nullopt;
    auto & currentState = states_.top();
    return boost::optional<GameStatePtr &>(currentState);
}

void Game::gameLoop()
{
    while (windowPtr_->isOpen())
    {
        const float dt = timer_.getDelta();

        auto currentState = peekState();
        if (!currentState.has_value())
            continue;

        // todo make a new class to handle custom GUI windows when needed
        ImGui_ImplGlfwGL3_NewFrame();

        // Check and call events
        windowPtr_->pollEvents();
        currentState.value()->events(dt);

        /* Update game and timer UPS */
        currentState.value()->update(dt);
        timer_.updateUPS();

        /* Render game and update timer FPS */
        glClearColor(0.73f, 0.82f, 0.89f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentState.value()->draw(dt);

        timer_.updateFPS();

        /* Update timer */
        timer_.update();

        // display fps
        std::ostringstream out;
        out << "Voxels • FPS: " << timer_.getFPS() << " | UPS: " << timer_.getUPS();
        windowPtr_->changeTitle(out.str().c_str());

        // render the GUI
        ImGui::Render();
        // Swap the buffers
        windowPtr_->swapBuffers();
    }
}

WindowPtr & Game::getWindowRef()
{
    return windowPtr_;
}