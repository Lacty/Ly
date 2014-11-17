
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

float alfa = 0;
int drawBlackOut(){
	alfa += 1.5;
	drawFillBox(-500, -300, 1000, 600, color256(0, 0, 0, alfa));

	if (alfa >= 255){
		return 0;
	}
}