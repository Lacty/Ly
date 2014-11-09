
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

struct Player{
	int x, y;
	int width, height;
};

Player player{
	0, -280,
	20, 20
};

//	物体を移動させるときの値
//	新機能でプレイヤーの移動スピードを上げることもあるかもしれないので
//	constは外しておく
int move = 3;

//	プレイヤーの移動制御
void playerMove(AppEnv& app_env){
	if (app_env.isPressKey(GLFW_KEY_RIGHT))player.x += move;	//	右に移動
	if (app_env.isPressKey(GLFW_KEY_LEFT))player.x -= move;	//	左に移動

	//	画面外に移動しないように制御
	if (player.x > 500 - player.width)player.x = 500 - player.width;
	if (player.x < -500)player.x = -500;
}

//	プレイヤーの描画
void drawPlayer(AppEnv& app_env){

	playerMove(app_env);

	drawFillBox(player.x, player.y, player.width, player.height,
		color256(100, 100, 100));

}