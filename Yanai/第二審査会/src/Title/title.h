
#pragma once

//
//	�^�C�g�����o
//

#include "../common.h"

class Title{
private:
	//	�\����Start�̔z��錾
	Object Start[5];
	//	���̐؂���ʒu�ύX�p�ϐ�
	int cut_y;
	//	�ړ��p�ϐ�
	int MOVE;

	//	�}�E�X�p�ϐ�
	Vec2f mouse_pos;
	bool isClick;
	float click_posx;
	float click_posy;

	bool modeSwitch;

	//	���Z�b�g�p�֐�
	void reset();
public:
	Title();

	void draw(Texture&);
	void update(int&);

};