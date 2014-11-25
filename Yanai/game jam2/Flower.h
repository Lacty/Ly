#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"
#include "Player.h"


struct Flower{
	float x, y;
	float width, height;

	int number;
	int point;

	bool active;
};

Flower flower[2]={
	{ 100, 0, 30, 30, 1, 1, true },
	{ 130, 20, 30, 30, 1, 1, true },
};

void drawFlower(){
	/*for (int i = 0; i < FLOWER_MAX; i++){
		if (!flower[i].active){
			flower[i].active = true;
		}
	}*/

	for (int i = 0; i < FLOWER_MAX; i++){
		if (flower[i].active){
		drawFillBox(flower[i].x, flower[i].y,
			flower[i].width, flower[i].height,
			Color(1, 1, 1));
		}
	}

	for (int i = 0; i < FLOWER_MAX; i++){
		if (Hit(player.x, player.y, player.width, player.height,
			flower[i].x, flower[i].y, flower[i].width, flower[i].height)){
			flower[i].active = false;
		}
	}
}