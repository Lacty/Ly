//
//	Player
//

#include "player.h"
#include "../app.h"


//	�R���X�g���N�^
Player::Player(){
	player_image = (Texture(PLAYER_IMAGE));
	player = { -WIDTH/2, -100, 80, 40, 0, 0, 200, 100, Color(1, 1, 1),
		false, true, -0.2, 0, 2 };
	tex_count = 0;
	for (int i = 0; i < SHOT_MAX; i++){
		shot[i] = { 0, 0, 40, 20,
			400, 200, 100, 100,
			Color(1, 1, 1), false, true };
		shot[i].speed = { 10 };
	}
}

//	Player�̕`��
void Player::draw(){
	//	�I���^�̉摜
	drawTextureBox(player.x, player.y, player.width, player.height,
		player.start_tx, player.start_ty,
		player.texture_width, player.texture_height,
		player_image,
		player.col);
	//	�e�̉摜
	for (int i = 0; i < SHOT_MAX; i++){
		if (shot[i].active){
			drawTextureBox(shot[i].x, shot[i].y, shot[i].width, shot[i].height,
				shot[i].start_tx, shot[i].start_ty,
				shot[i].texture_width, shot[i].texture_height,
				player_image,
				shot[i].col);
		}
	}

}

//	Player�̏�������
void Player::update(){
	playerMove();
	playerShot();
}

void Player::playerMove(){
	pos = App::app_env->mousePosition();

	//	�}�E�X���I���^���E�ɂ��鎞
	//	�I���^���E�Ɉړ�������
	if ((player.x + player.width) < pos.x()){
		player.x += player.speed;
	}
	//	�}�E�X���I���^�̒��S����E�ɂ����
	//	�I���^���E�Ɍ�������
	if ((player.x + player.width / 2) < pos.x()){
		if (!player.right){
			player.right = true;
			player.start_tx = 0;
			player.start_ty = 0;
		}
	}
	//	�}�E�X���I���^��荶�ɂ��鎞
	//	�I���^�����Ɉړ�������
	if (player.x > pos.x()){
		player.x -= player.speed;
	}
	//	�}�E�X���I���^�̒��S���獶�ɂ����
	//	�I���^�����Ɍ�������
	if ((player.x + player.width / 2) > pos.x()){
		if (player.right){
			player.right = false;
			player.start_tx = 600;
			player.start_ty = 0;
		}
	}


	//	�I���^�̏d��
	player.vy += player.g;
	player.y += player.vy;
}


void Player::playerShot(){
	if (App::app_env->isPushButton(LEFT)){
		for (int i = 0; i < SHOT_MAX; i++){
			if (!shot[i].active){
				//	�L�����N�^�[�����E�ǂ���������Ă��邩�ۑ�
				if (player.right){
					shot[i].right = true;
				}
				else{
					shot[i].right = false;
				}

				//	�e����ˏo
				shot[i].active = true;

				//	�����ʒu�̓L�����N�^�[���Q��
				shot[i].x = player.x;
				shot[i].y = player.y;
				break;
			}
		}
	}

	//	�e�������������Ɉړ�������
	for (int i = 0; i < SHOT_MAX; i++){
		if (shot[i].active){
			if (shot[i].right){
				shot[i].x += shot[i].speed;
				//	�摜�̐؂���ʒu���ύX
				shot[i].start_tx = 400;
			}
			else {
				shot[i].x -= shot[i].speed;
				//	�摜�̐؂���ʒu���ύX
				shot[i].start_tx = 500;
			}
		}
	}

	//	�e����ʊO�ɂł����������
	for (int i = 0; i < SHOT_MAX; i++){
		if (shot[i].x > WIDTH / 2){
			shot[i].active = false;
		}
		if (shot[i].x < (-WIDTH / 2) - shot[i].width){
			shot[i].active = false;
		}
	}
}
