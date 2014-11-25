#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "common.h"
#include "Player.h"
#include "Map.h"

void Game(){

	switch (GameFlag)
	{
		// タイトル
	case 0:
		//PrologueMove();
		//PrologueDraw();
		break;
		// ノベル(プロローグ)
	case 1:
		break;
		// 本編
	case 2:
		break;
		// 結果画面
	case 3:
		break;
	}

}

