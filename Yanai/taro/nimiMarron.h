
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "nimiPlayer.h"
#include "lib/random.hpp"
#include "common.h"


//	栗を出現させるトリガー
static bool trigger = false;

struct Marron{
	bool active;
	
	int x, y;
	int width, height;

	int point;
	float vy;
};

//	栗の最大数を定義
enum  {
	MARRON_MAX = 40
};

//	Marronを配列で用意
Marron marron[MARRON_MAX] = {
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },

	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },

	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },

	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
	{ false, 0, 300, 20, 20, 1, 0 },
};

//	あたり判定をboolで返す
bool isHit(int player_x, int player_y, int player_width, int player_height,
	int object_x, int object_y, int object_width, int object_height){
	if (player_x + player_width > object_x){
		if (player_x < object_x + object_width){
			if (player_y + player_height > object_y){
				if (player_y < object_y + object_height){
					//	当たっているのでtrueを返す
					return true;
				}
			}
		}
	}
	//	当たってないのでfalseを返す
	return false;
}


//	栗を出現させるトリガー
void marronTrigger(){
	//	栗を落下させるトリガーとなる変数
	static float trigger_count = 0;
	static float COUNT = 1;

	static int MODE = 0;

	//	triggerをtrueにする条件
	trigger_count += COUNT;
	if (trigger_count >= 60){
		trigger = true;

		//	trigger_count:0にカウントを初期化
		trigger_count = 0;
	}

	//	栗を一定の数獲得するごとに
	//	出現スピードを上げる
	if (nimiScore == 5){
		MODE = 1;
	}
	else if (nimiScore == 15){
		MODE = 2;
	}
	else if (nimiScore == 25){
		MODE = 3;
	}
	else if (nimiScore == 40){
		MODE = 4;
	}
	else if (nimiScore == 60){
		MODE = 5;
	}
	else if (nimiScore == 100){
		MODE = 6;
	}

	switch (MODE){
		case 0:{
			COUNT = 1;
		}break;
	
		case 1:{
			COUNT = 1.5;
		}break;
		
		case 2:{
			COUNT = 2.5;
		}break;
	
		case 3:{
			COUNT = 4;
		}break;
	
		case 4:{
			COUNT = 5.5;
		}break;

		case 5:{
			COUNT = 7;
		}

		case 6:{
			COUNT = 10;
		}
	}

}


//	栗の移動制御
void marronMove(AppEnv& app_env){

	//	重力発生機
	static double g = 0.1;
	static float vy[MARRON_MAX] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//	ランダム発生機
	static int time = 0;
	Random r;

	//	完全ランダムのための処理
	//	ランダムにタイム
	if (!isReady){
		time++;
		r.setSeed(time);
	}

	//	栗を出現させる
	if (trigger){
		for (int m = 0; m < MARRON_MAX; ++m){
			if (!marron[m].active){
				marron[m].active = true;
				
				//	xの初期値をランダムで決める
				time++;
				r.setSeed(time);
				marron[m].x = r.fromFirstToLast(-500, 480);

				trigger = false;
				break;
			}
		}
	}

	//	isReadyがtrueの時
	//	栗に重力を足す
	if (isReady){
		for (int m = 0; m < MARRON_MAX; ++m){
			if (marron[m].active){
				marron[m].vy += g;
				marron[m].y -= marron[m].vy;

				//	画面外にでたら消す（アクティブをfalseに
				if (marron[m].y < -310){
					marron[m].active = false;
				}
			}
			else{
				//	画面外にでたら栗の位置を初期化
				marron[m].y = 300;
				marron[m].vy = 0;
			}
		}
	}
}

//	スコアを獲得
void pointGeter(){

	for (int m = 0; m < MARRON_MAX; ++m){
		if (marron[m].active){
			if (isHit(player.x, player.y, player.width, player.height,
				marron[m].x, marron[m].y, marron[m].width, marron[m].height)){
				marron[m].active = false;

				//	獲得した栗のポイントを
				//	スコアに加算させる
				//	PowerPointで取得するポイントを変更させる
				//	nimiPlayer.h参照（パワーアップの作用）
				nimiScore = nimiScore + marron[m].point*PowerPoint;
			}
		}
	}
}

//	栗の描画
void drawMarron(AppEnv& app_env){
	if (isReady){
		marronTrigger();
		pointGeter();
	}
	//	完全ランダムになるようにMoveを外しておく
	marronMove(app_env);

	for (int m = 0; m < MARRON_MAX; ++m){
		//	アクティブなら描画
		if (marron[m].active){
			drawFillBox(marron[m].x, marron[m].y, marron[m].width, marron[m].height,
				color256(256, 120, 120));
		}
	}

}