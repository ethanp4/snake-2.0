#include "../include/input.h"
#include "../include/drawing.h"
#include "../include/game.h"
#include <raylib.h>

void handleInput() {
  if (IsKeyPressed(KEY_GRAVE)) { debug = !debug; }

  if (IsKeyPressed(KEY_UP)) { 
    if (movementDir != DOWN ) { movementDir = UP; }
   }
   if (IsKeyPressed(KEY_DOWN)) {
    if (movementDir != UP) { movementDir = DOWN; }
   }
   if (IsKeyPressed(KEY_RIGHT)) {
    if (movementDir != LEFT) { movementDir = RIGHT; }
   }
   if (IsKeyPressed(KEY_LEFT)) {
    if (movementDir != RIGHT) { movementDir = LEFT; }
   }
}