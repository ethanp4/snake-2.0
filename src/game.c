#include "game.h"
#include "drawing.h"
#include "input.h"
#include "raylib.h"
#include "raymath.h"
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

void initGame() {
  int squares = playAreaLengthUnits*playAreaLengthUnits;

  playField = malloc((sizeof(int*)*playAreaLengthUnits));
  for (int x = 0; x < playAreaLengthUnits; x++) {
    playField[x] = malloc((sizeof(int)*playAreaLengthUnits));
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
  // printf("Made %i food and %i none", foodCount, squares-foodCount);
}

void gameOver() {
  gameOverFlag = true;
}

Vector2 findNearestFood(Vector2 to) {
  // an "orbit" is each consecutive circle around the center  111   22222
  for (int orbit = 0; orbit < 10; orbit++) { //               101   20002
    // check each side of that overall square that is defined 111   20002
    for (int i = 0; i < (orbit*2)+1; i++) { // going clockwise      20002
                                            //                      22222
    }
    for (int i = 0; i < (orbit*2)+1; i++) { 

    }
    for (int i = 0; i < (orbit*2)+1; i++) { 

    }
    for (int i = 0; i < (orbit*2)+1; i++) { 
      
    }
  }
}

void moveBot() {
  
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
  if (botPos.x > playAreaLengthUnits-1) {
    botPos.x = 0;
  }
  if (botPos.x < 0) {
    botPos.x = playAreaLengthUnits-1;
  }
  if (botPos.y > playAreaLengthUnits-1) {
    botPos.y = 0;
  }
  if (botPos.y < 0) {
    botPos.y = playAreaLengthUnits-1;
  }

  for (int i = 0; i < botLength; i++) {
    playField[(int)botPositionHistory[i].x][(int)botPositionHistory[i].y] = PLAYER;
  }
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
  initGame();
  if (playerLength > highScore) { highScore = playerLength; }
  playerLength = 0;
  startTime = GetTime();
  gameOverFlag = false;
}

