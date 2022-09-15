#pragma once

typedef enum GAME_STATE
{
    PLAY_STATE,
    GAME_OVER_STATE
} GAME_STATE;

typedef enum PLAYER_STATE
{
    IDLE
} PLAYER_STATE;

enum AssetID
{
    MAIN_FONT = 0,
    WALL,
    NINJA,
    ATTACK
};
