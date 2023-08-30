#include <raylib.h>

int main(void) {
    InitWindow(800, 450, "basic window");

    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);
        DrawText("Congrats first window", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}