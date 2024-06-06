#include <raylib.h>

class Ball
{
public:

    Ball();
    float x, y;
    int speed_x, speed_y;
    float radius;
    void Draw() const
    {
        DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
    }
};

Ball ball;

int main()
{
    constexpr int screen_width = 1280;
    constexpr int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong");
    SetTargetFPS(60);

    ball.radius = 20.0f;
    ball.x = static_cast<float>(screen_width) / 2.0f;
    ball.y = static_cast<float>(screen_height) / 2.0f;
    ball.speed_x = 7;
    ball.speed_y = 7;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Drawing
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
        DrawRectangle(screen_width - 25 - 10, screen_height / 2 - 60, 25, 120, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
