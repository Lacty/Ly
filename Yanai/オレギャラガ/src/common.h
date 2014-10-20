
#pragma once
#include "lib/appEnv.hpp"



// �A�v���̃E�C���h�E�T�C�Y
enum Window {
	WIDTH = 650,
	HEIGHT = 850
};

// �v���C���[�̍\����
struct Player{
	float x, y;
};

// �v���C���[�̃I�u�W�F�N�g���쐬
Player player = {
	-32, -410
};

// �G�l�~�[�̍\����
struct Enemy{
	float x, y;
	float width, height;
	bool isHit;
};


// �G�l�~�[�̃I�u�W�F�N�g���쐬
Enemy enemy[4] = {
	30, 300, 40, 40, false,
	-70, 300, 40, 40, false,
	60, 200, 40, 40, false,
	-100, 200, 40, 40, false,
};


// �ő�e�����`
enum  {
	SHOT_MAX = 2
};


// �e�̒�`
struct Shot{
	float x, y;
	bool active;
};

// �e��z��ŗp��
Shot shot_data[SHOT_MAX];


// �w�i�̕`��
void backGround(int& scroll, Texture& bg){

	scroll -= 3;

	drawTextureBox(-325, -425, 650, 850,
		0, scroll, 650, 850,
		bg,
		Color(1, 1, 1));
}