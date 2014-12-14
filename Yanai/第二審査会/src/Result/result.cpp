//
//	���U���g���
//

#include "result.h"
#include "../App.h"


//	�R���X�g���N�^
Result::Result(){
	result_image = (Texture(RESULT_IMAGE));
}

//	���U���g�̕`��
void Result::draw(){
	drawTextureBox(-100, -100, 200, 200,
		0, 0, 200, 200,
		result_image,
		color256(200, 100, 200));
}

//	���U���g�̏���
void Result::update(int& MODE){
	if (App::app_env->isPushKey(GLFW_KEY_ENTER)){
		MODE = 1;
	}
}