
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "nimiPlayer.h"
#include "lib/random.hpp"

//	common�ɓ����ϐ�
//	����life�Ƃ��Ă���
int life = 0;


//	�~�j�Q�[���Ŋl������X�R�A��ۑ�����ϐ�
int nimiScore = 0;

struct Marron{
	bool active;
	
	int x, y;
	int width, height;

	int point;
	float vy;
};

enum  {
	MARRON_MAX = 20
};

//	Marron��z��ŗp��
Marron marron[MARRON_MAX] = {
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },

	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0},
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
};

bool isHit(int player_x, int player_y, int player_width, int player_height,
	int object_x, int object_y, int object_width, int object_height){
	if (player_x + player_width > object_x){
		if (player_x < object_x + object_width){
			if (player_y + player_height > object_y){
				if (player_y < object_y + object_height){
					//	�������Ă���̂�true��Ԃ�
					return true;
				}
			}
		}
	}
	//	�������ĂȂ��̂�false��Ԃ�
	return false;
}

void marronMove(AppEnv& app_env){

	//	�d�͔����@
	static float g = 0.1;
	static float vy[MARRON_MAX] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//	�����_�������@
	static int time = 0;
	time++;
	Random r;

	//	�I���o��������
	if (app_env.isPushKey(GLFW_KEY_ENTER)){
		for (int m = 0; m < MARRON_MAX; ++m){
			if (!marron[m].active){
				marron[m].active = true;
				
				//	x�̏����l�������_���Ō��߂�
				r.setSeed(time);
				marron[m].x = r.fromFirstToLast(-500, 480);
				break;
			}
		}
	}


	//	�I�ɏd�͂𑫂�
	for (int m = 0; m < MARRON_MAX; ++m){
		if (marron[m].active){
			marron[m].vy += g;
			marron[m].y -= marron[m].vy;

			//	��ʊO�ɂł�������i�A�N�e�B�u��false��
			if (marron[m].y < -310){
				marron[m].active = false;
			}
		}
		else{
			//	��ʊO�ɂł���I�̈ʒu��������
			marron[m].y = 300;
			marron[m].vy = 0;
		}
	}

}

//	�X�R�A���l��
void pointGeter(){

	for (int m = 0; m < MARRON_MAX; ++m){
		if (marron[m].active){
			if (isHit(player.x, player.y, player.width, player.height,
				marron[m].x, marron[m].y, marron[m].width, marron[m].height)){
				marron[m].active = false;

				//	�l�������I�̃|�C���g��
				//	�X�R�A�ɉ��Z������
				nimiScore = nimiScore + marron[m].point;
			}
		}
	}

}

//	�I�̕`��
void drawMarron(AppEnv& app_env){

	marronMove(app_env);
	pointGeter();

	for (int m = 0; m < MARRON_MAX; ++m){
		//	�A�N�e�B�u�Ȃ�`��
		if (marron[m].active){
			drawFillBox(marron[m].x, marron[m].y, marron[m].width, marron[m].height,
				color256(256, 120, 120));
		}
	}

}