
#pragma once
#include "lib/appEnv.hpp"



// �A�v���̃E�C���h�E�T�C�Y
enum Window {
	WIDTH = 650,
	HEIGHT = 850
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

// �e��
int MAX_SHOT;                    // ��������
int MAX_HIT;                    // ����������
int MAX_MISS = MAX_SHOT - MAX_HIT;     // �O������


// �w�i�̕`��
void backGround(int& scroll, Texture& bg){

	scroll -= 3;

	drawTextureBox(-325, -425, 650, 850,
		0, scroll, 650, 850,
		bg,
		Color(1, 1, 1));
}