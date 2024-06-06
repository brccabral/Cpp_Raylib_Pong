#include <raylib.h>

int player_score = 0;
int cpu_score = 0;

Color green = Color{38, 185, 154, 255};
Color darkGreen = Color{20, 160, 133, 255};
Color lightGreen = Color{129, 204, 184, 255};
Color yellow = Color{243, 213, 91, 255};

class Ball
{
public:

    Ball() : x(20), y(20), speed_x(7), speed_y(7), radius(20){};
    float x, y;
    float speed_x, speed_y;
    float radius;
    void Draw() const
    {
        DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, yellow);
    }
    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius < 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth())
        {
            cpu_score++;
            ResetBall();
        }
        if (x - radius < 0)
        {
            player_score++;
            ResetBall();
        }
    }
    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        speed_x *= GetRandomValue(0, 1) * 2 - 1;
        speed_y *= GetRandomValue(0, 1) * 2 - 1;
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
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }
    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }
        LimitMovement();
    }

protected:

    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }
};

Paddle player;

class CpuPaddle : public Paddle
{
public:

    void Update(const int ball_y)
    {
        // cpu follows the ball
        if (y + height / 2 > ball_y)
        {
            y -= speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y += speed;
        }
        LimitMovement();
    }
};

CpuPaddle cpu;

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

    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    while (!WindowShouldClose())
    {
        // Updating
        ball.Update();
        player.Update(); // the inputs are handled in Player.Update
        cpu.Update(ball.y);

        // Checking for collisions
        if (CheckCollisionCircleRec(
                    Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(
                    Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }

        // Drawing
        BeginDrawing();
        ClearBackground(darkGreen);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, green); // right side of field
        DrawCircle(screen_width / 2, screen_height / 2, 150, lightGreen);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

        ball.Draw();
        cpu.Draw();
        player.Draw();

        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
