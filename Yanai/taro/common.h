
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

//	commonに入れる変数
//	仮にlifeとしておく
int life = 0;

//	ミニゲームのタイム変数
int miniMODE = 0;

//	本編のスコアを保存する変数
int player_score = 0;

//	ミニゲームで獲得するスコアを保存する変数
int nimiScore = 0;

int keta[6] = {
	//	スコアの桁
	0, 0, 0, 0, 0, 0
};

int kiritori[10] = {
	//	数字の画像の切り取り位置
	0, 100, 200, 300, 400, 500, 600, 700, 800, 900
};


/*
	あたり判定増強1,2
	獲得ポイントを倍加(1=1倍,2=2倍)
*/
bool PowerWidthUp = false;
bool PowerWidthUp2 = false;
bool PowerPointUp = false;
int PowerPoint = 1;

//	ミニゲームの開始条件
bool isReady = false;

int miniTimer = 60*10;