#include "raylib.h"

int main(void) {
  InitWindow(800, 450, "raylib [core] example - basic window");

  Image image = LoadImage("assets/texture.png");
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Raylib is cool!", 190, 200, 20,
             LIGHTGRAY);
    DrawTexture(texture, 10, 10, WHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
