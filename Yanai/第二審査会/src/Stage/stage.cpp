//
//	ステージ選択
//

#include "stage.h"
#include "../app.h"
#include "../lib/random.hpp"


//	コンストラクタ
Stage::Stage(){
	Stage_[0] = { -175, -300, 100, 100, 0, 0, 100, 100, color256(0, 0, 0) };	//S
	Stage_[1] = { -105, -300, 100, 100, 100, 0, 100, 100, color256(0, 0, 0) };	//t
	Stage_[2] = { -48, -300, 100, 100, 200, 0, 100, 100, color256(0, 0, 0) };	//a
	Stage_[3] = { 20, -300, 100, 100, 0, 200, 100, 100, color256(0, 0, 0) };	//g
	Stage_[4] = { 80, -300, 100, 100, 100, 200, 100, 100, color256(0, 0, 0) };	//e
	alpha = 255;
	for (int i = 0; i < Yaji_MAX; i++){
		Yaji[i] = {
			0, -320, 100, 100,
			900, 0, 100, 100,
			color256(100, 100, 100, alpha),
			false
		};
	}
	Trigger = false;
	trigger_count = 0;
	COUNT = 2;
	Yaji_MOVE = 2;
	startStage_ = true;
	MOVE = 5;
}

//	Stageの描画
void Stage::draw(Texture& system_image){
	//	背景(矢印)の描画
	for (int i = 0; i < Yaji_MAX; i++){
		if (Yaji[i].active){
			drawTextureBox(Yaji[i].x, Yaji[i].y, Yaji[i].width, Yaji[i].height,
				Yaji[i].start_tx, Yaji[i].start_ty,
				Yaji[i].texture_width, Yaji[i].texture_height,
				system_image,
				Yaji[i].col,
				0.75,
				Vec2f(1, 1),
				Vec2f(0, 0));
		}
	}

	//	Stage(文字)の描画
	for (int i = 0; i < 5; i++){
		drawTextureBox(Stage_[i].x, Stage_[i].y, Stage_[i].width, Stage_[i].height,
			Stage_[i].start_tx, Stage_[i].start_ty,
			Stage_[i].texture_width, Stage_[i].texture_height,
			system_image,
			Stage_[i].col);
	}
}

//	Stageの処理部分
void Stage::update(int& MODE){
	if (startStage_){
		startStage();
	}
	else {
		backGround();
	}
	
	if (App::app_env->isPushKey(GLFW_KEY_ENTER)){
		reset();
		MODE = 2;
	}
}

//	ステージ選択へ来た時の演出
void Stage::startStage(){
	for (int i = 0; i < 5; i++){
		if (Stage_[i].y <= 100){
			Stage_[i].y += MOVE;
		}
		else {
			startStage_ = false;
		}
	}
}

//	背景の演出
void Stage::backGround(){
	trigger_count += COUNT;
	if (trigger_count >= 60){
		Trigger = true;

		//	trigger_count:0に初期化
		trigger_count = 0;
	}

	//	ランダム発生機
	static int time = 0;
	Random r;
	time++;
	r.setSeed(time);

	if (Trigger){
		for (int i = 0; i < Yaji_MAX; i++){
			//	アクティブでない矢印を探す
			if (!Yaji[i].active){
				//	アクティブでない矢印を1つtrueにする
				Yaji[i].active = true;

				//	x値にランダムを与える
				Yaji[i].x = r.fromFirstToLast(-400, 300);
				//	大きさをランダムにする
				Yaji[i].width = r.fromFirstToLast(20, 100);
				Yaji[i].height = Yaji[i].width;

				//	トリガーをfalseに
				Trigger = false;

				//	一度だけ実行するためにブレイク
				break;
			}
		}
	}

	for (int i = 0; i < Yaji_MAX; i++){
		if (Yaji[i].active){
			Yaji[i].y += Yaji_MOVE;

			//	矢印(背景)が画面外にでたら消す処理
			if (Yaji[i].y >= 240){
				Yaji[i].active = false;
			}
		}
		else {
			Yaji[i].y = -320;
		}
	}

}

//	リセット関数
void Stage::reset(){
	for (int i = 0; i < 5; i++){
		Stage_[i].y = -300;
	}
	for (int i = 0; i < Yaji_MAX; i++){
		Yaji[i].y = -320;
		Yaji[i].active = false;
	}
	alpha = 255;
	startStage_ = true;
}