#include <raylib.h>
#include <iostream>

int main() {
    std::cout << "Hello" << std::endl;
    InitWindow(800, 600, "title");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(SKYBLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}