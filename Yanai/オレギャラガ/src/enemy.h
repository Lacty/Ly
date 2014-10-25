
#pragma once
#include "lib/appEnv.hpp"
#include "common.h"
#include "player.h"

//
// 敵を出現させるぞぃ！
//

// エネミーの構造体
struct Enemy{
	float x, y;
	float width, height;
	int life;
	int point;
	bool isHit;
};


// エネミーのオブジェクトを作成
Enemy enemy[40] = {
	//Green
	5, 300, 35, 35, 2, 200, false,
	-40, 300, 35, 35, 2, 200, false,
	50, 300, 35, 35, 2, 200, false,
	-85, 300, 35, 35, 2, 200, false,

	//Red 1列目
	-175, 250, 35, 35, 1, 100, false,
	-130, 250, 35, 35, 1, 100, false,
	-85, 250, 35, 35, 1, 100, false,
	-40, 250, 35, 35, 1, 100, false,
	5, 250, 35, 35, 1, 100, false,
	50, 250, 35, 35, 1, 100, false,
	95, 250, 35, 35, 1, 100, false,
	140, 250, 35, 35, 1, 100, false,

	//Red 2列目
	-175, 200, 35, 35, 1, 100, false,
	-130, 200, 35, 35, 1, 100, false,
	-85, 200, 35, 35, 1, 100, false,
	-40, 200, 35, 35, 1, 100, false,
	5, 200, 35, 35, 1, 100, false,
	50, 200, 35, 35, 1, 100, false,
	95, 200, 35, 35, 1, 100, false,
	140, 200, 35, 35, 1, 100, false,

	//Blue 1列目
	-220, 150, 35, 35, 1, 50, false,
	-175, 150, 35, 35, 1, 50, false,
	-130, 150, 35, 35, 1, 50, false,
	-85, 150, 35, 35, 1, 50, false,
	-40, 150, 35, 35, 1, 50, false,
	5, 150, 35, 35, 1, 50, false,
	50, 150, 35, 35, 1, 50, false,
	95, 150, 35, 35, 1, 50, false,
	140, 150, 35, 35, 1, 50, false,
	185, 150, 35, 35, 1, 50, false,

	//Blue 2列
	-220, 100, 35, 35, 1, 50, false,
	-175, 100, 35, 35, 1, 50, false,
	-130, 100, 35, 35, 1, 50, false,
	-85, 100, 35, 35, 1, 50, false,
	-40, 100, 35, 35, 1, 50, false,
	5, 100, 35, 35, 1, 50, false,
	50, 100, 35, 35, 1, 50, false,
	95, 100, 35, 35, 1, 50, false,
	140, 100, 35, 35, 1, 50, false,
	185, 100, 35, 35, 1, 50, false,
};


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


void drawEnemy(AppEnv& app_env, Enemy enemy[], Shot shot_data[], int& play_point){
	for (int e = 0; e < 40; ++e){
		// 弾と敵のあたり判定
		for (int i = 0; i < SHOT_MAX; ++i){
			if ((shot_data[i].active)&&(!enemy[e].isHit)) {
				if (Hit(shot_data[i].x, shot_data[i].y, enemy[e].x, enemy[e].y, enemy[e].width, enemy[e].height)){
					enemy[e].life -= 1;
					if (enemy[e].life == 0){
						enemy[e].isHit = true;
						play_point = play_point + enemy[e].point;
					}
					//enemy[e].isHit = true;
					shot_data[i].active = false;

					// 撃った弾が当たったら足す
					MAX_HIT = MAX_HIT + 1;
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

	if (app_env.isPushKey('Z')){
		for (int e = 0; e < 40; ++e){
			enemy[e].isHit = false;
		}
	}
}