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
    input_->bind(KEY_T, [this]
                 { toggleDebugMode(); });
}

void Game::run()
{

    while (!game_window_->shouldClose())
    {

        delta_time = GetFrameTime();
        timer += delta_time;
        if (timer >= 0.2f)
        {
            timer = 0.0f;
            frame++;
        }
        frame = frame % 2;
        // std::cout << frame << std::endl;

        input_->update();
        player_->update(delta_time, frame);
        player_->confirmMove();
        cam_->update(player_->getX(), player_->getY(), delta_time);

        game_window_->beginFrame();
        ClearBackground(BLACK);

        cam_->beginFrame();

        renderer_->drawMap(*map_);
        renderer_->drawPlayer(*player_);
        std::cout << player_->getX() << "," << player_->getY() << std::endl;
        // std::cout << "cols: " << map_->getCols() << " rows: " << map_->getRows() <<std::endl;
        displayLogs(*map_);
        cam_->endFrame();
        DrawFPS(0, 0);
        game_window_->endFrame();
    }
}

void Game::toggleDebugMode()
{
    debug_mode = !debug_mode;
}

void Game::displayLogs(const Map &m)
{
    if (!debug_mode)
        return;

    for (auto y{0}; y <= m.getRows(); y++)
    {
        for (auto x{0}; x <= m.getCols(); x++)
        {
            DrawLine(x * TILE_SIZE, y * TILE_SIZE, x * TILE_SIZE, VIRTUAL_HEIGHT, RED);
            DrawLine(x * TILE_SIZE, y * TILE_SIZE, VIRTUAL_WIDTH, y * TILE_SIZE, RED);
        }
    }
}
