#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"


//	プレイヤーの構造体
struct Player{
	float x, y;
	float width, height;

	float g;
	float vy;
};

Player player{
	px, py, 200, 200,
	0.2, 0
};

struct Kiritori{
	int x, y;
	int width, height;
};

Kiritori kiritori[]{
		{ 0, 0, 128, 128 },
		{ 0, 128, 128, 128 },
		{ 128, 128, 128, 128 },
		{ 256, 128, 128, 128 },

		//	空中
		{ 0, 512, 128, 128, },
		{ 128, 512, 128, 128 },
		{ 256, 512, 128, 128 },

		//	左向き（歩き
		{ 0, 1152, 128, 128 },
		{ 128, 1152, 128, 128 },
		{ 256, 1152, 128, 128 },
		//	棒立ち
		{ 0, 1027, 128, 128 }
};

//	プレイヤーの重力
void playerG(){
	player.vy += player.g;
	player.y -= player.vy;
}

//	プレイヤーの移動制御
void playerMove(AppEnv& app_env){
	if (app_env.isPressKey('D'))player.x += PLAYER_MOVE;
	if (app_env.isPressKey('A'))player.x -= PLAYER_MOVE;
	if (box_y + map_height < player.y + player.height) {
		player.vy += 0.4;
	}
	if (app_env.isPressKey(GLFW_KEY_SPACE)){
		jump = true;
		player.vy -= 0.4;
	}
	if (app_env.isPushKey(GLFW_KEY_SPACE)){
		jump = true;
		player.vy -= 2;
	}
	if (jump)playerG();
}

void jimen(){
	// 上空でプレイヤーがある程度（ｙ軸-200）下がったら、背景画像を動かす
	if (player.y <= -190){
		box_y += map_move_y1;
	}
	
	// マップ外に出るのを制御①（マップの下にめり込んだ時の対処）
	if (player.y <= jimen_y){//map_y){
		jump = false;
		player.vy = 0;
		player.y = jimen_y;//map_y;
	}

	// マップ外に出るのを制御②（背景画像の下限がない場合 かつ プレイヤーが地面にちかづいたとき）
	if ((box_y == map_y) && (player.y <= box_y + 10)){
		jump = false;
		player.vy = 0;
		player.y = -340;
	}
}

//	プレイヤーの描画
void drawPlayer(AppEnv& app_env, Texture& ouzi_image){
	playerMove(app_env);
	jimen();

	if (app_env.isPushKey('D'))Player_Right = true;		//	Dを押したら右をtrue
	if (app_env.isPushKey('A'))Player_Right = false;		//	Aを押したら右をfalse

	if (Player_Right){
		if (app_env.isPressKey('D')){
			Kiritori_COUNTER_R++;
			Kiritori_COUNTER_L--;
		}
		if (app_env.isPullKey('D')){
			Kiritori_COUNTER_R = 0;
		}
		if (Kiritori_COUNTER_R == 0){
			if (!jump){
				Kiritori_MODE = 0;
			}
			else {
				Kiritori_MODE = 4;
			}
		}
	}
	else if (!Player_Right){
		if (app_env.isPressKey('A')){
			Kiritori_COUNTER_L++;
			Kiritori_COUNTER_R--;
		}
		if (app_env.isPullKey('A')){
			Kiritori_COUNTER_L = 0;
		}
		if (Kiritori_COUNTER_L == 0){
			if (!jump){
				Kiritori_MODE = 10;
			}
			else {
				Kiritori_MODE = 4;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	//	モーションしている部分 右向きの画像
	/////////////////////////////////////////////////////////////////////////////
	if ((Kiritori_COUNTER_R > 0) && (Kiritori_COUNTER_R < 30)){
		if (!jump){
			Kiritori_MODE = 1;
		}
		else {
			Kiritori_MODE = 5;
		}
	}
	else if ((Kiritori_COUNTER_R > 31) && (Kiritori_COUNTER_R < 60)){
		if (!jump){
			Kiritori_MODE = 2;
		}
		else {
			Kiritori_MODE = 5;
		}
	}
	else if ((Kiritori_COUNTER_R > 61) && (Kiritori_COUNTER_R < 90)){
		if (!jump){
			Kiritori_MODE = 3;
		}
		else {
			Kiritori_MODE = 5;
		}
	}
	else if ((Kiritori_COUNTER_R > 91) && (Kiritori_COUNTER_R < 120)){
		if (!jump){
			Kiritori_MODE = 2;
		}
		else {
			Kiritori_MODE = 5;
		}
	}

	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	//	モーションしている部分 左向き
	/////////////////////////////////////////////////////////////////////
	if ((Kiritori_COUNTER_L > 0) && (Kiritori_COUNTER_L < 30)){
		if (!Player_Right){
			if (!jump){
				Kiritori_MODE = 7;
			}
			else {
				Kiritori_MODE = 6;
			}
		}
	}
	else if ((Kiritori_COUNTER_L > 31) && (Kiritori_COUNTER_L < 60)){
		if (!Player_Right){
			if (!jump){
				Kiritori_MODE = 8;
			}
			else {
				Kiritori_MODE = 6;
			}
		}
	}
	else if ((Kiritori_COUNTER_L > 61) && (Kiritori_COUNTER_L < 90)){
		if (!Player_Right){
			if (!jump){
				Kiritori_MODE = 9;
			}
			else {
				Kiritori_MODE = 6;
			}
		}
	}
	else if ((Kiritori_COUNTER_L > 91) && (Kiritori_COUNTER_L < 120)){
		if (!Player_Right){
			if (!jump){
				Kiritori_MODE = 8;
			}
			else {
				Kiritori_MODE = 6;
			}
		}
	}


	//	切り取りカウントが120より増えたら1に戻す
	if (Kiritori_COUNTER_R > 120){
		Kiritori_COUNTER_R = 1;
	}
	if (Kiritori_COUNTER_R <= -1){
		Kiritori_COUNTER_R = 0;
	}
	if (Kiritori_COUNTER_L > 120){
		Kiritori_COUNTER_L = 1;
	}
	if (Kiritori_COUNTER_L <= -1){
		Kiritori_COUNTER_L = 0;
	}


	drawTextureBox(player.x, player.y,
		player.width, player.height,
		kiritori[Kiritori_MODE].x, kiritori[Kiritori_MODE].y,
		kiritori[Kiritori_MODE].width, kiritori[Kiritori_MODE].height,
		ouzi_image,
		Color(1, 1, 1));
}