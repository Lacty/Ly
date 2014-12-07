//
//	タイトルStartの表示
//

#include "system.h"
#include "../isHit.h"

using namespace collision;

//	コンストラクタ
System::System(){
	system_image = (Texture(SYSTEM_IMAGE));
	Start[0] = { 200, 0, 100, 100, 0, 0, 100, 100, color256(0, 0, 0) };			// S
	Start[1] = { -200, -180, 100, 100, 100, 0, 100, 100, color256(0, 0, 0) };	// t
	Start[2] = { 80, -200, 100, 100, 200, 0, 100, 100, color256(0, 0, 0) };		// a
	Start[3] = { 50, 130, 100, 100, 300, 0, 100, 100, color256(0, 0, 0) };		// r
	Start[4] = { -150, 50, 100, 100, 400, 0, 100, 100, color256(0, 0, 0) };		// t
}

void System::draw(){
	for (int i = 0; i < 5; i++){
		drawTextureBox(Start[i].x, Start[i].y, Start[i].width, Start[i].height,
			Start[i].start_tx, Start[i].start_ty,
			Start[i].texture_width, Start[i].texture_height,
			system_image,
			Start[i].col);
	}
}

void System::update(AppEnv& app_env){
	Vec2f mouse_pos = app_env.mousePosition();

	bool isClick = false;
	float click_posx;
	float click_posy;

	
	for (int i = 0; i < 5; i++){

		//	マウスが矩形に当たっているかの判定
		if (point_to_rect(mouse_pos.x(), mouse_pos.y(), Start[i].x, Start[i].y,
			Start[i].width, Start[i].height)){

			Start[i].col = color256(100, 100, 255);

			if (app_env.isPushButton(Mouse::LEFT)){
				isClick = true;
				click_posx = Start[i].x - mouse_pos.x();
				click_posy = Start[i].y - mouse_pos.y();
			}

			if (app_env.isPressButton(Mouse::LEFT)){
				if (isClick){
					Start[i].x = mouse_pos.x() + click_posx;
					Start[i].y = mouse_pos.y() + click_posy;
					Start[i].col = color256(0, 0, 0);
				}
			}

			if (app_env.isPullButton(Mouse::LEFT)){
				//isClick = false;
			}

		}
		else {
			Start[i].col = color256(0, 0, 0);
		}
	}
	

	/*
	//	マウスが矩形に当たっているかの判定
	if (point_to_rect(mouse_pos.x(), mouse_pos.y(), Start[0].x, Start[0].y,
		Start[0].width, Start[0].height)){

		Start[0].col = color256(100, 100, 255);

		if (app_env.isPushButton(Mouse::LEFT)){
			isClick = true;
			click_posx = Start[0].x - mouse_pos.x();
			click_posy = Start[0].y - mouse_pos.y();
		}

		if (app_env.isPressButton(Mouse::LEFT)){
			if (isClick){
				Start[0].x = mouse_pos.x() + click_posx;
				Start[0].y = mouse_pos.y() + click_posy;
				Start[0].col = color256(0, 0, 0);
			}
		}

		if (app_env.isPullButton(Mouse::LEFT)){
			//isClick = false;
		}

	}
	else {
		Start[0].col = color256(0, 0, 0);
	}
	*/
}