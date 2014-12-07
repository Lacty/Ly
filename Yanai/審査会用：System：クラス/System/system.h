
#pragma once

//
//	ƒVƒXƒeƒ€
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