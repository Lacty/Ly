
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"


enum  {
	//	エフェクトの最大数を定義
	EFECT_MAX = 3
};

//	エフェクトの構造体
struct Efect{
	bool active;			//	エフェクトを実体化させる

	float x, y;
	float width, height;

	float movey;			//	Y軸：エフェクトの移動
	float move;			//	sinに掛けているもの
	int point;			//	X軸：エフェクトの出現場所
	int kakex;			//	左右への振れ幅
};

//	エフェクトを配列で用意
Efect efect_data[EFECT_MAX] = {
	{ false, 0, 0, 0, 0, 0, 0, -200, 44, },
	{ false, 0, 0, 0, 0, 0, 10,   0, 50, },
	{ false, 0, 0, 0, 0, 0, 5, 180, 53, },
};

//	エフェクトを動かす変数
const float EFECT_MOVE = 0.05;
const float EFECT_MOVEY = -0.5;


//	mainの中で一度だけ実行させてます
void setupEfect(){

	//	エフェクトの初期化
	//	activeをすべてtrueにする
	for (int i = 0; i < EFECT_MAX; ++i){
		if (!efect_data[i].active){
			efect_data[i].active = true;
		}
	}

}

//	エフェクトの描画
void drawEfect(){
	
	/*	画面外に出た時の処理
		画面の上に移動させる	*/
	for (int i = 0; i < EFECT_MAX; ++i){
		if (efect_data[i].y < -300){
			efect_data[i].movey = 300;
		}
	}


	//	表示位置を変更するところ
	//	汚いコードになってるので、わからなかったら梁井まで
	//	完成して時間があれば手直しします
	for (int i = 0; i < EFECT_MAX; ++i){
		efect_data[i].move += EFECT_MOVE;
		efect_data[i].movey += EFECT_MOVEY;
		efect_data[i].x = sin(efect_data[i].move / 2) * efect_data[i].kakex + efect_data[i].point;
		efect_data[i].y = sin(efect_data[i].move) * 10 + efect_data[i].movey;
	}


	//
	//	activeがtrueの間表示させる
	//
	for (int i = 0; i < EFECT_MAX; ++i){
		if (efect_data[i].active){
			drawPoint(efect_data[i].x, efect_data[i].y, 5, color256(255, 150, 150));
		}
	}
}