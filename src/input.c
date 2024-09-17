#include "input.h"
#include "drawing.h"
#include "game.h"
#include <raylib.h>

//this is to allow queuing one input, and preventing the player from changing the direction twice 
//before the game has actually moved the snake

//if current input isnt set -> set currentInput
//if it is set and queuedInput isnt -> set queuedInput
//if theyre both set -> ignore the input
enum dirs currentInput = NO_INPUT;
enum dirs queuedInput = NO_INPUT;

void handleInput() {
  if (IsKeyPressed(KEY_GRAVE)) { debug = !debug; }
  if (IsKeyPressed(KEY_BACKSPACE)) { gameOverFlag = true; }
  if (IsKeyPressed(KEY_SPACE) && gameOverFlag) { restartGame(); }

  if (currentInput == NO_INPUT){
    if (IsKeyPressed(KEY_UP)) { 
      if (movementDir != DOWN ) { currentInput = UP; }
    }
    if (IsKeyPressed(KEY_DOWN)) {
      if (movementDir != UP) { currentInput = DOWN; }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      if (movementDir != LEFT) { currentInput = RIGHT; }
    }
    if (IsKeyPressed(KEY_LEFT)) {
      if (movementDir != RIGHT) { currentInput = LEFT; }
    }
  } else if (queuedInput == NO_INPUT) {
    if (IsKeyPressed(KEY_UP)) { 
      if (currentInput != DOWN ) { queuedInput = UP; }
    }
    if (IsKeyPressed(KEY_DOWN)) {
      if (currentInput != UP) { queuedInput = DOWN; }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      if (currentInput != LEFT) { queuedInput = RIGHT; }
    }
    if (IsKeyPressed(KEY_LEFT)) {
      if (currentInput != RIGHT) { queuedInput = LEFT; }
    }
  }
}