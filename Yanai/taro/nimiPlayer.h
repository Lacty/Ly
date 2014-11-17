
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"

struct Player{
	int x, y;
	int width, height;
};

Player player{
	0, -280,
	40, 20
};

//	物体を移動させるときの値
//	新機能でプレイヤーの移動スピードを上げることもあるかもしれないので
//	constは外しておく
int move = 4;


//	プレイヤーの移動制御
void playerMove(AppEnv& app_env){
	if (app_env.isPressKey('D'))player.x += move;	//	右に移動
	if (app_env.isPressKey('A'))player.x -= move;	//	左に移動

	//	画面外に移動しないように制御
	if (player.x > 500 - player.width)player.x = 500 - player.width;
	if (player.x < -500)player.x = -500;
}

//	パワーアップ処理
void powerUp(AppEnv& app_env){

	static int MODE = 0;
	if (MODE == 0){
		if (nimiScore == 15){
			PowerWidthUp = true;
			MODE = 1;
		}
	}
	if (MODE == 1){
		if (nimiScore == 50){
			PowerPointUp = true;
			MODE = 2;
		}
	}
	if (MODE == 2){
		if (nimiScore == 60){
			PowerWidthUp2 = true;
			MODE = 3;
		}
	}

	//	パワーアップができる状態でPを押すと
	//	栗を拾える範囲が拡大する
	if (PowerWidthUp){
		if (app_env.isPressKey('P')){
			app_env.flushInput();
			player.width = player.width + 20;

			PowerWidthUp = false;
		}
	}
	if (PowerWidthUp2){
		if (app_env.isPushKey('P')){
			app_env.flushInput();
			player.width = player.width + 40;

			PowerWidthUp2 = false;
		}
	}

	//	獲得できるポイントが増加
	//	下の関数参照
	if (PowerPointUp){
		if (app_env.isPushKey('O')){
			app_env.flushInput();
			PowerPoint = 2;
			PowerPointUp = false;
		}
	}
}

//	獲得するポイントを増加させる関数
void powerPointUp(){
	static int count = 0;

	if (PowerPoint == 2){
		count++;
		if (count >= 600){
			PowerPoint = 1;
			count = 0;
		}
	}
}

//	プレイヤーの描画
void drawPlayer(AppEnv& app_env){

	/*
		プレイヤーの移動制御
		栗を拾うあたり判定の増強
		獲得できるポイントを一定時間増加
	*/
	if (isReady){
		playerMove(app_env);
		powerUp(app_env);
		powerPointUp();
	}
	drawFillBox(player.x, player.y, player.width, player.height,
		color256(100, 100, 100));

}