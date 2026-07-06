#include "Game.hpp"

Game::Game() {
    game_window_ = std::make_unique<Window>();
    player_ = std::make_unique<Player>("filip");
    input_ = std::make_unique<InputManager>();

    input_->bind(KEY_F10, [this] {game_window_->toggleFullscreen();});

}

void Game::run() {

    SetTargetFPS(60);

    while(!game_window_->shouldClose()) {
        game_window_->beginFrame();
        input_->update();

        ClearBackground(BLACK);

        game_window_->endFrame();
    }

}