#pragma once
#include <gb/gb.h>

#define AIR 4
#define FT1 0

#define gameboyW 144
#define gameboyH 160

#define worldXSize 23
#define worldXSizeP worldXSize*16

// min/max の定義を追加
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
/*
const int map[9][23] = {
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, AIR, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, AIR, FT1, FT1, AIR, AIR, AIR, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR},
    {AIR, AIR, AIR, AIR, AIR, AIR, FT1, FT1, FT1, AIR, AIR, FT1, AIR, AIR, FT1, AIR, AIR, FT1, AIR, FT1, FT1, FT1, AIR},
    {FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1},
    {FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1, FT1}};
*/