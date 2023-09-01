#include "model.cpp"
#include <utility>
#include <raylib.h>
#include <deque>


void drawGrid(int x, int y, int posX, int posY, int width, int height, int margin) {
        Color customblack = {20,20,10,255};
        for(int i = 0; i < x; ++i) {
            for(int j = 0; j < y; ++j) {
                DrawRectangle(posX + i * width - margin, posY +  height * j + margin, width - 2*margin, height - 2 * margin, customblack);
            }
        }
}

void drawApple(pair<int, int> apple, int width, int height, int offX, int offY, int margin) {
    Rectangle rect;
    rect.height = height - 2 * margin;
    rect.width = width - 2 * margin;
    rect.x = offX + apple.first * width - margin;
    rect.y = offY + apple.second * height + margin;
    DrawRectangleRounded(rect, 1, 1, RED);
}   

void drawSnake(deque<pair<int,int>> snake, int width, int height, int offX, int offY, int margin, Color s_color)  {
    Color head_c = {90,160,40,255};
    for(auto i = snake.begin(); i != snake.end(); ++i) {
        Rectangle rect;
        rect.height = height - 2 * margin;
        rect.width = width - 2 * margin;
        rect.x = offX + i->first * width - margin;
        rect.y = offY + i->second * height + margin;
        DrawRectangleRounded(rect, 0.8, 1, s_color);
    }
    Rectangle rect;
    rect.height = height - 2 * margin;
    rect.width = width - 2 * margin;
    rect.x = offX + snake.begin()->first * width - margin;
    rect.y = offY + snake.begin()->second * height + margin;
    DrawRectangleRounded(rect, 0.8, 1, head_c);
}

int main(void) {

    int width = 400 + 800;
    int height = 800;

    InitWindow(width, height, "Snake");

    int grid_x = 20;
    int grid_y = 20;
    SnakeGame sg(grid_x, grid_y);
    
    int block_width = 30;
    int block_height = 30;
    int margin = 3;
    int offX = 400 + 55 + block_width + margin;
    int offY = 55 + block_height + margin;

    Color s_green = {10,150,10,255};
    Color dead_snake = {20,60,20,255};

    float time = 0;
    float move_time = 0.3;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //input
        if(IsKeyPressed(KEY_UP)) {
            sg.change("up");
        }
        if(IsKeyPressed(KEY_RIGHT)) {
            sg.change("right");
        }
        if(IsKeyPressed(KEY_DOWN)) {
            sg.change("down");
        }
        if(IsKeyPressed(KEY_LEFT)) {
            sg.change("left");
        }

        if(IsKeyPressed(KEY_R)) {
            sg = SnakeGame(grid_x, grid_y);
        }
        if(IsKeyPressed(KEY_P)) {
            sg.direction = -1;
        }
        

        //update
        time += GetFrameTime();
        if (time > move_time) {
            sg.update();
            time -= move_time;
        }

        //draw
        BeginDrawing();
        ClearBackground(BLACK);

        drawGrid(grid_x, grid_y, offX, offY, block_width, block_height, margin);
        drawApple(sg.apple, block_width, block_height, offX, offY, margin);
        if (!sg.finished) {
            drawSnake(sg.snake, block_width, block_height, offX, offY, margin, s_green);
        } else {
            drawSnake(sg.snake, block_width, block_height, offX, offY, margin, dead_snake);
        }

        DrawFPS(margin,margin);
        DrawText(TextFormat("Score: %i", sg.score),5,margin+100, 60, WHITE);
        DrawText(TextFormat("Move up: up key"),5,margin+220, 20, WHITE);
        DrawText(TextFormat("Move down: down key"),5,margin+240, 20, WHITE);
        DrawText(TextFormat("Move right: right key"),5,margin+260, 20, WHITE);
        DrawText(TextFormat("Move left: left key"),5,margin+280, 20, WHITE);
        DrawText(TextFormat("Reset game: R key"),5,margin+300, 20, WHITE);
        DrawText(TextFormat("Pause game: P key"),5,margin+320, 20, WHITE);
        

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}