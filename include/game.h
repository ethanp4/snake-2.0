#ifndef GAME_H
#define GAME_H
#include <raylib.h>

enum objects{ NONE, PLAYER, FOOD };
enum dirs { UP, DOWN, LEFT, RIGHT, NO_INPUT };
extern Vector2 dirs[4];

enum mode { SINGLE_PLAYER, BOT, TWO_PLAYER };
extern enum mode mode;

extern enum dirs playerMovementDir;
extern enum dirs botMovementDir;

extern float startTime;
extern float timeElapsed;
extern int highScore;

extern int playerLength;
extern int botLength;
extern int foodCount;
extern bool gameOverFlag;
extern Vector2 playerPos;
extern Vector2 botPos;

extern Vector2 playerPositionHistory[200]; //i cant make this dynamically allocated
extern Vector2 botPositionHistory[200];
extern int playField[40][40]; //allocated on init

void movePlayer();
void moveBot();
void initGame();
void spawnFood();
void restartGame();

#endif
