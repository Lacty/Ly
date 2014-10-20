
#pragma once
#include "lib/appEnv.hpp"
#include "common.h"
#include "player.h"

//
// 敵を出現させるぞぃ！
//


bool Hit(float shot_x, float shot_y,
	float x, float y, float width, float height){
	if (shot_x > x){
		if (shot_x < (x + width)){
			if (shot_y > y) {
				if (shot_y < (y + height))
					// 当たっているのでtrue
					return true;
			}
		}
	}
	// 当たっていないのでfalse
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
		// 弾と敵のあたり判定
		for (int i = 0; i < SHOT_MAX; ++i){
			if ((shot_data[i].active)&&(!enemy[e].isHit)) {
				if (Hit(shot_data[i].x, shot_data[i].y, enemy[e].x, enemy[e].y, enemy[e].width, enemy[e].height)){
					enemy[e].isHit = true;
					shot_data[i].active = false;
				}
			}
		}

		// 敵の描画
		if (enemy[e].isHit == false){
			drawFillBox(enemy[e].x, enemy[e].y,
				enemy[e].width, enemy[e].height,
				Color(1, 1, 1));
		}
	}
}