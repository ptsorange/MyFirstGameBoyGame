#pragma once
#include <gb/gb.h>
#include <stdint.h>

// ワールド、スクリーンの大きさ
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 9
#define TILE_SIZE 8
#define BLOCK_SIZE 16

#define SCREEN_BLOCK_WIDTH 11
#define SCREEN_CENTER_X 80
#define PLAYER_MAX_X 152
#define PLAYER_MIN_X 8

// タイルのnum
#define FT1 0
#define AIR 4
#define TILE_PLAYER 8
#define SPK 12

// 物理
#define GRAVITY_MAX 4
#define JUMP_FORCE -10
#define PLAYER_SPEED 2
#define PLAYER_START_X 16
#define PLAYER_START_Y 80
#define DEATH_Y 160

// Min/Max のマクロ
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

void setSpritePos(int sprite, int x, int y, int w, int h);
void setBkgTile(int tile_index, int x, int y);
void resetGame(int *px, int *py, int *camX, int *force, int *oldBlock);

extern const unsigned char playerTile[];
extern const unsigned char floorTile[];
extern const unsigned char airTile[];
extern const unsigned char spikeTile[];
extern const int map[WORLD_HEIGHT][WORLD_WIDTH];