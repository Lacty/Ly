
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


int moving = 0;// ���̏㉺�^��������ϐ�
bool player1 = true;

bool modechange = false;
int blackout = 256;

void drawTitle(AppEnv& app_env, int& MODE, Texture& titlebg, Texture& but){
	// �w�i�F
	// ���[�h�`�F���W���s��ꂽ�Ƃ��w�i�����ɂ���
	if (modechange){ blackout-=2; }
	app_env.bgColor(color256(blackout, blackout, blackout));


	// �w�i�̉摜��\��
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


	// �v���C���[1�C2�����߂�
	// UP��Down�Ń�����������
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

	// MODE�P�Ɉڍs����R�[�h
	if (app_env.isPushKey(GLFW_KEY_ENTER)){
		modechange = true;
	}
	// �w�i�����ɂȂ�����MODE���P�Ɉڍs
	if (blackout <= 1){
		MODE++;
		modechange = false;
		blackout = 256;
	}
}