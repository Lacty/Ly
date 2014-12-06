//
//	タイトルStartの表示
//

#include "system.h"

//	コンストラクタ
System::System(){
	system_image = (Texture(SYSTEM_IMAGE));
}

void System::draw(){
	drawTextureBox(-512, -800, 1024, 1024,
		0, 0, 1024, 1024,
		system_image,
		Color(0, 0, 0));
}