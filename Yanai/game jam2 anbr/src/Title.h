#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"

int yaji_x = -280;
int yaji_y = -155;
bool yajiUp = true;
bool drawYaji = true;
int time = 0;

void TitleDraw(AppEnv& app_env, Texture& title_bg){
	//	背景
	drawTextureBox(-512, -340, 1024, 680,
		0, 0, 1024, 680,
		title_bg,
		Color(1, 1, 1));
	//	タイトル
	drawTextureBox(-310, 40, 620, 157,
		0, 681, 620, 157,
		title_bg,
		Color(1, 1, 1));
	//	もくじ
	drawTextureBox(-100, -60, 230, 100,
		620, 681, 230, 100,
		title_bg,
		Color(1, 1, 1));
	//	プロローグ
	drawTextureBox(-115, -155, 230, 100,
		620, 780, 230, 100,
		title_bg,
		Color(1, 1, 1));
	//	本編
	drawTextureBox(-115, -220, 200, 100,
		830, 681, 200, 100,
		title_bg,
		Color(1, 1, 1));
	//	Enterで決定
	drawTextureBox(-230, -300, 500, 100,
		0, 870, 500, 100,
		title_bg,
		Color(1, 1, 1));


	//	矢印の移動
	if (app_env.isPushKey('W')){
		yajiUp = true;
	}
	if (app_env.isPushKey('S')){
		yajiUp = false;
	}
	if (yajiUp){
		yaji_x = -270;
		yaji_y = -155;
	}
	else{
		yaji_x = -220;
		yaji_y = -230;
	}


	time++;
	if ((time > 0) && (time < 30)){
		drawYaji = true;
	}
	if ((time >= 30) && (time < 60))drawYaji = false;
	if (time >= 60){
		time = 0;
	}
	drawTextureBox(yaji_x, yaji_y, 150, 100,
		840, 780, 150, 100,
		title_bg,
		Color(1, 1, 1));


	if (yajiUp){
		if (app_env.isPushKey(GLFW_KEY_ENTER)) GameFlag = 1;
	}
	else if (app_env.isPushKey(GLFW_KEY_ENTER)) GameFlag = 2;
};