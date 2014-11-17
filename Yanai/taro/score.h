#pragma once

#include "lib/defines.hpp"
// ������͕K���ŏ���include����

#include "lib/appEnv.hpp"
// ���K�v�ȃw�b�_�t�@�C���͓K���C���N���[�h����

//���L�ϐ��̓ǂݍ���
#include "common.h"

struct Number{
	int x, y;
	int width, height;
};

Number number_main{ -405, 170, 40, 40 };
Number number_mini{ -405, 170, 40, 40 };


void score(int& play_point){

	keta[3] = play_point % 10000;
	keta[3] = keta[3] / 1000;
	keta[2] = play_point % 1000;
	keta[2] = keta[2] / 100;
	keta[1] = play_point % 100;
	keta[1] = keta[1] / 10;
	keta[0] = play_point % 10;
}

void drawScoreWindow(Texture& score_window){
	//�X�R�A�E�B���h�E�̕\��
	drawTextureBox(-500, 70, 256, 256,
		0, 0, 256, 256,
		score_window,
		Color(1, 1, 1));
}

void drawScore(Texture& numb,Number number){

	//�X�R�A�v�Z
	score(player_score);
	//	�~�j�Q�[���̃X�R�A�v�Z
	score(nimiScore);

	for (int i = 0; i < 4; ++i){
		drawTextureBox(number.x - i * 20, number.y, number.width, number.height,
			kiritori[keta[i]], 0, 100, 100,
			numb,
			Color(1, 1, 1));
	}
}