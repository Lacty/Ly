#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"


//	�v���C���[�̍\����
struct Player{
	float x, y;
	float width, height;

	float g;
	float vy;
};

Player player{
	0, 0, 200, 200,
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

	//	��
	{ 0, 512, 128, 128, },
	{ 128, 512, 128, 128 },
	{ 256, 512, 128, 128 }
};

//	�v���C���[�̏d��
void playerG(){
	player.vy += player.g;
	player.y -= player.vy;
}

//	�v���C���[�̈ړ�����
void playerMove(AppEnv& app_env){
	if (app_env.isPressKey('D'))player.x += PLAYER_MOVE;
	if (app_env.isPressKey('A'))player.x -= PLAYER_MOVE;
	if (app_env.isPushKey(GLFW_KEY_SPACE)){
		jump = true;
		player.vy -= 6;
	}
	if (jump)playerG();
}

void jimen(){
	if (player.y <= jimen_y){
		jump = false;
		player.vy = 0;
		player.y = jimen_y;
	}
}

//	�v���C���[�̕`��
void drawPlayer(AppEnv& app_env, Texture& ouzi_image){
	playerMove(app_env);
	jimen();

	if (app_env.isPushKey('D'))Player_Right = true;		//	D����������E��true
	if (app_env.isPushKey('A'))Player_Right = false;		//	A����������E��false

	if (Player_Right){
		if (app_env.isPressKey('D')){
			Kiritori_COUNTER_R++;
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
	else if (app_env.isPressKey('A')){
		Kiritori_COUNTER_R--;
	}

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	//	���[�V�������Ă��镔��
	/////////////////////////////////////////////////////////////////////////////
	if ((Kiritori_COUNTER_R > 0) && (Kiritori_COUNTER_R < 30)){
		if (Player_Right){
			if (!jump){
				Kiritori_MODE = 1;
			} else {
				Kiritori_MODE = 4;
			}
		}
	}
	else if ((Kiritori_COUNTER_R > 31) && (Kiritori_COUNTER_R < 60)){
		if (Player_Right){
			if (!jump){
				Kiritori_MODE = 2;
			} else {
				Kiritori_MODE = 6;
			}
		}
	}
	else if ((Kiritori_COUNTER_R > 61) && (Kiritori_COUNTER_R < 90)){
		if (Player_Right){
			if (!jump){
				Kiritori_MODE = 3;
			} else {
				Kiritori_MODE = 4;
			}
		}
	}
	else if ((Kiritori_COUNTER_R > 91) && (Kiritori_COUNTER_R < 120)){
		if (Player_Right){
			if (!jump){
				Kiritori_MODE = 2;
			} else {
				Kiritori_MODE = 5;
			}
		}
	}
	//	�؂���J�E���g��120��葝������1�ɖ߂�
	if (Kiritori_COUNTER_R > 120){
		Kiritori_COUNTER_R = 1;
	}
	if (Kiritori_COUNTER_R <= -1){
		Kiritori_COUNTER_R = 0;
	}


	drawTextureBox(player.x, player.y,
		player.width, player.height,
		kiritori[Kiritori_MODE].x, kiritori[Kiritori_MODE].y,
		kiritori[Kiritori_MODE].width, kiritori[Kiritori_MODE].height,
		ouzi_image,
		Color(1, 1, 1));
}