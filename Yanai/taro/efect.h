
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"


enum  {
	//	�G�t�F�N�g�̍ő吔���`
	EFECT_MAX = 3
};

//	�G�t�F�N�g�̍\����
struct Efect{
	bool active;			//	�G�t�F�N�g�����̉�������

	float x, y;
	float width, height;

	float movey;			//	Y���F�G�t�F�N�g�̈ړ�
	float move;			//	sin�Ɋ|���Ă������
	int point;			//	X���F�G�t�F�N�g�̏o���ꏊ
	int kakex;			//	���E�ւ̐U�ꕝ
};

//	�G�t�F�N�g��z��ŗp��
Efect efect_data[EFECT_MAX] = {
	{ false, 0, 0, 0, 0, 0, 0, -200, 44, },
	{ false, 0, 0, 0, 0, 0, 10,   0, 50, },
	{ false, 0, 0, 0, 0, 0, 5, 180, 53, },
};

//	�G�t�F�N�g�𓮂����ϐ�
const float EFECT_MOVE = 0.05;
const float EFECT_MOVEY = -0.5;


//	main�̒��ň�x�������s�����Ă܂�
void setupEfect(){

	//	�G�t�F�N�g�̏�����
	//	active�����ׂ�true�ɂ���
	for (int i = 0; i < EFECT_MAX; ++i){
		if (!efect_data[i].active){
			efect_data[i].active = true;
		}
	}

}

//	�G�t�F�N�g�̕`��
void drawEfect(){
	
	/*	��ʊO�ɏo�����̏���
		��ʂ̏�Ɉړ�������	*/
	for (int i = 0; i < EFECT_MAX; ++i){
		if (efect_data[i].y < -300){
			efect_data[i].movey = 300;
		}
	}


	//	�\���ʒu��ύX����Ƃ���
	//	�����R�[�h�ɂȂ��Ă�̂ŁA�킩��Ȃ����������܂�
	//	�������Ď��Ԃ�����Ύ蒼�����܂�
	for (int i = 0; i < EFECT_MAX; ++i){
		efect_data[i].move += EFECT_MOVE;
		efect_data[i].movey += EFECT_MOVEY;
		efect_data[i].x = sin(efect_data[i].move / 2) * efect_data[i].kakex + efect_data[i].point;
		efect_data[i].y = sin(efect_data[i].move) * 10 + efect_data[i].movey;
	}


	//
	//	active��true�̊ԕ\��������
	//
	for (int i = 0; i < EFECT_MAX; ++i){
		if (efect_data[i].active){
			drawPoint(efect_data[i].x, efect_data[i].y, 5, color256(255, 150, 150));
		}
	}
}