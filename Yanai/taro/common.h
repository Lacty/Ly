
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

//	common�ɓ����ϐ�
//	����life�Ƃ��Ă���
int life = 0;

//	�~�j�Q�[���̃^�C���ϐ�
int miniMODE = 0;

//	�{�҂̃X�R�A��ۑ�����ϐ�
int player_score = 0;

//	�~�j�Q�[���Ŋl������X�R�A��ۑ�����ϐ�
int nimiScore = 0;

int keta[6] = {
	//	�X�R�A�̌�
	0, 0, 0, 0, 0, 0
};

int kiritori[10] = {
	//	�����̉摜�̐؂���ʒu
	0, 100, 200, 300, 400, 500, 600, 700, 800, 900
};


/*
	�����蔻�葝��1,2
	�l���|�C���g��{��(1=1�{,2=2�{)
*/
bool PowerWidthUp = false;
bool PowerWidthUp2 = false;
bool PowerPointUp = false;
int PowerPoint = 1;

//	�~�j�Q�[���̊J�n����
bool isReady = false;

int miniTimer = 60*10;