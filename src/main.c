#include "game.h"
#include "raylib.h"
#include <../include/input.h>
#include <../include/drawing.h>

int main() {
  InitWindow(resolution.x, resolution.y, "Snake 2.0");
  SetTargetFPS(60);
  float moveTimer = 0;
  initGame();

  while (!WindowShouldClose()) {
    handleInput();
    BeginDrawing();
      drawBackground();
      drawText();

      moveTimer += GetFrameTime();
      if (moveTimer > 0.25) {
        movePlayer();
        moveTimer = 0;
      }

      drawObjects();

    EndDrawing();
  }
  CloseWindow();
}
