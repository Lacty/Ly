
#pragma once
#include "lib/appEnv.hpp"



// アプリのウインドウサイズ
enum Window {
	WIDTH = 650,
	HEIGHT = 850
};


// 最大弾数を定義
enum  {
	SHOT_MAX = 2
};


// 弾の定義
struct Shot{
	float x, y;
	bool active;
};

// 弾を配列で用意
Shot shot_data[SHOT_MAX];

// 弾を
int MAX_SHOT;                    // 撃った数
int MAX_HIT;                    // 当たった数
int MAX_MISS = MAX_SHOT - MAX_HIT;     // 外した数


// 背景の描画
void backGround(int& scroll, Texture& bg){

	scroll -= 3;

	drawTextureBox(-325, -425, 650, 850,
		0, scroll, 650, 850,
		bg,
		Color(1, 1, 1));
}