
#pragma once

//
//	リザルト画面
//

#include "../common.h"

class Result{
private:
	Texture result_image;
	
public:
	Result();

	void draw();
	void update(int& MODE);

};