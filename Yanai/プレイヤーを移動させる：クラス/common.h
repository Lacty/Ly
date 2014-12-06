
#pragma once

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

//	‚ ‚½‚è”»’è
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