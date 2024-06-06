#include <raylib.h>

class Ball
{
public:

    Ball() : x(20), y(20), speed_x(7), speed_y(7), radius(20){};
    float x, y;
    float speed_x, speed_y;
    float radius;
    void Draw() const
    {
        DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
    }
    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius < 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius < 0)
        {
            speed_x *= -1;
        }
    }
};

Ball ball;

class Paddle
{
public:

    Paddle() : x(10), y(10), width(25), height(120), speed(7){};
    float x, y;
    float width, height;
    float speed;
    void Draw() const
    {
        DrawRectangle(x, y, width, height, WHITE);
    }
    void Update()
    {
        if(IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }
        if(y<=0)
        {y=0;}
        if(y+height>=GetScreenHeight())
        {y=GetScreenHeight()-height;}
    }
};

Paddle player;

int main()
{
    constexpr int screen_width = 1280;
    constexpr int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong");
    SetTargetFPS(60);

    ball.radius = 20.0f;
    ball.x = static_cast<float>(screen_width) / 2.0f;
    ball.y = static_cast<float>(screen_height) / 2.0f;
    ball.speed_x = 7.0f;
    ball.speed_y = 7.0f;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    while (!WindowShouldClose())
    {
        ball.Update();
        player.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        // Drawing
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
        player.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
