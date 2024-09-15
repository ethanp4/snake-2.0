#include "game.h"
#include "raylib.h"
#include <../include/input.h>
#include <../include/drawing.h>

#include <stdlib.h>
#include <time.h>

//numerical constants

int main() {
  InitWindow(resolution.x, resolution.y, "Snake 2.0");
  SetTargetFPS(60);

  initGame();

  while (!WindowShouldClose()) {
    BeginDrawing();
      drawBackground();
      drawText();
      handleInput();
      

    EndDrawing();
  }
  CloseWindow();
}