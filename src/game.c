#include "game.h"
#include "drawing.h"
#include "input.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

bool gameOverFlag = false;

enum dirs playerMovementDir = UP;
enum dirs botMovementDir = DOWN;
enum mode mode;

int highScore = 0;
int foodCount = 0;
//the GetTime() of when the current life started
float startTime = 0;
float timeElapsed = 0;

Vector2 dirs[4] = { {0,-1}, {0,1}, {-1,0}, {1,0} };

int** playField;

int playerLength = 0;
int botLength = 0;
Vector2 playerPos = {25, 25};
Vector2 botPos = {15, 15};
Vector2 playerPositionHistory[200];
Vector2 botPositionHistory[200];

void initGame(bool restart) {
  int squares = playAreaLengthUnits*playAreaLengthUnits;

  if (!restart) { playField = malloc((sizeof(int*)*playAreaLengthUnits)); }
  for (int x = 0; x < playAreaLengthUnits; x++) {
    if (!restart) { playField[x] = malloc((sizeof(int)*playAreaLengthUnits)); }
    for (int y = 0; y < playAreaLengthUnits; y++) {
      if (GetRandomValue(0, squares) < 10) {
        playField[x][y] = FOOD;
        foodCount++;
      } else {
        playField[x][y] = NONE;
      }
    }
  }
  playerMovementDir = GetRandomValue(0, 3);
  botMovementDir = GetRandomValue(0, 3);
}

void gameOver() {
  gameOverFlag = true;
}

Vector2 wrapVector(Vector2 vec) {
  if (vec.x > playAreaLengthUnits-1) {
    vec.x = 0;
  }
  if (vec.x < 0) {
    vec.x = playAreaLengthUnits-1;
  }
  if (vec.y > playAreaLengthUnits-1) {
    vec.y = 0;
  }
  if (vec.y < 0) {
    vec.y = playAreaLengthUnits-1;
  }
  return vec;
}

//returns input parameter if no food is found
Vector2 findNearestFood(Vector2 to) {
  // an "orbit" is each consecutive ring around the center
  for (int orbit = 1; orbit <= 5; orbit++) {
    Vector2 top_l = { to.x-orbit*2, to.y-orbit };
    for (int i = 0; i < orbit*2+1; i++) { //top row going right
      Vector2 v = { top_l.x+i, top_l.y };
      // v = wrapVector(v);
      if (!Vector2Equals(wrapVector(v), v)) {
        continue;
      }
      if (playField[(int)v.x][(int)v.y] == FOOD) {
        return v;
      }
    }
    for (int i = 0; i < orbit*2+1; i++) { //left column downwards
      Vector2 v = { top_l.x, top_l.y - i};
      // v = wrapVector(v);
      if (!Vector2Equals(wrapVector(v), v)) {
        continue;
      }
      if (playField[(int)v.x][(int)v.y] == FOOD) {
        return v;
      }
    }

    Vector2 bottom_r = { to.x+orbit*2, to.y+orbit };
    for (int i = 0; i < orbit*2+1; i++) { //bottom row going left
      Vector2 v = { bottom_r.x-i, bottom_r.y };
      // v = wrapVector(v);
      if (!Vector2Equals(wrapVector(v), v)) {
        continue;
      }
      if (playField[(int)v.x][(int)v.y] == FOOD) {
        return v;
      }
    }
    for (int i = 0; i < orbit*2+1; i++) { //right column going up
      Vector2 v = { bottom_r.x, bottom_r.y+i};
      // v = wrapVector(v);
      if (!Vector2Equals(wrapVector(v), v)) {
        continue;
      }
      if (playField[(int)v.x][(int)v.y] == FOOD) {
        return v;
      }
    }
  }
  return to;
}

