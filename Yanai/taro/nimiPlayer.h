
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

struct Player{
	int x, y;
	int width, height;
};

Player player{
	0, -280,
	20, 20
};

//	���̂��ړ�������Ƃ��̒l
//	�V�@�\�Ńv���C���[�̈ړ��X�s�[�h���グ�邱�Ƃ����邩������Ȃ��̂�
//	const�͊O���Ă���
int move = 3;

//	�v���C���[�̈ړ�����
void playerMove(AppEnv& app_env){
	if (app_env.isPressKey(GLFW_KEY_RIGHT))player.x += move;	//	�E�Ɉړ�
	if (app_env.isPressKey(GLFW_KEY_LEFT))player.x -= move;	//	���Ɉړ�

	//	��ʊO�Ɉړ����Ȃ��悤�ɐ���
	if (player.x > 500 - player.width)player.x = 500 - player.width;
	if (player.x < -500)player.x = -500;
}

//	�v���C���[�̕`��
void drawPlayer(AppEnv& app_env){

	playerMove(app_env);

	drawFillBox(player.x, player.y, player.width, player.height,
		color256(100, 100, 100));

}