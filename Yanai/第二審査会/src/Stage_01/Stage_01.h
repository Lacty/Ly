
#pragma once

//
//	Stage_01
//

#include "../common.h"
#include "../Player/player.h"

class Stage_01{
private:
	Object floor[20];
	void Floor(Player& player);
	Object block[2];
	void Block(Player& player);
	Object goal;
	void Goal(Player& player, int& MODE);

	void Reset01(Player& player);
	bool reset;

public:
	Stage_01();

	void draw(Player& player);
	void update(Player& player, int& MODE);

};