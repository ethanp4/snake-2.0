#include "game.h"
#include "raylib.h"
#include <../include/input.h>
#include <../include/drawing.h>

int main() {
  InitWindow(resolution.x, resolution.y, "Snake 2.0");
  SetTargetFPS(60);
  float moveTimer = 0;
  float spawnTimer = 0;
  initGame();

  while (!WindowShouldClose()) {
    //logic before drawing
    handleInput();
    if (!gameOverFlag) {
      timeElapsed = GetTime() - startTime;
      // avoid calling this twice (who knows how long it takes to call)
      float ft = GetFrameTime();
      moveTimer += ft;
      spawnTimer += ft;
      if (moveTimer > 0.20) {
          movePlayer();
          moveTimer = 0;
      }
      if (spawnTimer > 6) {
          spawnFood();
          spawnTimer = 0;
      }
    }
    BeginDrawing();
      drawBackground();
      drawObjects();
      drawText();
    EndDrawing();
  }
  CloseWindow();
}
