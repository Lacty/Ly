#pragma once

#include "lib/defines.hpp"
// ↑これは必ず最初にincludeする

#include "lib/appEnv.hpp"
// ↑必要なヘッダファイルは適時インクルードする

//共通の変数読み込み
#include "common.h"

void player_draw(){

	//プレイヤー表示
	drawFillBox(player_x, player_y, player_size_x, player_size_y, Color(1, 0.2, 0.2));

}

void player_movement(AppEnv& app_env){

	//プレイヤー操作
	//左に壁がない時左キーで左へ
	if (wall_left == 0){
		if (app_env.isPressKey(GLFW_KEY_LEFT)){
			camera_x += player_move_power;
		}
	}
	//右に壁がない時右キーで右へ
	if (wall_right == 0){
		if (app_env.isPressKey(GLFW_KEY_RIGHT)){
			camera_x -= player_move_power;
		}
	}
	//地面にいるときスペースでジャンプ
	if (jump == 0){
		if (app_env.isPushKey(GLFW_KEY_SPACE)){
			jump = 1;
		}
	}

	//ジャンプの上昇処理
	if (jump == 1){
		jump_vy -= 1;
		player_y += jump_vy;
		//最高点まで到達したら落下に切り替え(jump = 0 →地面にいる,jump =1→上昇中,jump = -1 →落下中)
		if (jump_vy == 0){
			jump = -1;
			jump_vy = jump_power;
		}
	}
	//落下処理
	if (jump == -1 || jump == 0){
		gravity += 1;
		player_y -= gravity;
		jump = -1;
	}

}

//自機
void player(){

	//プレイヤー表示
	player_draw();

	//プレイヤーの動き関連
	player_movement(app_env);
	
}
