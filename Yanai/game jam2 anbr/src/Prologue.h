#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"


const int PRO_BG_MOVE = 6;
bool XXXX_hit = true;
int XXX = -512;
int X = 0;
int Y = 0;

void PrologueMove(){

	if (XXX + X <= -7650){
		//X += PRO_BG_MOVE;
		XXXX_hit = false;
	}

	if (XXXX_hit) {
		if (player.x > bg_MovePoint){
			player.x -= PLAYER_MOVE;
			X -= PRO_BG_MOVE;
		}

		if (player.x < -320){
			player.x += PLAYER_MOVE;
			X += PRO_BG_MOVE;
		}
	}

	/*
	if (!XXXX_hit){
	if (player.x + 200 >(XXX + X)){
	//player.x -= PLAYER_MOVE;
	prolog_time -= 1;
	}
	}
	*/

	/////////////////////////////////////////
	/*	êÿÇËéÊÇËÇµÇΩïîï™

	if (prolog_time < p_time){
	prolog_rect_alpha += 0.01;
	}

	*/
	///////////////////////////////////////
	if (prolog_rect_alpha > 1){
		//player.x = -300;
		//player.y = -190;
		XXXX_hit = true;
		p_time = 10 * 60;
		prolog_time = 10 * 60;
		prolog_rect_alpha = 0;
		player.x = -300;
		Kiritori_MODE = 0;
		XXX = -512;
		X = 0;
		Y = 0;

		iswhite = false;

		GameFlag = 2;
	}


	//////////////////////////////////////
	//	à√ì]ÇÃâ¸íËïîï™
	//	common.hÇ≈
	//	bool iswhite = false;
	//	êÈåæÇµÇƒÇÈÇ®

	if (player.x > 0){
		iswhite = true;
	}

	if (iswhite){
		prolog_rect_alpha += 0.01;
	}

	//	Ç‡ÇøÇÎÇÒégÇ¢èIÇÌÇ¡ÇΩÇÁiswhiteÇ
	//	falseÇ≈èâä˙âªÇÀÇÇ
	/////////////////////////////////////


}

void PrologueDraw(Texture& prologue_bg){

	drawFillBox(0, 0, 12, 12, Color(1, 1, 1));

	drawTextureBox(XXX + X, -680 + Y, 8192, 1024,
		0, 0, 8192, 1024,
		prologue_bg,
		Color(1, 1, 1));

}

void prologue_FO(){

	drawFillBox(-512, -340, 1024, 680, Color(1, 1, 1, prolog_rect_alpha));

}