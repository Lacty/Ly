
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "nimiPlayer.h"
#include "nimiMarron.h"

//	ƒQ[ƒ€‚Ì•`‰æ
void nimiGame(AppEnv& app_env){
	app_env.bgColor(Color(1, 1, 1));

	drawMarron(app_env);
	drawPlayer(app_env);
}