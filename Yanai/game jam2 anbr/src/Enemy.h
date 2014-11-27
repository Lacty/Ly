#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"

struct Enemy{
	bool active;

	float x, y;
	float width, height;
};

Enemy enemy[2] = {
	{ false, 0, 0, 20, 20, },
	{ false, 0, 0, 20, 20, }
};

void drawEnemy(){
}
