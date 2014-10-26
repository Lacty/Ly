
#pragma once
#include "lib/appEnv.hpp"
#include "common.h"
#include "player.h"

//
// �G���o�������邼���I
//


// �G�l�~�[�̍\����
struct Enemy{
	float x, y;
	float width, height;
	int life;
	int point;
	int number;
	bool isHit;
};


// �G�l�~�[�̃I�u�W�F�N�g���쐬
Enemy enemy[40] = {
	//Green
	5, 300, 35, 35, 2, 200, 3, false,
	-40, 300, 35, 35, 2, 200, 3, false,
	50, 300, 35, 35, 2, 200, 3, false,
	-85, 300, 35, 35, 2, 200, 3, false,

	//Red 1���
	-175, 250, 35, 35, 1, 100, 2, false,
	-130, 250, 35, 35, 1, 100, 2, false,
	-85, 250, 35, 35, 1, 100, 2, false,
	-40, 250, 35, 35, 1, 100, 2, false,
	5, 250, 35, 35, 1, 100, 2, false,
	50, 250, 35, 35, 1, 100, 2, false,
	95, 250, 35, 35, 1, 100, 2, false,
	140, 250, 35, 35, 1, 100, 2, false,

	//Red 2���
	-175, 200, 35, 35, 1, 100, 2, false,
	-130, 200, 35, 35, 1, 100, 2, false,
	-85, 200, 35, 35, 1, 100, 2, false,
	-40, 200, 35, 35, 1, 100, 2, false,
	5, 200, 35, 35, 1, 100, 2, false,
	50, 200, 35, 35, 1, 100, 2, false,
	95, 200, 35, 35, 1, 100, 2, false,
	140, 200, 35, 35, 1, 100, 2, false,

	//Blue 1���
	-220, 150, 35, 35, 1, 50, 1, false,
	-175, 150, 35, 35, 1, 50, 1, false,
	-130, 150, 35, 35, 1, 50, 1, false,
	-85, 150, 35, 35, 1, 50, 1, false,
	-40, 150, 35, 35, 1, 50, 1, false,
	5, 150, 35, 35, 1, 50, 1, false,
	50, 150, 35, 35, 1, 50, 1, false,
	95, 150, 35, 35, 1, 50, 1, false,
	140, 150, 35, 35, 1, 50, 1, false,
	185, 150, 35, 35, 1, 50, 1, false,

	//Blue 2��
	-220, 100, 35, 35, 1, 50, 1, false,
	-175, 100, 35, 35, 1, 50, 1, false,
	-130, 100, 35, 35, 1, 50, 1, false,
	-85, 100, 35, 35, 1, 50, 1, false,
	-40, 100, 35, 35, 1, 50, 1, false,
	5, 100, 35, 35, 1, 50, 1, false,
	50, 100, 35, 35, 1, 50, 1, false,
	95, 100, 35, 35, 1, 50, 1, false,
	140, 100, 35, 35, 1, 50, 1, false,
	185, 100, 35, 35, 1, 50, 1, false,
};


bool Hit(float shot_x, float shot_y,
	float x, float y, float width, float height){
	if (shot_x > x){
		if (shot_x < (x + width)){
			if (shot_y > y) {
				if (shot_y < (y + height))
					// �������Ă���̂�true
					return true;
			}
		}
	}
	// �������Ă��Ȃ��̂�false
	return false;
}


void drawEnemy(AppEnv& app_env, Enemy enemy[], Shot shot_data[],
	int& play_point, Texture& ene, Media& syobon, Media& sonna, Media& an, Media& iyan){
	for (int e = 0; e < 40; ++e){
		// �e�ƓG�̂����蔻��
		for (int i = 0; i < SHOT_MAX; ++i){
			if ((shot_data[i].active)&&(!enemy[e].isHit)) {
				if (Hit(shot_data[i].x, shot_data[i].y, enemy[e].x, enemy[e].y, enemy[e].width, enemy[e].height)){
					
					// �e������������Life���P���
					enemy[e].life -= 1;
					if (enemy[e].life == 0){
						enemy[e].isHit = true;
						play_point = play_point + enemy[e].point;

						// ���񂾂Ƃ��̃T�E���h��number�����ɕ����Ė炷
						if (enemy[e].number == 1)
							syobon.play();
						if (enemy[e].number == 2)
							sonna.play();
						if (enemy[e].number == 3)
							iyan.play();
					}
					if ((enemy[e].life==1)&&(enemy[e].number == 3))
						an.play();

					//enemy[e].isHit = true;
					shot_data[i].active = false;

					// �������e�����������瑫��
					MAX_HIT = MAX_HIT + 1;
				}
			}
		}

		// �G�̕`��
		if (enemy[e].isHit == false){
			// �i���o�[�ŋ敪���A�i���o�[�R��Life���Q
			// number3::if(Life==2)�� else��
			if (enemy[e].number == 3){
				if (enemy[e].life == 2)
				drawTextureBox(enemy[e].x - 5, enemy[e].y, enemy[e].width + 8, enemy[e].height + 3,
					0, 0, 340, 250,
					ene,
					color256(150, 256, 150));
				if (enemy[e].life == 1)
					drawTextureBox(enemy[e].x - 5, enemy[e].y, enemy[e].width + 8, enemy[e].height + 3,
					0, 0, 340, 250,
					ene,
					color256(256, 100, 100));
			}
			if (enemy[e].number == 2){
				drawTextureBox(enemy[e].x - 2, enemy[e].y - 5, enemy[e].width + 5, enemy[e].height + 5,
					350, 0, 330, 250,
					ene,
					color256(256, 150, 150));
			}
			if (enemy[e].number == 1){
				drawTextureBox(enemy[e].x, enemy[e].y-5, enemy[e].width+5, enemy[e].height+5,
					680, 0, 330, 250,
					ene,
					color256(150, 150, 256));
			}
		}
	}

	// �`�[�g�R�}���hZ
	// �G��S������������R�}���h
	if (app_env.isPushKey('Z')){
		for (int e = 0; e < 40; ++e){
			enemy[e].isHit = false;
			if (enemy[e].number == 1){
				enemy[e].life = 1;
			}
			else if (enemy[e].number == 2){
				enemy[e].life = 1;
			}
			else{
				enemy[e].life = 2;
			}
		}
	}
}