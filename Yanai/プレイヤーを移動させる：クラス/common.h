
#pragma once

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

//	�����蔻��
//#include "isHit.h"


enum Window {
	WIDTH = 640,
	HEIGHT = 480
};

struct Object {
	int x, y;
	int width, height;

	Color color;
};