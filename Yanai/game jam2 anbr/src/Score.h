#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"

void score(int score){
	//	桁の数字を決める計算
	keta[3] = score % 10000;
	keta[3] = keta[3] / 1000;
	keta[2] = score % 1000;
	keta[2] = keta[2] / 100;
	keta[1] = score % 100;
	keta[1] = keta[1] / 10;
	keta[0] = score % 10;
}

void drawPlayPoint(Texture& number_image){
	//	スコア計算
	score(play_point);

	for (int i = 0; i < 3; i++){
		drawTextureBox(450 - i * 20, 280, 40, 40,
			kiritori_score[keta[i]], 0, 100, 100,
			number_image,
			Color(1, 1, 1));
	}
}