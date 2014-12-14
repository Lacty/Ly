
#pragma once

//
//	�V�X�e��
//

#include "../common.h"
#include "../Title/title.h"
#include "../Stage/stage.h"
#include "../Stage_01/Stage_01.h"
#include "../Player/player.h"
#include "../Result/result.h"

class System{
private:
	//	�V�X�e���p�摜
	Texture system_image;

	Title title;
	Stage stage;
	Stage_01 stage_01;
	Player player;
	Result result;

	//	�V�[���؂�ւ��p�ϐ�
	int MODE;

public:
	System();

	void draw();
	void update();

};
