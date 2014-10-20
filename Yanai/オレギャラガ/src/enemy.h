
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

int red = 1;

void drawEnemy(AppEnv& app_env, Enemy enemy[], Shot shot_data[]){
	for (int i = 0; i < SHOT_MAX; ++i){
		if (shot_data[i].active) {
			if (Hit(shot_data[i].x, shot_data[i].y, enemy[0].x, enemy[0].y, enemy[0].width, enemy[0].height)){
				red = 0;
			}
			else red = 1;
		}
	}


	drawFillBox(enemy[0].x, enemy[0].y,
		enemy[0].width, enemy[0].height,
		Color(red, 1, 1));

	drawFillBox(enemy[1].x, enemy[1].y,
		enemy[1].width, enemy[1].height,
		Color(red, 1, 1));

	drawFillBox(enemy[2].x, enemy[2].y,
		enemy[2].width, enemy[2].height,
		Color(red, 1, 1));
}