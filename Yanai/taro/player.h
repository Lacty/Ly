#pragma once

#include "lib/defines.hpp"
// ������͕K���ŏ���include����

#include "lib/appEnv.hpp"
// ���K�v�ȃw�b�_�t�@�C���͓K���C���N���[�h����

//���ʂ̕ϐ��ǂݍ���
#include "common.h"

void player_draw(){

	//�v���C���[�\��
	drawFillBox(player_x, player_y, player_size_x, player_size_y, Color(1, 0.2, 0.2));

}

void player_movement(AppEnv& app_env){

	//�v���C���[����
	//���ɕǂ��Ȃ������L�[�ō���
	if (wall_left == 0){
		if (app_env.isPressKey(GLFW_KEY_LEFT)){
			camera_x += player_move_power;
		}
	}
	//�E�ɕǂ��Ȃ����E�L�[�ŉE��
	if (wall_right == 0){
		if (app_env.isPressKey(GLFW_KEY_RIGHT)){
			camera_x -= player_move_power;
		}
	}
	//�n�ʂɂ���Ƃ��X�y�[�X�ŃW�����v
	if (jump == 0){
		if (app_env.isPushKey(GLFW_KEY_SPACE)){
			jump = 1;
		}
	}

	//�W�����v�̏㏸����
	if (jump == 1){
		jump_vy -= 1;
		player_y += jump_vy;
		//�ō��_�܂œ��B�����痎���ɐ؂�ւ�(jump = 0 ���n�ʂɂ���,jump =1���㏸��,jump = -1 ��������)
		if (jump_vy == 0){
			jump = -1;
			jump_vy = jump_power;
		}
	}
	//��������
	if (jump == -1 || jump == 0){
		gravity += 1;
		player_y -= gravity;
		jump = -1;
	}

}

//���@
void player(){

	//�v���C���[�\��
	player_draw();

	//�v���C���[�̓����֘A
	player_movement(app_env);
	
}
