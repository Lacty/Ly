#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"
#include "Player.h"
#include "Map.h"


struct Flower{
	float x, y;
	float width, height;

	int number;
	int point;

	bool active;
};


Flower flower[FLOWER_MAX]={
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
	{ 0, 0, 100, 100, 1, 5, true },
};

void drawFlower(Texture& hana){
	/*for (int i = 0; i < FLOWER_MAX; i++){
	if (!flower[i].active){
	flower[i].active = true;
	}
	}*/

	flower[0].x = box_x+400;
	flower[0].y = box_y+350;
	flower[1].x = box_x+600;
	flower[1].y = box_y+350;
	flower[2].x = box_x+1000;
	flower[2].y = box_y+800;
	flower[3].x = box_x+1500;
	flower[3].y = box_y+800;
	flower[4].x = box_x+1300;
	flower[4].y = box_y+1300;
	flower[5].x = box_x+1600;
	flower[5].y = box_y+2000;
	flower[6].x = box_x+2500;
	flower[6].y = box_y+1400;
	flower[7].x = box_x+3000;
	flower[7].y = box_y+500;
	flower[8].x = box_x+3500;
	flower[8].y= box_y+600;
	flower[9].x = box_x+3500;
	flower[9].y = box_y+1300;
	flower[10].x = box_x+3700;
	flower[10].y = box_y+2000;

	for (int i = 0; i < FLOWER_MAX; i++){
		if (flower[i].active){
			drawTextureBox(flower[i].x, flower[i].y,
				flower[i].width, flower[i].height,
				0, 0, 1024, 1024,
				hana,
				Color(1, 1, 1));
			//drawFillBox(flower[i].x, flower[i].y,
			//	flower[i].width, flower[i].height,
			//	Color(1, 1, 1));
		}
	}

	for (int i = 0; i < FLOWER_MAX; i++){
		if (flower[i].active){
			if (Hit(player.x, player.y, player.width-40, player.height-40,
				flower[i].x, flower[i].y, flower[i].width, flower[i].height)){
				flower[i].active = false;
				play_point = play_point + flower[i].point;
			}
		}
	}

}