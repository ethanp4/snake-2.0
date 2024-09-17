#include "game.h"
#include "drawing.h"
#include "input.h"
#include "raylib.h"
#include "raymath.h"

bool gameOverFlag = false;

int playerLength = 0;
int highScore = 0;
int foodCount = 0;
//the GetTime() of when the current life started
float startTime = 0;
float timeElapsed = 0;

Vector2 dirs[4] = { {0,-1}, {0,1}, {-1,0}, {1,0} };
enum dirs movementDir = UP; //might change this

//using local coordinates
//(playAreaLengthUnits)
Vector2 playerPos = {20,20};

int playField[40][40];
Vector2 positionHistory[200];

void initGame() {
  int squares = playAreaLengthUnits*playAreaLengthUnits;
  // realloc dimension x
  // playField = realloc(playField, sizeof(int)*playAreaLengthUnits);

  //malloc each row (dimension y)
  for (int x = 0; x < playAreaLengthUnits; x++) {
    // playField[x] = (int*)malloc(sizeof(int)*playAreaLengthUnits);

    //initialize the array
    for (int y = 0; y < playAreaLengthUnits; y++) {
      if (GetRandomValue(0, squares) < 10) { // shoot for 10
        playField[x][y] = FOOD;
        foodCount++;
      } else {
        playField[x][y] = NONE;
      }
    }
  }
  movementDir = GetRandomValue(0, 3);
  // printf("Made %i food and %i none", foodCount, squares-foodCount);
}

void gameOver() {
  gameOverFlag = true;
}

void movePlayer() {
  playField[(int)playerPos.x][(int)playerPos.y] = NONE;
  ///unset the collision of the tail before updating it
  for (int i = 0; i < playerLength; i++) {
    playField[(int)positionHistory[i].x][(int)positionHistory[i].y] = NONE;
  }
  //shift the input queue
  if (currentInput != NO_INPUT){
    movementDir = currentInput;
    currentInput = queuedInput;
    queuedInput = NO_INPUT;
  }

  //shift elements over by one to make room for the newest element
  for (int i = playerLength; i > 0; i--) {
    //current element = the element to before it
    positionHistory[i] = positionHistory[i-1]; 
  }
  //set the newest element before adding the movement dir
  positionHistory[0] = playerPos;

  playerPos = Vector2Add(playerPos, dirs[movementDir]);
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
    playField[(int)positionHistory[i].x][(int)positionHistory[i].y] = PLAYER;
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