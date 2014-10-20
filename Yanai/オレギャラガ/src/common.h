
#pragma once
#include "lib/appEnv.hpp"



// アプリのウインドウサイズ
enum Window {
	WIDTH = 650,
	HEIGHT = 850
};

// プレイヤーの構造体
struct Player{
	float x, y;
};

// プレイヤーのオブジェクトを作成
Player player = {
	-32, -410
};

// エネミーの構造体
struct Enemy{
	float x, y;
	float width, height;
	bool isHit;
};


// エネミーのオブジェクトを作成
Enemy enemy[4] = {
	30, 300, 40, 40, false,
	-70, 300, 40, 40, false,
	60, 200, 40, 40, false,
	-100, 200, 40, 40, false,
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


// 背景の描画
void backGround(int& scroll, Texture& bg){

	scroll -= 3;

	drawTextureBox(-325, -425, 650, 850,
		0, scroll, 650, 850,
		bg,
		Color(1, 1, 1));
}