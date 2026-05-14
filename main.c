#include "main.h"

// スクリプトの位置をセット
void setSpritePos(int sprite, int x, int y, int w, int h) {
  int i = 0;
  for (int w1 = 0; w1 < w; w1++) {
    for (int h1 = 0; h1 < h; h1++) {
      move_sprite(sprite + i, x + (h1 * TILE_SIZE), y + (w1 * TILE_SIZE));
      i++;
    }
  }
}

// タイルの位置をセット
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

  int px = PLAYER_START_X;
  int py = PLAYER_START_Y;
  int force = 0;

  set_bkg_data(FT1, 4, floorTile);
  set_bkg_data(AIR, 4, airTile);
  set_sprite_data(TILE_PLAYER, 4, playerTile);

  for (int y = 0; y < WORLD_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_BLOCK_WIDTH; x++) {
      setBkgTile(map[y][x], x, y);
    }
  }

  for (int i = 0; i < 4; i++) {
    set_sprite_tile(i + TILE_PLAYER, i + TILE_PLAYER);
  }

  SHOW_SPRITES;
  SHOW_BKG;
  DISPLAY_ON;

  while (1) {
    uint8_t input = joypad();
    block = camX / BLOCK_SIZE;

    int worldX = px + camX - TILE_SIZE;
    int worldY = py - BLOCK_SIZE;

    int footY = (worldY + BLOCK_SIZE) / BLOCK_SIZE;
    int leftX = worldX / BLOCK_SIZE;
    int rightX = (worldX + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // 重力とジャンプ
    if (map[footY][leftX] == AIR && map[footY][rightX] == AIR) {
      if (force < GRAVITY_MAX)
        force++;
    }
    py += force;

    worldY = py - BLOCK_SIZE;
    int newFootY = (worldY + BLOCK_SIZE) / BLOCK_SIZE;
    if (map[newFootY][leftX] == FT1 || map[newFootY][rightX] == FT1) {
      if (force > 0) {
        force = 0;
        py = newFootY * BLOCK_SIZE;
      }

      if (input & J_UP) {
        int nextTopY = (worldY - 3) / BLOCK_SIZE;
        if (map[nextTopY][leftX] == AIR && map[nextTopY][rightX] == AIR) {
          force = JUMP_FORCE;
        }
      }
    }

    if (force < 0) {
      int checkTopY = (py - BLOCK_SIZE) / BLOCK_SIZE;
      if (map[checkTopY][leftX] == FT1 || map[checkTopY][rightX] == FT1) {
        force = 0;
        py = (checkTopY + 1) * BLOCK_SIZE + BLOCK_SIZE;
      }
    }

    py += force;

    // 天井の当たり判定
    if (force < 0) {
      int checkTopY = (py - BLOCK_SIZE) / BLOCK_SIZE;
      if (map[checkTopY][leftX] == FT1 || map[checkTopY][rightX] == FT1) {
        force = 0;
        py = (checkTopY + 1) * BLOCK_SIZE + BLOCK_SIZE;
      }
    }

    // 右
    if (input & J_RIGHT) {
      int nextRightX = (worldX + BLOCK_SIZE) / BLOCK_SIZE;
      int topY = worldY / BLOCK_SIZE;
      int bottomY = (worldY + BLOCK_SIZE - 1) / BLOCK_SIZE;

      if (map[topY][nextRightX] == AIR && map[bottomY][nextRightX] == AIR) {
        int maxCamX = (WORLD_WIDTH - (SCREEN_WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
        if (camX >= maxCamX || px < SCREEN_CENTER_X) {
          px += PLAYER_SPEED;
        } else {
          camX += PLAYER_SPEED;
        }
      }
    }

    // 左
    if (input & J_LEFT) {
      int nextLeftX = (worldX - 1) / BLOCK_SIZE;
      int topY = worldY / BLOCK_SIZE;
      int bottomY = (worldY + BLOCK_SIZE - 1) / BLOCK_SIZE;

      if (map[topY][nextLeftX] == AIR && map[bottomY][nextLeftX] == AIR) {
        if (camX == 0 || px > SCREEN_CENTER_X) {
          px -= PLAYER_SPEED;
        } else {
          camX -= PLAYER_SPEED;
        }
      }
    }

    camX = max(0, camX);
    camX = min((WORLD_WIDTH - (SCREEN_WIDTH / BLOCK_SIZE)) * BLOCK_SIZE, camX);
    px = max(PLAYER_MIN_X, px);
    px = min(PLAYER_MAX_X, px);

    // 背景
    if (block != oldBlock) {
      int newBlockX =
          (block > oldBlock) ? block + (SCREEN_WIDTH / BLOCK_SIZE) : block;
      if (newBlockX >= 0 && newBlockX < WORLD_WIDTH) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
          setBkgTile(map[y][newBlockX], newBlockX, y);
        }
      }
      oldBlock = block;
    }

    setSpritePos(TILE_PLAYER, px, py, 2, 2);
    move_bkg(camX, 0);
    wait_vbl_done();
  }
}
