
#pragma once
#include "lib/appEnv.hpp"
#include "common.h"


// ���@�̕`��
void drawPlayer(Texture& ziki, Player& player){
	drawTextureBox(player.x, player.y, 100, 100,
		0, 0, 256, 256,
		ziki,
		Color(1, 1, 1));
}


// ���@�̈ړ�����
void playerMovement(AppEnv& app_env, Player& player, float& move){
	if (app_env.isPressKey('A')) player.x -= move;
	if (app_env.isPressKey('D')) player.x += move;
	if (player.x <= -WIDTH / 2) player.x = -WIDTH / 2;
	if (player.x >= WIDTH / 2 - 64) player.x = WIDTH / 2 - 64;
}


// �e�̏����i�`��j
void playerShots(AppEnv& app_env, Shot shot_data[], Player& player){
	// �X�y�[�X�L�[�Œe���P����
	if (app_env.isPushKey(GLFW_KEY_SPACE)){
		for (int i = 0; i < SHOT_MAX; ++i) {
			// �z��̒����疢�g�p�f�[�^��T��
			if (!shot_data[i].active) {
				// ���g�p���g�p��
				shot_data[i].active = true;

				// �e�̏����l�͎��@���
				shot_data[i].x = player.x + 32;
				shot_data[i].y = player.y;

				break;
			}
		}
	}


	// �g�p���̒e�𓮂���
	for (int i = 0; i < SHOT_MAX; ++i){
		if (shot_data[i].active) {
			shot_data[i].y += 15;

			// ��ʊO�ɂł��疢�g�p�ɂ���
			if (shot_data[i].y >(HEIGHT / 2)) {
				shot_data[i].active = false;
			}
		}
	}

	// �g�p���̒e��\��
	for (int i = 0; i < SHOT_MAX; ++i){
		if (shot_data[i].active){
			drawFillCircle(shot_data[i].x, shot_data[i].y,
				5, 5,
				10,
				Color(1, 1, 1));
		}
	}
}