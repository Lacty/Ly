//
//	�V�X�e��
//

#include "system.h"
#include "../app.h"


//	�R���X�g���N�^
System::System(){
	system_image = (Texture(SYSTEM_IMAGE));
	MODE = 0;
}

//	System�̕`�敔��
void System::draw(){
	switch (MODE){
	case 0:{
		title.draw(system_image);
	}break;

	case 1:{
		stage.draw(system_image);
	}break;

	case 2:{
		stage_01.draw(player);
	}break;

	case 14:{
		result.draw();
	}break;
	}
}

//	System�̏�������
void System::update(){
	switch (MODE){
	case 0:{
		title.update(MODE);
	}break;

	case 1:{
		stage.update(MODE);
	}break;

	case 2:{
		stage_01.update(player, MODE);
	}break;

	case 14:{
		result.update(MODE);
	}break;
	}
}