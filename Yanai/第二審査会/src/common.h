
#pragma once

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "image.h"


enum Window {
	WIDTH = 800,
	HEIGHT = 450
};

//	�I�u�W�F�N�g�\����
struct Object{
	float x, y;
	float width, height;

	float start_tx;
	float start_ty;

	float texture_width;
	float texture_height;

	Color col;

	bool active;
	bool right;

	float g;		// �d��
	float vy;	// ����

	float speed;	// �ړ��X�s�[�h
};
