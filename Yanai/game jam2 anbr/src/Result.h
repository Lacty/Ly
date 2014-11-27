#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"

void ResultMove(){}

void drawResult(AppEnv& app_env, Texture& HappyEnd, Texture& BadEnd){

	if (play_point < 20)
	{
		drawTextureBox(-512, -340, 1024, 680,
			0, 0, 1024, 680,
			BadEnd,
			Color(1, 1, 1));
	}
	else {
		drawTextureBox(-512, -340, 1024, 680,
			0, 0, 1024, 680,
			HappyEnd,
			Color(1, 1, 1));
	}

	if (app_env.isPushKey(GLFW_KEY_ENTER)){
		// ‰Šú‰»
		XXXX_hit = true;
		prologFlag = true;
		player.x = -300;
		player.y = -190;
		box_x = -512;
		box_y = -340;
		play_point = 0;
		XXX = -512;
		X = 0;
		Y = 0;
		flower[0].x = box_x + 400;
		flower[0].y = box_y + 350;
		flower[1].x = box_x + 600;
		flower[1].y = box_y + 350;
		flower[2].x = box_x + 1000;
		flower[2].y = box_y + 800;
		flower[3].x = box_x + 1500;
		flower[3].y = box_y + 800;
		flower[4].x = box_x + 1300;
		flower[4].y = box_y + 1300;
		flower[5].x = box_x + 1600;
		flower[5].y = box_y + 2000;
		flower[6].x = box_x + 2500;
		flower[6].y = box_y + 1400;
		flower[7].x = box_x + 3000;
		flower[7].y = box_y + 500;
		flower[8].x = box_x + 3500;
		flower[8].y = box_y + 600;
		flower[9].x = box_x + 3500;
		flower[9].y = box_y + 1300;

		p_time = 10 * 60;
		prolog_time = 10 * 60;
		prolog_rect_alpha = 0;
		player.x = -300;
		GameFlag = 2;
		Kiritori_MODE = 0;
		XXX = -512;
		X = 0;
		Y = 0;


		for (int i = 0; i < 10; i++){
			flower[i].active = true;
		}



		GameFlag = 0;
	}


}