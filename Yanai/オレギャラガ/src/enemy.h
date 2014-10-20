
#pragma once
#include "lib/appEnv.hpp"
#include "common.h"
#include "player.h"

//
// “G‚ðoŒ»‚³‚¹‚é‚¼‚¡I
//


bool Hit(float shot_x, float shot_y,
	float x, float y, float width, float height){
	if (shot_x > x){
		if (shot_x < (x + width)){
			if (shot_y > y) {
				if (shot_y < (y + height))
					// “–‚½‚Á‚Ä‚¢‚é‚Ì‚Åtrue
					return true;
			}
		}
	}
	// “–‚½‚Á‚Ä‚¢‚È‚¢‚Ì‚Åfalse
	return false;
}


void drawEnemy(AppEnv& app_env, Enemy enemy[], Shot shot_data[]){
	/*
	for (int i = 0; i < SHOT_MAX; ++i){
		if (shot_data[i].active) {
			for (int e = 0; e < 3; ++e){
				if (Hit(shot_data[i].x, shot_data[i].y, enemy[e].x, enemy[e].y, enemy[e].width, enemy[e].height)){
					enemy[0].isHit = true;
					shot_data[i].active = true;
				}
			}
		}
	}*/


	for (int e = 0; e < 4; ++e){
		// ’e‚Æ“G‚Ì‚ ‚½‚è”»’è
		for (int i = 0; i < SHOT_MAX; ++i){
			if ((shot_data[i].active)&&(!enemy[e].isHit)) {
				if (Hit(shot_data[i].x, shot_data[i].y, enemy[e].x, enemy[e].y, enemy[e].width, enemy[e].height)){
					enemy[e].isHit = true;
					shot_data[i].active = false;
				}
			}
		}

		// “G‚Ì•`‰æ
		if (enemy[e].isHit == false){
			drawFillBox(enemy[e].x, enemy[e].y,
				enemy[e].width, enemy[e].height,
				Color(1, 1, 1));
		}
	}
}