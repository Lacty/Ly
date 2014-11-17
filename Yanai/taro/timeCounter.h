
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"

struct Object{
	int x, y;
	int width, height;
};

Object object{
	-300, 270,
	790, 20
};

void timeCounter(){
	if (isReady){
		miniTimer--;
	}

	if (miniTimer == 0){
		isReady = false;
	}
}

void drawCount(){
	timeCounter();

	//	残り時間が少なくなるとバーの色が変化
	static int red = 256;
	static int green = 180;
	static int blue = 180;

	if (miniTimer < 600){
		green = 0;
		blue = 0;
	}

	//	残り時間を矩形で表示
	drawFillBox(object.x, object.y, object.width, object.height,
		color256(100, 100, 100));
	drawFillBox(object.x, object.y, (miniTimer*object.width)/(60*60), object.height,
		color256(red, green, blue));
	//	枠線
	drawBox(object.x, object.y, object.width, object.height, 2, color256(200, 200, 256));
}