#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"
#include "Player.h"
#include "Map.h"
#include "Flower.h"
#include "Title.h"
#include "Prologue.h"
#include "Result.h"
#include "UserInterface.h"
#include "Score.h"


void Game(AppEnv& app_env, Texture& background,
	Texture& ouzi_image, Texture& hana,
	Texture& title_bg, Texture& prologue_bg,
	Texture& result_bg, Texture& umbrella1,
	Texture& umbrella2, Texture& number_image,
	Texture& tyuke_image, Texture& castle_image, Texture& show_image,
	Texture& himesama, Texture& HappyEnd, Texture& BadEnd){

	switch (GameFlag)
	{
		// タイトル
	case 0:
		TitleDraw(app_env, title_bg);
		break;
		// プロローグ
	case 1:
		PrologueMove();
		PrologueDraw(prologue_bg);
		drawPlayer(app_env, ouzi_image);
		prologue_FO();
		break;
		// 本編
	case 2:
		MapMove();
		UmbrellaMove();
		drawMap(background, tyuke_image, castle_image, show_image, himesama);
		drawPlayer(app_env, ouzi_image);
		drawFlower(hana);
		//drawUmbrella(umbrella1, umbrella2);
		//drawPlayPoint(number_image);
		break;
		// 結果画面
	case 3:
		prologFlag = true;
		ResultMove();
		drawResult(app_env, HappyEnd, BadEnd);
		break;
	}
}

