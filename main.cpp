#include <raylib.h>

int main()
{
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Drawing
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        DrawCircle(screen_width / 2, screen_height / 2, 20, WHITE);
        DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
        DrawRectangle(screen_width - 25 - 10, screen_height / 2 - 60, 25, 120, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}