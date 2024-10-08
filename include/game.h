#ifndef GAME_H
#define GAME_H
#include <raylib.h>

enum objects{ NONE, PLAYER, FOOD, BOT };
enum dirs { UP, DOWN, LEFT, RIGHT, NO_INPUT };
enum gameover_type { PLAYER_HIT_SELF, PLAYER_HIT_BOT, BOT_HIT_SELF, BOT_HIT_PLAYER };
extern Vector2 dirs[4];

enum mode { SINGLE_PLAYER, BOT_MODE, TWO_PLAYER };
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
extern bool botInfo; // console info
extern Vector2 playerPos;
extern Vector2 botPos;

extern Vector2 playerPositionHistory[200]; //i cant make this dynamically allocated
extern Vector2 botPositionHistory[200];
extern int** playField;

void movePlayer();
void moveBot(bool updateTarget);
void initGame(bool restart);
void spawnFood();
void restartGame();

#endif