Vector2 nearestFood;
void moveBot(bool updateTarget) {
  //update the target if the food is no longer there or the timer went 
  if (updateTarget || playField[(int)nearestFood.x][(int)nearestFood.y] != FOOD) {
    nearestFood = findNearestFood(botPos);
    if (!Vector2Equals(nearestFood, botPos)) {
      printf("botPos: x: %.0f, y: %.0f\nnearestFood:x: %.0f, y: %.0f\n", botPos.x, botPos.y, nearestFood.x, nearestFood.y);
      // botMovementDir
      if (nearestFood.x > botPos.x) {
        botMovementDir = LEFT;
      } else if (nearestFood.x < botPos.x) {
        botMovementDir = RIGHT;
      } else if (nearestFood.y > botPos.y) {
        botMovementDir = DOWN;
      } else if (nearestFood.y < botPos.y) {
        botMovementDir = UP;
      }
    } 
  }
  //unset old position
  playField[(int)botPos.x][(int)botPos.y] = NONE;
  for (int i = 0; i < botLength; i++) {
    playField[(int)botPositionHistory[i].x][(int)botPositionHistory[i].y] = NONE;
  }

  //update history array
  for (int i = botLength; i > 0; i--) {
    botPositionHistory[i] = botPositionHistory[i-1];
  }
  botPositionHistory[0] = botPos;

  botPos = Vector2Add(botPos, dirs[botMovementDir]);
  botPos = wrapVector(botPos);

  for (int i = 0; i < botLength; i++) {
    playField[(int)botPositionHistory[i].x][(int)botPositionHistory[i].y] = BOT;
  }
  playField[(int)botPos.x][(int)botPos.y] = BOT;
}

void movePlayer() {
  playField[(int)playerPos.x][(int)playerPos.y] = NONE;
  ///unset the collision of the tail before updating it
  for (int i = 0; i < playerLength; i++) {
    playField[(int)playerPositionHistory[i].x][(int)playerPositionHistory[i].y] = NONE;
  }
  //shift the input queue
  if (currentInput != NO_INPUT){
    playerMovementDir = currentInput;
    currentInput = queuedInput;
    queuedInput = NO_INPUT;
  }

  //shift elements over by one to make room for the newest element
  for (int i = playerLength; i > 0; i--) {
    //current element = the element to before it
    playerPositionHistory[i] = playerPositionHistory[i-1]; 
  }
  //set the newest element before adding the movement dir
  playerPositionHistory[0] = playerPos;

  playerPos = Vector2Add(playerPos, dirs[playerMovementDir]);
  if (playerPos.x > playAreaLengthUnits-1) {
    playerPos.x = 0;
  }
  if (playerPos.x < 0) {
    playerPos.x = playAreaLengthUnits-1;
  }
  if (playerPos.y > playAreaLengthUnits-1) {
    playerPos.y = 0;
  }
  if (playerPos.y < 0) {
    playerPos.y = playAreaLengthUnits-1;
  }

  ///set the collision of the tail
  for (int i = 0; i < playerLength; i++) {
  // for (int i = playerLength; i > 0; i--) {
    playField[(int)playerPositionHistory[i].x][(int)playerPositionHistory[i].y] = PLAYER;
  }

  //check the collision
  if (playField[(int)playerPos.x][(int)playerPos.y] == FOOD) {
    playerLength++;
    foodCount--;
  }
  if (playField[(int)playerPos.x][(int)playerPos.y] == PLAYER) {
    gameOver();
  }

  playField[(int)playerPos.x][(int)playerPos.y] = PLAYER;
}

//for spawning food after initalization
void spawnFood() {
  if (foodCount > 15) { return; }
  for (int x = 0; x < playAreaLengthUnits; x++) {
    for (int y = 0; y < playAreaLengthUnits; y++) {
      if (GetRandomValue(0, playAreaLengthUnits*playAreaLengthUnits) < 5) {  //spawn around 5 each time
        if (playField[x][y] != NONE) { continue; }
        playField[x][y] = FOOD;
        foodCount++;
      } 
    }
  }
}

void restartGame() {
  initGame(true);
  if (playerLength > highScore) { highScore = playerLength; }
  playerLength = 0;
  startTime = GetTime();
  gameOverFlag = false;
}

