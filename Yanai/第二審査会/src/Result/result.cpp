//
//	リザルト画面
//

#include "result.h"
#include "../App.h"


//	コンストラクタ
Result::Result(){
	result_image = (Texture(RESULT_IMAGE));
}

//	リザルトの描画
void Result::draw(){
	drawTextureBox(-100, -100, 200, 200,
		0, 0, 200, 200,
		result_image,
		color256(200, 100, 200));
}

//	リザルトの処理
void Result::update(int& MODE){
	if (App::app_env->isPushKey(GLFW_KEY_ENTER)){
		MODE = 1;
	}
}