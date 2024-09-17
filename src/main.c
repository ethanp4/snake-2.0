#include "game.h"
#include "raylib.h"
#include <input.h>
#include <drawing.h>

int main() {
  InitWindow(resolution.x, resolution.y, "Snake 2.0");
  SetTargetFPS(60);
  float moveTimer = 0;
  float spawnTimer = 0;
  initGame();
  mode = BOT;

  while (!WindowShouldClose()) {
    //logic before drawing
    handleInput();
    if (!gameOverFlag) {
      timeElapsed = GetTime() - startTime;
      moveTimer += GetFrameTime();
      spawnTimer += GetFrameTime();
      if (moveTimer > 0.20) {
          if (mode == BOT) { moveBot(); }
          movePlayer();
          // checkCollision(); //this will need to be separate if there are two moving players
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
