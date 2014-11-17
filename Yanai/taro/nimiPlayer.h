
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"

struct Player{
	int x, y;
	int width, height;
};

Player player{
	0, -280,
	40, 20
};

//	���̂��ړ�������Ƃ��̒l
//	�V�@�\�Ńv���C���[�̈ړ��X�s�[�h���グ�邱�Ƃ����邩������Ȃ��̂�
//	const�͊O���Ă���
int move = 4;


//	�v���C���[�̈ړ�����
void playerMove(AppEnv& app_env){
	if (app_env.isPressKey('D'))player.x += move;	//	�E�Ɉړ�
	if (app_env.isPressKey('A'))player.x -= move;	//	���Ɉړ�

	//	��ʊO�Ɉړ����Ȃ��悤�ɐ���
	if (player.x > 500 - player.width)player.x = 500 - player.width;
	if (player.x < -500)player.x = -500;
}

//	�p���[�A�b�v����
void powerUp(AppEnv& app_env){

	static int MODE = 0;
	if (MODE == 0){
		if (nimiScore == 15){
			PowerWidthUp = true;
			MODE = 1;
		}
	}
	if (MODE == 1){
		if (nimiScore == 50){
			PowerPointUp = true;
			MODE = 2;
		}
	}
	if (MODE == 2){
		if (nimiScore == 60){
			PowerWidthUp2 = true;
			MODE = 3;
		}
	}

	//	�p���[�A�b�v���ł����Ԃ�P��������
	//	�I���E����͈͂��g�傷��
	if (PowerWidthUp){
		if (app_env.isPressKey('P')){
			app_env.flushInput();
			player.width = player.width + 20;

			PowerWidthUp = false;
		}
	}
	if (PowerWidthUp2){
		if (app_env.isPushKey('P')){
			app_env.flushInput();
			player.width = player.width + 40;

			PowerWidthUp2 = false;
		}
	}

	//	�l���ł���|�C���g������
	//	���̊֐��Q��
	if (PowerPointUp){
		if (app_env.isPushKey('O')){
			app_env.flushInput();
			PowerPoint = 2;
			PowerPointUp = false;
		}
	}
}

//	�l������|�C���g�𑝉�������֐�
void powerPointUp(){
	static int count = 0;

	if (PowerPoint == 2){
		count++;
		if (count >= 600){
			PowerPoint = 1;
			count = 0;
		}
	}
}

//	�v���C���[�̕`��
void drawPlayer(AppEnv& app_env){

	/*
		�v���C���[�̈ړ�����
		�I���E�������蔻��̑���
		�l���ł���|�C���g����莞�ԑ���
	*/
	if (isReady){
		playerMove(app_env);
		powerUp(app_env);
		powerPointUp();
	}
	drawFillBox(player.x, player.y, player.width, player.height,
		color256(100, 100, 100));

}