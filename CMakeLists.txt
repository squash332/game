cmake_minimum_required(VERSION 3.14)

project(
    game
    VERSION 0.1.0
    DESCRIPTION "a game"
    LANGUAGES CXX
)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(json)

add_executable(game_exe
    source/main.cpp
    source/Game.cpp
    
    components/input/InputManager.cpp
    components/entity/Entity.cpp
    components/entity/Player.cpp
    components/entity/Enemy.cpp

    components/map/Map.cpp
    components/camera/Camera.cpp
    
    ui/Renderer.cpp
    ui/Window.cpp
    ui/HUD.cpp
    ui/ActionBar.cpp

    utils/Collision.cpp
    utils/Settings.cpp
    utils/Ability.cpp
)

target_include_directories(game_exe PRIVATE include ui/include utils/include)
target_compile_features(game_exe PRIVATE cxx_std_20)
target_link_libraries(game_exe PRIVATE raylib nlohmann_json::nlohmann_json)
set_property(TARGET game_exe PROPERTY OUTPUT_NAME game)