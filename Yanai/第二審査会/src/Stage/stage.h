
#pragma once

//
//	�X�e�[�W�I��
//

#include "../common.h"

class Stage{
private:
	//	�\����Stage�̔z��錾
	Object Stage_[5];

	///////////////////////////////////////
	//             ���(�w�i)            //
	//	���(�w�i)�̍ő吔
	enum{
		Yaji_MAX = 20
	};
	//	���(�w�i)�̓����x
	int alpha;
	//	���(�w�i)�̈ړ��X�s�[�h
	int Yaji_MOVE;
	
	//	���(�w�i)�̍\����
	Object Yaji[Yaji_MAX];

	//	���(�w�i)������
	bool Trigger;
	int trigger_count;
	int COUNT;
	/////////////////////////////////////
	/////////////////////////////////////

	bool startStage_;
	int MOVE;

	//	�X�e�[�W�I���֗������̉��o
	void startStage();

	//	�w�i�̉��o
	void backGround();

	//	���Z�b�g�֐�
	void reset();

public:
	Stage();

	void draw(Texture&);
	void update(int&);

};