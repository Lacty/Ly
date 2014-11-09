
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "nimiPlayer.h"
#include "lib/random.hpp"


//	commonに入れる変数
//	仮にlifeとしておく
int life = 0;

//	栗を出現させるトリガー
static bool trigger = false;

//	ミニゲームで獲得するスコアを保存する変数
int nimiScore = 0;

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
		COUNT = 1.5;
	}
	else if (nimiScore == 15){
		COUNT = 2;
	}
	else if (nimiScore == 25){
		COUNT = 3.5;
	}
	else if (nimiScore == 40){
		COUNT = 5;
	}

}


//	栗の移動制御
void marronMove(AppEnv& app_env){

	//	重力発生機
	static float g = 0.1;
	static float vy[MARRON_MAX] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//	ランダム発生機
	static int time = 0;
	time++;
	Random r;

	//	栗を出現させる
	if (trigger){
		for (int m = 0; m < MARRON_MAX; ++m){
			if (!marron[m].active){
				marron[m].active = true;
				
				//	xの初期値をランダムで決める
				r.setSeed(time);
				marron[m].x = r.fromFirstToLast(-500, 480);

				trigger = false;
				break;
			}
		}
	}


	//	栗に重力を足す
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

//	スコアを獲得
void pointGeter(){

	for (int m = 0; m < MARRON_MAX; ++m){
		if (marron[m].active){
			if (isHit(player.x, player.y, player.width, player.height,
				marron[m].x, marron[m].y, marron[m].width, marron[m].height)){
				marron[m].active = false;

				//	獲得した栗のポイントを
				//	スコアに加算させる
				nimiScore = nimiScore + marron[m].point;
			}
		}
	}

}

//	栗の描画
void drawMarron(AppEnv& app_env){

	marronTrigger();
	marronMove(app_env);
	pointGeter();

	for (int m = 0; m < MARRON_MAX; ++m){
		//	アクティブなら描画
		if (marron[m].active){
			drawFillBox(marron[m].x, marron[m].y, marron[m].width, marron[m].height,
				color256(256, 120, 120));
		}
	}

}