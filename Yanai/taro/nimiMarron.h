
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "nimiPlayer.h"
#include "lib/random.hpp"

struct Marron{
	bool active;
	
	int x, y;
	float width, height;

	int point;
};

enum  {
	MARRON_MAX = 20
};

//	Marronを配列で用意
Marron marron[MARRON_MAX] = {
	{ true, 0, 300, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },

	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
	{ false, 0, 0, 20, 20, 1 },
};

void marronMove(){

	//	重力発生機
	static float g = 0.1;
	static float vy[MARRON_MAX] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//	vyに重力を足す
	for (int m = 0; m < MARRON_MAX; ++m){
		if (marron[m].active){
			vy[m] += g;
		}
	}

	//	栗のyに重力を足す
	for (int m = 0; m < MARRON_MAX; ++m){
		if (marron[m].active){
			marron[m].y -= vy[m];
		}
	}


	static int time = 0;
	time++;
	Random r;
	r.setSeed(time);

	for (int m = 0; m < MARRON_MAX; ++m){
		if (marron[m].active){
			marron[m].x = r.fromFirstToLast(-500, 480);
		}
	}

}

//	栗の描画
void drawMarron(){

	marronMove();

	for (int m = 0; m < MARRON_MAX; ++m){
		//	アクティブなら描画
		if (marron[m].active){
			drawFillBox(marron[m].x, marron[m].y, marron[m].width, marron[m].height,
				color256(256, 120, 120));
		}
	}

}