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
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1,
     AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1,
     AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1,
     AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1,
     AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, AIR,
     AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, FT1, AIR, AIR, AIR,
     AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, FT1, FT1, FT1, AIR, AIR, FT1,
     AIR, AIR, FT1, AIR, AIR, FT1, AIR, FT1, FT1, FT1, AIR},
    {FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1,
     FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1},
    {FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1,
     FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1}};

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
  int vram_x = (x * 2) % 32;
  int vram_y = y * 2;

  set_bkg_tile_xy(vram_x, vram_y, tile_index);
  set_bkg_tile_xy((vram_x + 1) % 32, vram_y, tile_index + 1);
  set_bkg_tile_xy(vram_x, vram_y + 1, tile_index + 2);
  set_bkg_tile_xy((vram_x + 1) % 32, vram_y + 1, tile_index + 3);
}

void main(void) {
  int camX = 0;
  int block = 0;
  int oldBlock = 0;

  int speed = 2;

  int px = 16;
  int py = 80;

  int force = 0;

  set_bkg_data(0, 4, floorTile);
  set_bkg_data(4, 4, airTile);
  set_sprite_data(8, 4, playerTile);

  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 11; x++) {
      setBkgTile(map[y][x], x, y);
    }
  }

  for (int i = 0; i < 4; i++) {
    set_sprite_tile(i + 8, i + 8);
  }

  SHOW_SPRITES;
  SHOW_BKG;
  DISPLAY_ON;

  while (1) {
    uint8_t input = joypad();
    block = camX / 16;

    int worldX = px + camX - 8;
    int worldY = py - 16;

    int footY = (worldY + 16) / 16;
    int leftX = worldX / 16;
    int rightX = (worldX + 15) / 16;

    if (map[footY][leftX] == AIR && map[footY][rightX] == AIR) {
      force++;
    } else {
      if (input & J_UP) {
        int worldX = px + camX - 8;
        int worldY = py - 16;

        int nextTopY = (worldY - 3) / 16;
        int leftX = worldX / 16;
        int rightX = (worldX + 15) / 16;

        if (map[nextTopY][leftX] == AIR && map[nextTopY][rightX] == AIR) {
          force = -10;
        }
      } else {
        force = 0;
        py -= py % 16;
      }
    }

    // --- 垂直移動の計算 ---
    py += force; // まず移動させる

    // 上昇中に頭をぶつけたかチェック
    if (force < 0) {
      int checkTopY = (py - 16) / 16; // 移動後の頭上のマップ位置
      if (map[checkTopY][leftX] == FT1 || map[checkTopY][rightX] == FT1) {
        force = 0;                      // 上昇を止める
        py = (checkTopY + 1) * 16 + 16; // 天井にめり込まないよう位置を補正
      }
    }

    if (input & J_RIGHT) {
      int worldX = px + camX - 8;
      int worldY = py - 16;

      int nextRightX = (worldX + 16) / 16;
      int topY = worldY / 16;
      int bottomY = (worldY + 15) / 16;

      if (map[topY][nextRightX] == AIR && map[bottomY][nextRightX] == AIR) {
        int maxCamX = (worldXSize - 10) * 16;
        if (camX >= maxCamX || px < 80) {
          px += speed;
        } else {
          camX += speed;
        }
      }
    }

    if (input & J_LEFT) {
      int worldX = px + camX - 8;
      int worldY = py - 16;

      int nextLeftX = (worldX - 1) / 16;
      int topY = worldY / 16;
      int bottomY = (worldY + 15) / 16;

      if (map[topY][nextLeftX] == AIR && map[bottomY][nextLeftX] == AIR) {
        if (camX == 0 || px > 80) {
          px -= speed;
        } else {
          camX -= speed;
        }
      }
    }

    camX = max(0, camX);
    camX = min((worldXSize - 10) * 16, camX);
    px = max(8, px);
    px = min(152, px);

    if (block != oldBlock) {
      if (block > oldBlock) {
        int newBlockX = block + 10;
        if (newBlockX < 23) {
          for (int y = 0; y < 9; y++) {
            setBkgTile(map[y][newBlockX], newBlockX, y);
          }
        }
      } else {
        int newBlockX = block;
        if (newBlockX >= 0) {
          for (int y = 0; y < 9; y++) {
            setBkgTile(map[y][newBlockX], newBlockX, y);
          }
        }
      }
      oldBlock = block;
    }

    setSpritePos(8, px, py, 2, 2);
    move_bkg(camX, 0);
    wait_vbl_done();
  }
}