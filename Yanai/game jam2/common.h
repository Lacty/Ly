#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "Hit.h"

// game flag
int GameFlag = 0;

//	�X�R�A�ϐ�
int play_point = 0;	// ���Ƀv���C��ʂ̃v���C�|�C���g��ۑ�����ϐ����쐬

// map
float map_x = -512;
float map_y = -340;
float map_width = 5000;
float map_height = 2500;
int box_x = -512;
int box_y = map_y;
const int MAP_MOVE = 4;

float jimen_y = -340; 


// player
bool jump = false;
const int PLAYER_MOVE = 3;

// floaer
const int FLOWER_MAX = 2;

//	�摜�̐؂�ւ��p�ϐ�
bool Player_Right = true; 
int Kiritori_MODE = 0;
int Kiritori_COUNTER_R = 0; 
int Kiritori_COUNTER_L = 0; 

//	�X�R�A�Ŏg���ϐ�
int keta[3] = {
	0, 0, 0
};
//	�摜�̐؂���ʒu
int kiritori[10] = {
	0, 100, 200, 300, 400, 500, 600, 700, 800, 900
};