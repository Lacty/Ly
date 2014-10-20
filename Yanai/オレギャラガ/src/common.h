
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
};


// エネミーのオブジェクトを作成
Enemy enemy[3] = {
	0, 0, 30, 30,
	70, 30, 30, 30,
	-100, -20, 30, 30,
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