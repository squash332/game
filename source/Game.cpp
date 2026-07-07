#include "Game.hpp"

Game::Game() {
    game_window_ = std::make_unique<Window>();
    player_ = std::make_unique<Player>("filip");
    input_ = std::make_unique<InputManager>();
    renderer_ = std::make_unique<Renderer>();

    input_->bind(KEY_F10, [this] {game_window_->toggleFullscreen();});

}

void Game::run() {

    while(!game_window_->shouldClose()) {
        input_->update();
        game_window_->beginFrame();
        ClearBackground(WHITE);

        renderer_->drawPlayer(*player_);
        player_->update();
        std::cout << "updated player" << std::endl;
        std::cout << player_->getX() <<  ","  << player_->getY() << std::endl;


        game_window_->endFrame();
    }

}