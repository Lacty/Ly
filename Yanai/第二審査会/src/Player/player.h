
#pragma once

//
//	Player
//

#include "../common.h"

class Player{
private:
	//	�v���C���[�p�摜
	Texture player_image;

	Object player;

	//	�v���C���[�̈ړ�����
	void playerMove();
	//	�v���C���[�̃��[�V�����̃J�E���g
	int tex_count;
	//	�}�E�X�̈ʒu���擾����ϐ�
	Vec2f pos;

	enum {
		//	�e�̍ő吔
		SHOT_MAX = 2
	};
	Object shot[SHOT_MAX];
	//	�v���C���[�̒e��������
	void playerShot();
	
	//	�t�����h�w��
	//	�w�肵���N���X����v���C���[�̒��ɃA�N�Z�X�ł���I
	//	�v���C���[����w���̃N���X�̒��̓A�N�Z�X�ł��Ȃ��I
	friend class Stage_01;
	/*
	�N���X�̒���draw�����w���
	friend void Stage_01::draw;
	*/

public:
	Player();

	void draw();
	void update();

};