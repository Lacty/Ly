//
//	�^�C�g��Start�̕\��
//

#include "title.h"
#include "../isHit.h"
#include "../app.h"

using namespace collision;

//	�R���X�g���N�^
Title::Title(){
	Start[0] = { -200, 30, 100, 100, 0, 0, 100, 100, color256(0, 0, 0) };		// S
	Start[1] = { -120, -50, 100, 100, 100, 0, 100, 100, color256(0, 0, 0) };	// t
	Start[2] = { -40, -50, 100, 100, 200, 0, 100, 100, color256(0, 0, 0) };	// a
	Start[3] = { 40, -50, 100, 100, 300, 0, 100, 100, color256(0, 0, 0) };		// r
	Start[4] = { 120, -50, 100, 100, 400, 0, 100, 100, color256(0, 0, 0) };	// t
	cut_y = 0;
	MOVE = 5;
	modeSwitch = false;
}

//	�^�C�g���̃��Z�b�g�֐�
void Title::reset(){
	Start[0] = { -200, 30, 100, 100, 0, 0, 100, 100, color256(0, 0, 0) };		// S
	Start[1] = { -120, -50, 100, 100, 100, 0, 100, 100, color256(0, 0, 0) };	// t
	Start[2] = { -40, -50, 100, 100, 200, 0, 100, 100, color256(0, 0, 0) };	// a
	Start[3] = { 40, -50, 100, 100, 300, 0, 100, 100, color256(0, 0, 0) };		// r
	Start[4] = { 120, -50, 100, 100, 400, 0, 100, 100, color256(0, 0, 0) };	// t
	cut_y = 0;
	modeSwitch = false;
}

//	Title�̕`�揈��
void Title::draw(Texture& system_image){
	//	������̕\��
	for (int i = 0; i < 5; i++){
		drawTextureBox(Start[i].x, Start[i].y, Start[i].width, Start[i].height,
			Start[i].start_tx, Start[i].start_ty,
			Start[i].texture_width, Start[i].texture_height,
			system_image,
			Start[i].col);
	}
	//	���̕\��
	if (!modeSwitch){
		drawTextureBox(-240, 70-cut_y, 80, cut_y,
			500, 0, 100, cut_y,
			system_image,
			Color(1, 1, 1));
	}
}

//	Title�̏�������
void Title::update(int& MODE){
	//	�}�E�X�̈ʒu����
	mouse_pos = App::app_env->mousePosition();

	//	�������Ă��Ȃ��Ԃ̐F���w��
	Start[0].col = color256(0, 0, 0);

	//	modeSwitch��false�̊Ԏ��s
	if (!modeSwitch){
		//	�}�E�X����`�ɓ������Ă��邩�̔���
		if (point_to_rect(mouse_pos.x(), mouse_pos.y(), Start[0].x, Start[0].y,
			Start[0].width, Start[0].height)){

			//	�������Ă���Ԃ̐F���w��
			Start[0].col = color256(100, 100, 255);

			if (!isClick){
				click_posx = Start[0].x - mouse_pos.x();
				click_posy = Start[0].y - mouse_pos.y();
			}

			//	���N���b�N�����������Ă���Ԃ̏���
			if (App::app_env->isPressButton(Mouse::LEFT)){
				isClick = true;
				Start[0].x = mouse_pos.x() + click_posx;
				Start[0].y = mouse_pos.y() + click_posy;
			}
			else {
				isClick = false;

				//	���N���b�N�����̈ʒu�ŗ�����
				//	"S"���ʒu�ֈړ�������
				if (point_to_rect(mouse_pos.x(), mouse_pos.y(), -200, -50,
					100, 100)){
					if (App::app_env->isPullButton(Mouse::LEFT)){
						Start[0].x = -200;
						Start[0].y = -50;

						modeSwitch = true;
					}
				}
			}
		}

		//	���̐؂���ʒu�ύX����
		cut_y++;
		if (cut_y >= 100){
			cut_y = 0;
		}
	}

	//	modeSwitch��true�ɂȂ�������s
	if (modeSwitch){
		for (int i = 0; i < 5; i++){
			Start[i].y += MOVE;

			if (Start[i].y >= Window::HEIGHT / 2){
				reset();
				MODE = 1;
			}
		}
	}


}