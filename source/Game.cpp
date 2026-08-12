#include "Game.hpp"

Game::Game()
    : game_window_(),
      player_("filip"),
      input_(),
      renderer_(),
      map_("res/testmap.json"),
      cam_(),
      hud_()
{
    enemies_.push_back(std::make_unique<Enemy>("knight"));

    input_.bindPressed(KEY_F10, [this]
                       { game_window_.toggleFullscreen(); });
    input_.bindHeld(KEY_W, [this]
                    { player_.addDirection(Direction::Up); });
    input_.bindHeld(KEY_A, [this]
                    { player_.addDirection(Direction::Left); });
    input_.bindHeld(KEY_S, [this]
                    { player_.addDirection(Direction::Down); });
    input_.bindHeld(KEY_D, [this]
                    { player_.addDirection(Direction::Right); });
    input_.bindPressed(KEY_T, [this]
                       { toggleDebugMode(); });
}

void Game::run()
{
    while (!game_window_.shouldClose())
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

        input_.update();
        player_.update(delta_time, frame);
        if (collision::isTileWalkable(player_.getPlayerRect(), map_)) {
            player_.confirmMove();
        }
        cam_.update(player_.getX(), player_.getY(), delta_time);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            handleTargetClick();
        }

        game_window_.beginFrame();
        ClearBackground(BLACK);
        cam_.beginFrame();

        renderer_.drawMap(map_);
        renderer_.drawNameplate(player_);

        for (auto &enemy : enemies_)
        {
            bool targeted = (current_target == enemy.get());
            renderer_.drawNameplate(*enemy, targeted);
            renderer_.drawEnemy(*enemy);
        }
        renderer_.drawPlayer(player_);

        // draw player rectangle hitbox
        if (debug_mode)
            DrawRectangleLines(player_.getX(), player_.getY(), player_.getWidth(), player_.getHeight(), GREEN);
        // std::cout << player_.getX() << "," << player_.getY() << std::endl;
        // std::cout << "cols: " << map_.getCols() << " rows: " << map_.getRows() <<std::endl;
        cam_.endFrame();

        hud_.drawPlayerFrame(player_);
        if (current_target != nullptr)
            hud_.drawTargetedFrame(*current_target);

        hud_.drawPlayerFrame(player_);
        if (current_target != nullptr)
            hud_.drawTargetedFrame(*current_target);

        displayLogs();
        game_window_.endFrame();
    }
}

void Game::toggleDebugMode()
{
    debug_mode = !debug_mode;
}

void Game::displayLogs()
{
    if (!debug_mode)
        return;

    // display fps
    // DrawFPS(0, 0);

    // tile pos under player pos :
    int playerTileX = (int)floorf(player_.getX() / TILE_SIZE);
    int playerTileY = (int)floorf(player_.getY() / TILE_SIZE);

    // display player coordinates
    DrawText("x position: ", 0, VIRTUAL_HEIGHT - 20, 15, RED);
    DrawText("y position: ", 0, VIRTUAL_HEIGHT - 40, 15, RED);
    DrawText("tile position: ", 0, VIRTUAL_HEIGHT - 60, 15, RED);
    DrawText(std::to_string((int)player_.getX()).c_str(), 80, VIRTUAL_HEIGHT - 20, 15, RED);
    DrawText(std::to_string((int)player_.getY()).c_str(), 80, VIRTUAL_HEIGHT - 40, 15, RED);

    DrawText(std::to_string(playerTileX).c_str(), 90, VIRTUAL_HEIGHT - 60, 15, RED);
    DrawText(std::to_string(playerTileY).c_str(), 110, VIRTUAL_HEIGHT - 60, 15, RED);
}

void Game::handleTargetClick()
{
    // select nothing is default
    // TODO :: later when combat implemented, it will feel bad and clunky
    // turn off not targeting anything when in combat
    // or maybe hide mouse while holding right click just like in wow or maybe untarget just with ESCAPE
    current_target = nullptr;

    // compute mouse position in our game in relation to camera
    Vector2 mouseScreen = GetMousePosition();
    Vector2 mouseWorld = GetScreenToWorld2D(mouseScreen, cam_.getCamera());

    for (auto &enemy : enemies_)
    {
        Rectangle bounds = {enemy->getX(), enemy->getY(), enemy->getWidth(), enemy->getHeight()};
        if (CheckCollisionPointRec(mouseWorld, bounds))
        {
            current_target = enemy.get();
            break;
        }
    }

    Rectangle player = {player_.getX(), player_.getY(), player_.getWidth(), player_.getHeight()};

    if (CheckCollisionPointRec(mouseWorld, player))
    {
        current_target = &player_;
        return;
    }
}
