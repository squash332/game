#include "Game.hpp"

Game::Game()
    : game_window_(),
      player_("filip"),
      input_(),
      renderer_(),
      map_("res/testmap.json"),
      cam_(),
      hud_(),
      action_bar_(),
      drawn_menu(false),
      in_edit_mode(false),
      cached_player_frame_{0},
      cached_target_frame_{0},
      cached_focus_frame_{0},
      save_btn_{0},
      discard_btn_{0},
      cached_action_bar_{0}
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
    input_.bindPressed(KEY_ONE, [this]
                       { tryAttack(); });
    input_.bindPressed(KEY_ESCAPE, [this]
                       { handleEscapeKey(); });
}

void Game::run()
{
    while (!game_window_.shouldClose())
    {
        updateMouse();

        delta_time = GetFrameTime();
        timer += delta_time;
        if (timer >= 0.1f)
        {
            timer = 0.0f;
            frame++;
        }
        updateTargetRange();

        if (in_edit_mode)
        {
            updateEditMode();
        }
        
        input_.update();
        player_.update(delta_time, frame);
        tryMove();

        cam_.update(player_.getX(), player_.getY(), delta_time);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!in_edit_mode) 
                handleTargetClick();

            handleMenuClick();
        }

        // start drawing
        game_window_.beginFrame();
        ClearBackground(BLACK);

        // start camera
        cam_.beginFrame();

        renderer_.drawMap(map_);
        renderer_.drawNameplate(player_);
        renderer_.drawPlayer(player_);

        updateEnemies();
        handleDebugMode();
        cam_.endFrame();
        // end camera

        action_bar_.draw(player_);
        hud_.drawPlayerFrame(player_);
        if (current_target != nullptr) hud_.drawTargetedFrame(*current_target);
        if (drawn_menu) hud_.drawSettingsWindow();
        if (in_edit_mode) drawEditMode();


        displayLogs();
        game_window_.endFrame();
        // end drawing
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

    // compute mouse position in our game in relation to camera
    Vector2 mouseWorld = GetScreenToWorld2D(mouse, cam_.getCamera());
    // if player clicks on his player frame, nothing happens
    if (current_target != nullptr && CheckCollisionPointRec(mouse, hud_.getTargetFrame()))
        return;
    if (current_target != nullptr && CheckCollisionPointRec(mouse, hud_.getPlayerFrame()))
    {
        current_target = &player_;
        return;
    }
    if (current_target == nullptr && CheckCollisionPointRec(mouse, hud_.getPlayerFrame()))
    {
        current_target = &player_;
        return;
    }

    // current_target = nullptr;

    for (auto &enemy : enemies_)
    {
        Rectangle bounds = {enemy->getX(), enemy->getY(), enemy->getSpriteWidth(), enemy->getSpriteHeight()};
        if (CheckCollisionPointRec(mouseWorld, bounds))
        {
            current_target = enemy.get();
            return;
        }
    }

    Rectangle player = {player_.getX(), player_.getY(), player_.getSpriteWidth(), player_.getSpriteHeight()};

    if (CheckCollisionPointRec(mouseWorld, player) || CheckCollisionPointRec(mouseWorld, hud_.getPlayerFrame()))
    {
        current_target = &player_;
        return;
    }
}

void Game::tryMove()
{
    Rectangle MovementX = player_.getHitboxAt(player_.getNextX(), player_.getY());
    bool canX = collision::isTileWalkable(MovementX, map_);

    Rectangle MovementY = player_.getHitboxAt(player_.getX(), player_.getNextY());
    bool canY = collision::isTileWalkable(MovementY, map_);

    player_.confirmMove(canX, canY);
}


void Game::updateEnemies()
{
    for (auto &enemy : enemies_)
    {
        bool targeted = (current_target == enemy.get());
        renderer_.drawNameplate(*enemy, targeted);
        renderer_.drawEnemy(*enemy);

        if (debug_mode)
        {
            DrawRectangleLines(enemy->getX(), enemy->getY(), enemy->getSpriteWidth(), enemy->getSpriteHeight(), RED);
            Rectangle e_hitbox = enemy->getHitboxAt(enemy->getX(), enemy->getY());
            DrawRectangleLines(e_hitbox.x, e_hitbox.y, e_hitbox.width, e_hitbox.height, GREEN);
        }
    }
}

void Game::updateTargetRange()
{
    if (current_target == nullptr)
        return;

    bool in_range = collision::isInMeleeRange(player_, *current_target);
    player_.setMeleeRange(in_range);
}

