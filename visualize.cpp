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
    for(auto i = snake.begin(); i != snake.end(); ++i) {
        Rectangle rect;
        rect.height = height - 2 * margin;
        rect.width = width - 2 * margin;
        rect.x = offX + i->first * width - margin;
        rect.y = offY + i->second * height + margin;
        DrawRectangleRounded(rect, 0.8, 1, s_color);
    }
}

int main(void) {

    int width = 400 + 800;
    int height = 800;

    InitWindow(width, height, "Snake");

    int grid_x = 8;
    int grid_y = 8;
    SnakeGame sg(grid_x, grid_y);
    
    int block_width = 100;
    int block_height = 100;
    int margin = 5;
    int offX = 400;
    int offY = 0;

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
        DrawText(TextFormat("Score: %i", sg.score),margin,margin+100, 20, RED);
        
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}