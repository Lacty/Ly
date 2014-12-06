
#pragma once

//
//	エネミーを表示
//

#include "../common.h"

class Enemy{
private:
	Object enemy;

public:
	Enemy();

	void draw(AppEnv&);
	void update(AppEnv&, Object&);
};