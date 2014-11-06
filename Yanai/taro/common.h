#pragma once

#include "lib/defines.hpp"
// ↑これは必ず最初にincludeする

//プレイヤーサイズ
const int player_size_x = 50, player_size_y = 50;
//ジャンプ力
const int jump_power = 20;
//キャラの移動速度(ドット/1フレーム)
const int player_move_power = 5;
//ジャンプ判定用
static int jump = 0;
//ジャンプ処理用
static float gravity = 0, jump_vy = jump_power;
//床の位置
static int floor_y = 0;
//壁判定用
bool wall_left = 0, wall_right = 0;
//カメラ位置移動用
static double camera_x = 0;
static double camera_y = 0;
//キャラ位置
const double player_x = 0;
static double player_y = 0;

//コンスト定義

const int MAX_MAP_Y = 12;//配列用

const int MAX_MAP_X = 80;//配列用

const int size_x = 50;//Xに対しての大きさ

const int size_y = 50; //Yに対しての大きさ

int object_x, object_y;//オブジェクト表示位置