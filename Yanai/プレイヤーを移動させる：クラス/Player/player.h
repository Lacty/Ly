
#pragma once

//
//	�v���C���[��\��
//

#include "../common.h"


class Player {
private:
	Object player;
	int MOVE;

public:
	Player();

	void draw(AppEnv&);
	void update(AppEnv&);
	Object get_pos() const;
};
