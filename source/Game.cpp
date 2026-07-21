#include "Game.hpp"

Game::Game()
{
    game_window_ = std::make_unique<Window>();
    player_ = std::make_unique<Player>("filip");
    input_ = std::make_unique<InputManager>();
    renderer_ = std::make_unique<Renderer>();
    map_ = std::make_unique<Map>("res/testmap.json");
    cam_ = std::make_unique<Cam2d>();

    input_->bind(KEY_F10, [this]
                 { game_window_->toggleFullscreen(); });
    input_->bind(KEY_W, [this]
                 { player_->addDirection(Direction::Up); });
    input_->bind(KEY_A, [this]
                 { player_->addDirection(Direction::Left); });
    input_->bind(KEY_S, [this]
                 { player_->addDirection(Direction::Down); });
    input_->bind(KEY_D, [this]
                 { player_->addDirection(Direction::Right); });
}

void Game::run()
{
    while (!game_window_->shouldClose())
    {
        input_->update();
        player_->update();
        player_->confirmMove();
        cam_->update(player_->getX(), player_->getY());

        game_window_->beginFrame();
        ClearBackground(BLACK);
        
        cam_->beginFrame();
        
        renderer_->drawMap(*map_);
        renderer_->drawPlayer(*player_);
        std::cout << player_->getX() << "," << player_->getY() << std::endl;
        cam_->endFrame();
        renderer_->displayLogs();
        game_window_->endFrame();
    }
}
