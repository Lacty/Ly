#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "Hit.h"

// game flag
int GameFlag = 0;

// map
float map_x = -512;
float map_y = -340;
float map_width = 5000;
float map_height = 2500;
float map_move_x1 = 2.5;
float map_move_x2 = 5;
float map_move_y1 = 6;
float map_move_y2 = 6;
float jimen_y = -190;
int box_x = -512;
int box_y = map_y;


// map hit





// player
int px = -300;
int py = -190;
int Kiritori_MODE = 0;
int Kiritori_COUNTER_L = 0;
int Kiritori_COUNTER_R = 0;
bool jump = false;
bool Player_Right = true;
const int PLAYER_MOVE = 3;

// floaer
const int FLOWER_MAX = 10;

// umbrella
const int KASA_X = -512;
const int KASA_Y = 240;
const int KASA_SIZE = 100;

// prologue fanction
int bg_x1 = -512;
int bg_x2 = (bg_x1 + 150 + 100);
int bg_x3 = (bg_x2 + 1000);
int bg_y1 = -190;
int bg_y3 = -90;
int bg_MovePoint = -100;
int bg_width = 5000;
int bg_height = 2500;
float p_time = 10 * 60;
int prolog_time = 10 * 60;
float prolog_rect_alpha = 0;
bool prologFlag = true;

//ˆÃ“]—p‚Ìbool
bool iswhite = false;

// score
int play_point = 0;
int keta[3] = { 0, 0, 0 };
int kiritori_score[10] = {
	0, 100, 200, 300, 400, 500, 600, 700, 800, 900
};
