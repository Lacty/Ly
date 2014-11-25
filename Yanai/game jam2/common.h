#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "Hit.h"

// game flag
int GameFlag = 0;

//	スコア変数
int play_point = 0;	// 仮にプレイ画面のプレイポイントを保存する変数を作成

// map
float map_x = -512;
float map_y = -340;
float map_width = 5000;
float map_height = 2500;
int box_x = -512;
int box_y = map_y;
const int MAP_MOVE = 4;

float jimen_y = -340; 


// player
bool jump = false;
const int PLAYER_MOVE = 3;

// floaer
const int FLOWER_MAX = 2;

//	画像の切り替え用変数
bool Player_Right = true; 
int Kiritori_MODE = 0;
int Kiritori_COUNTER_R = 0; 
int Kiritori_COUNTER_L = 0; 

//	スコアで使う変数
int keta[3] = {
	0, 0, 0
};
//	画像の切り取り位置
int kiritori[10] = {
	0, 100, 200, 300, 400, 500, 600, 700, 800, 900
};