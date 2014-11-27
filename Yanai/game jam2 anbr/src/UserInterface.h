#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"



void UmbrellaMove(){}

void drawUmbrella(Texture& umbrella1, Texture& umbrella2){

	drawTextureBox(KASA_X, KASA_Y, KASA_SIZE, KASA_SIZE,
		0, 0, 512, 512,
		umbrella1,
		Color(1, 1, 1));

}