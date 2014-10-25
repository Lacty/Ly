
#pragma once
#include "lib/appEnv.hpp"
#include "enemy.h"
#include "player.h"


//int play_point = 0;

int keta[6] = {
	0, 0, 0, 0, 0, 0
};

int kiritori[10] = {
	0, 100, 200, 300, 400, 500, 600, 700, 800, 900
};

struct Number{
	int x, y;
	int width, height;
};

Number number{ -180, 360, 60, 60 };

void score(AppEnv& app_env, Enemy enemy[], int& play_point){
	/*
	for (int e = 0; e < 40; ++e){
		if (enemy[e].isHit){
			play_point = play_point + enemy[e].point;
		}
	}*/


	keta[5] = play_point % 1000000;
	keta[5] = keta[5] / 100000;
	keta[4] = play_point % 100000;
	keta[4] = keta[4] / 10000;
	keta[3] = play_point % 10000;
	keta[3] = keta[3] / 1000;
	keta[2] = play_point % 1000;
	keta[2] = keta[2] / 100;
	keta[1] = play_point % 100;
	keta[1] = keta[1] / 10;
	keta[0] = play_point % 10;
}

void drawScore(AppEnv& app_env, Texture& numb){
	for (int i = 0; i < 6; ++i){
			drawTextureBox(number.x - i*30, number.y, number.width, number.height,
				kiritori[keta[i]], 0, 100, 100,
				numb,
				Color(1, 1, 1));
	}
}