
#pragma once

//
//	システム
//

#include "../common.h"
#include "../Title/title.h"
#include "../Stage/stage.h"
#include "../Stage_01/Stage_01.h"
#include "../Player/player.h"
#include "../Result/result.h"

class System{
private:
	//	システム用画像
	Texture system_image;

	Title title;
	Stage stage;
	Stage_01 stage_01;
	Player player;
	Result result;

	//	シーン切り替え用変数
	int MODE;

public:
	System();

	void draw();
	void update();

};