void Game::tryAttack()
{
    // without this, spamming the ability fast removes the target's hp even though player attacked once
    if (player_.isAttacking())
    {
        return;
    }
    if (current_target == nullptr)
    {
        std::cout << "You don't have a target." << std::endl;
        return;
    }
    if (current_target->is_ally_ == true)
    {
        std::cout << "Current target is not hostile." << std::endl;
        return;
    }
    if (!player_.isInMeleeRange() && current_target != nullptr)
    {
        std::cout << "You are out of range." << std::endl;
        return;
    }

    // compare the melee circles and turn the player towards his target when attacking and retain this position
    MeleeRangeCircle player_circle = player_.getMeleeHitbox();
    MeleeRangeCircle target_circle = current_target->getMeleeHitbox();
    Direction facing_towards_enemy = getDirectionToTarget(player_circle.center.x, player_circle.center.y, target_circle.center.x, target_circle.center.y);

    player_.attack(facing_towards_enemy);

    // TODO: make the abilities a struct and then extract the damage, cost, cooldown etc based on need (here damage which is being dealt)
    current_target->takeDamage(20);
}

void Game::handleDebugMode()
{
    // green - collision box
    // red - spritesheet draw box (nameplate size or?)
    if (debug_mode)
    {
        DrawRectangleLines(player_.getX(), player_.getY(), player_.getSpriteWidth(), player_.getSpriteHeight(), RED);
        Rectangle hitbox = player_.getHitboxAt(player_.getX(), player_.getY());
        DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, GREEN);
        renderer_.drawCircle(player_);
        for (const auto &Enemy : enemies_)
        {
            auto x = Enemy.get();
            renderer_.drawCircle(*x);
        }
    }
}

// function called in lambda on pressing ESC key button
void Game::handleEscapeKey()
{
    // first remove current target, then on another 'ESC' click open the settings menu
    if (current_target != nullptr)
    {
        current_target = nullptr;
        return;
    }

    drawn_menu = !drawn_menu;
    in_edit_mode = false;
}

void Game::handleMenuClick()
{
    // if edit mode button clicked, hide menu, cache current positions and return
    if (CheckCollisionPointRec(mouse, hud_.getBtnEditModeBounds()))
    {
        drawn_menu = false;
        cachePositions();
        std::cout << "clicked on edit mode" << std::endl;
        return;
    }

    // if not in edit mode, don't even check for button clicks
    if (!in_edit_mode) return; 

    if (CheckCollisionPointRec(mouse, save_btn_.bounds))
    {
        endEditMode(true);
        return;
    }
    if (CheckCollisionPointRec(mouse, discard_btn_.bounds))
    {
        endEditMode(false);
        std::cout << "end edit mode false called" << std::endl;
        return;
    }
}

void Game::cachePositions()
{
    if (in_edit_mode) return; // cache only once entering edit mode, then stop caching

    in_edit_mode = true;
    cached_player_frame_ = hud_.getPlayerFrame();
    cached_target_frame_ = hud_.getTargetFrame();
    cached_action_bar_ = action_bar_.getActionBar();
    std::cout << "cached!!" << std::endl;
}


void Game::updateEditMode()
{
    hud_.update();
    action_bar_.update();
}

void Game::drawEditMode()
{
    Rectangle edit_mode_window = centerRectOnScreen(VIRTUAL_HEIGHT / 1.5, VIRTUAL_HEIGHT / 3);
    DrawRectangleRec(edit_mode_window, COLOR_WINDOW_BG);

    // buttons: Discard Changes & Save
    Rectangle centerRec = centerRectInRect(edit_mode_window, VIRTUAL_HEIGHT / 1.5, VIRTUAL_HEIGHT / 3);
    DrawRectangleRec(centerRec, COLOR_WINDOW_BG);
    save_btn_ = {centerRectInRect(edit_mode_window, edit_mode_window.width / 4, edit_mode_window.height / 4), "Save"};
    
    discard_btn_ = save_btn_;
    discard_btn_.label = "Discard";
    // TODO FIX DISCARD, NOT WORKING RN!!
    save_btn_.setBounds({save_btn_.bounds.x - save_btn_.bounds.width, save_btn_.bounds.y});
    discard_btn_.setBounds({save_btn_.bounds.x + save_btn_.bounds.width*2  , save_btn_.bounds.y});
    hud_.drawButton(save_btn_, FONT_SIZE, BLACK, WHITE);
    hud_.drawButton(discard_btn_, FONT_SIZE, BLACK, WHITE);

    DrawRectangleLinesEx(hud_.getPlayerFrame(), 2.0f, COLOR_EDITABLE_COMPONENT);
    DrawRectangleLinesEx(hud_.getTargetFrame(), 2.0f, COLOR_EDITABLE_COMPONENT);
    DrawRectangleLinesEx(action_bar_.getActionBar(), 2.0f, COLOR_EDITABLE_COMPONENT);
}

void Game::endEditMode(bool save)
{
    in_edit_mode = false;

    if (save)
    {
        Settings settings;
        settings.player_frame_config = hud_.getPlayerFrame();
        settings.targeted_frame_config = hud_.getTargetFrame();
        settings.action_bar_config = action_bar_.getActionBar();
        saveSettings(settings, SETTINGS_PATH);
        return;
    }
    hud_.setPlayerFramePos(cached_player_frame_);
    hud_.setTargetFramePos(cached_target_frame_);
    action_bar_.setActionBarPos(cached_action_bar_);
}
