
#pragma once

//
//	�V�X�e��
//

#include "../common.h"

class System{
private:
	Texture system_image;
	Object Start[5];

public:
	System();

	void draw();
	void update(AppEnv&);

};