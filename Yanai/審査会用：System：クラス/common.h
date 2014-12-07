
#pragma once

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "image.h"


enum Window {
	WIDTH = 640,
	HEIGHT = 480
};

//	�I�u�W�F�N�g�\����
struct Object{
	float x, y;
	float width, height;

	float start_tx;
	float start_ty;

	float texture_width;
	float texture_height;

	Color col;
};
