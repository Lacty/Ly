
#pragma once
#include "lib/appEnv.hpp"
#include "common.h"


// プレイヤーの構造体
struct Player{
	float x, y;
};

// プレイヤーのオブジェクトを作成
Player player = {
	-32, -410
};

// 自機の描画
void drawPlayer(Texture& ziki, Player& player){
	drawTextureBox(player.x, player.y, 100, 100,
		0, 0, 256, 256,
		ziki,
		Color(1, 1, 1));
}


// 自機の移動制御
void playerMovement(AppEnv& app_env, Player& player, float& move){
	if (app_env.isPressKey('A')) player.x -= move;
	if (app_env.isPressKey('D')) player.x += move;

	// 画面から出ないように制御
	if (player.x <= -WIDTH / 2) player.x = -WIDTH / 2;
	if (player.x >= WIDTH / 2 - 64) player.x = WIDTH / 2 - 64;
}


// 弾の処理（描画）
void playerShots(AppEnv& app_env, Shot shot_data[], Player& player){
	// スペースキーで弾を１つ生成
	if (app_env.isPushKey(GLFW_KEY_SPACE)){
		for (int i = 0; i < SHOT_MAX; ++i) {
			// 配列の中から未使用データを探す
			if (!shot_data[i].active) {
				// 未使用→使用中
				shot_data[i].active = true;

				// 撃った弾の数を足す
				MAX_SHOT = MAX_SHOT + 1;

				// 弾の初期値は自機より
				shot_data[i].x = player.x + 32;
				shot_data[i].y = player.y;

				break;
			}
		}
	}


	// 使用中の弾を動かす
	for (int i = 0; i < SHOT_MAX; ++i){
		if (shot_data[i].active) {
			shot_data[i].y += 15;

			// 画面外にでたら未使用にする
			if (shot_data[i].y >(HEIGHT / 2)) {
				shot_data[i].active = false;
			}
		}
	}

	// 使用中の弾を表示
	for (int i = 0; i < SHOT_MAX; ++i){
		if (shot_data[i].active){
			drawFillCircle(shot_data[i].x, shot_data[i].y,
				5, 5,
				10,
				Color(1, 1, 1));
		}
	}
}