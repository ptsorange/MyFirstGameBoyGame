#include "main.h"

// プレイヤーのテクスチャ
const unsigned char playerTile[] = {
    0x1f, 0x1f, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x84, 0x84, 0x84,
    0x84, 0x84, 0x84, 0x84, 0x84, 0xf8, 0xf8, 0x4,  0x4,  0x2,  0x2,
    0x1,  0x1,  0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40,
    0x20, 0x20, 0x1f, 0x1f, 0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
    0x1,  0x1,  0x1,  0x2,  0x2,  0x4,  0x4,  0xf8, 0xf8,
};

// 床のテクスチャ
const unsigned char floorTile[] = {
    0xff, 0x0,  0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff,
    0x7f, 0xff, 0x7f, 0x8f, 0x7f, 0xff, 0x0,  0xff, 0xfe, 0xf9, 0xfe,
    0xe7, 0xfe, 0xcf, 0xfe, 0xbf, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0xe0,
    0x7f, 0xfe, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f,
    0xff, 0x7f, 0xff, 0x0,  0xff, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x3f,
    0xfe, 0xbf, 0xfe, 0xbf, 0xfe, 0xbf, 0xfe, 0xff, 0x0,
};

// 空気のテクスチャ
const unsigned char airTile[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// マップのデータ
const int map[9][23] = {
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR,
     AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR,
     AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, FT1, AIR, FT1, AIR, FT1, FT1, FT1, AIR, FT1, AIR,
     AIR, AIR, FT1, AIR, AIR, AIR, AIR, FT1, AIR, AIR, AIR},
    {AIR, AIR, FT1, AIR, FT1, AIR, FT1, AIR, AIR, AIR, FT1, AIR,
     AIR, AIR, FT1, AIR, AIR, AIR, FT1, AIR, FT1, AIR, AIR},
    {AIR, AIR, FT1, FT1, FT1, AIR, FT1, FT1, FT1, AIR, FT1, AIR,
     AIR, AIR, FT1, AIR, AIR, AIR, FT1, AIR, FT1, AIR, AIR},
    {AIR, AIR, FT1, AIR, FT1, AIR, FT1, AIR, AIR, AIR, FT1, AIR,
     AIR, AIR, FT1, AIR, AIR, AIR, FT1, AIR, FT1, AIR, AIR},
    {AIR, AIR, FT1, AIR, FT1, AIR, FT1, FT1, FT1, AIR, FT1, FT1,
     FT1, AIR, FT1, FT1, FT1, AIR, AIR, FT1, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR,
     AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR,
     AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR}};

void setSpritePos(int sprite, int x, int y, int w, int h) {
  int i = 0;
  for (int w1 = 0; w1 < w; w1++) {
    for (int h1 = 0; h1 < h; h1++) {
      move_sprite(sprite + i, x + (h1 * 8), y + (w1 * 8));
      i++;
    }
  }
}

void setBkgTile(int tile_index, int x, int y) {
  int screen_x = x * 2;
  int screen_y = y * 2;

  set_bkg_tile_xy(screen_x, screen_y, tile_index);
  set_bkg_tile_xy(screen_x + 1, screen_y, tile_index + 1);
  set_bkg_tile_xy(screen_x, screen_y + 1, tile_index + 2);
  set_bkg_tile_xy(screen_x + 1, screen_y + 1, tile_index + 3);
}

void main(void) {
  int camX = 0;
  int block = 0;
  int oldBlock = 0;

  set_bkg_data(0, 4, floorTile);
  set_bkg_data(4, 1, airTile);

  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 11; x++) {
      setBkgTile(map[y][x], x, y);
    }
  }

  SHOW_BKG;
  DISPLAY_ON;

  while (1) {
    uint8_t input = joypad();
    block = (int)(camX / 16);
    if (input & J_LEFT) {
      if (camX > 0)
        camX--;
    }
    if (input & J_RIGHT) {
      if (camX < 208)
        camX++;
    }
    if (oldBlock != block) {
      for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 11; x++) {
          setBkgTile(map[y][x+block], x, y);
        }
      }
      oldBlock = block;
    }
    move_bkg(camX % 16, 0);
    wait_vbl_done();
  }
}