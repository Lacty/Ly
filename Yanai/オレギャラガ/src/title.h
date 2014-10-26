
#pragma once
#include "lib/appEnv.hpp"

struct Button{
	int x, y;
	int width, height;
	int move;
};

Button button{
	-140, -158,
	40, 40,
	37
};


int moving = 0;// Ωの上下運動させる変数
bool player1 = true;

bool modechange = false;
int blackout = 256;

void drawTitle(AppEnv& app_env, int& MODE, Texture& titlebg, Texture& but){
	// 背景色
	// モードチェンジが行われたとき背景を黒にする
	if (modechange){ blackout-=2; }
	app_env.bgColor(color256(blackout, blackout, blackout));


	// 背景の画像を表示
	drawTextureBox(-380, -430, 800, 800,
		0, 0, 512, 512,
		titlebg,
		Color(1, 1, 1));

	moving++;
	if (moving == 100)moving = 0;
	drawTextureBox(button.x, sin(moving/2)*2 + button.y, button.width, button.height,
		0, 0, 32, 32,
		but,
		Color(1, 1, 1));


	// プレイヤー1，2を決める
	// UPとDownでΩをうごかす
	if (!modechange){
		if (player1){
			if (app_env.isPushKey(GLFW_KEY_DOWN)){
				button.y -= button.move;
				player1 = false;
			}
		}
		else if (app_env.isPushKey(GLFW_KEY_UP)){
			button.y += button.move;
			player1 = true;
		}
	}
	else if (!player1){
		if (button.y < (-158)){
			button.y++;
		}
	}

	// MODE１に移行するコード
	if (app_env.isPushKey(GLFW_KEY_ENTER)){
		modechange = true;
	}
	// 背景が黒になったらMODEを１に移行
	if (blackout <= 1){
		MODE++;
		modechange = false;
		blackout = 256;
	}
}