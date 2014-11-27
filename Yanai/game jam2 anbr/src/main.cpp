#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "GamePage.h"


enum Window {
	WIDTH = 1024,
	HEIGHT = 680
};



int main() {
	AppEnv app_env(Window::WIDTH, Window::HEIGHT,
		false, false);

	Texture background("res/background.png");
	Texture ouzi_image("res/ouzisama.png");
	Texture hana("res/hana_test.png");
	Texture title_bg("res/title_bg.png");
	Texture prologue_bg("res/prologue_bg.png");
	Texture result_bg("res/result_bg.png");
	Texture umbrella1("res/umbrella1.png");
	Texture umbrella2("res/umbrella2.png");
	Texture number_image("res/number.png");
	Texture tyuke_image("res/tyuke.png");
	Texture castle_image("res/Castle.png");
	Texture show_image("res/show.png");
	Texture himesama("res/himesama.png");
	Texture HappyEnd("res/happy_end.png");
	Texture BadEnd("res/bad_end.png");



	while (1) {
		if (!app_env.isOpen()) return 0;
		app_env.setupDraw();

		// 初期化
		prologFlag = true;
		player.x = -300;
		player.y = -190;
		box_x = -512;
		box_y = -340;
		play_point = 0;
		prolog_time = p_time;
		prolog_rect_alpha = 0;
		GameFlag = 0;

		while (1) {
			if (!app_env.isOpen()) return 0;

			app_env.setupDraw();

			//if (app_env.isPushKey(GLFW_KEY_ENTER)) GameFlag++;
			Game(app_env, background, ouzi_image, hana,
				title_bg, prologue_bg, result_bg, umbrella1,
				umbrella2, number_image, tyuke_image, castle_image, show_image,
				himesama, HappyEnd, BadEnd);

			if (GameFlag == 4) break;

			app_env.update();
		}

		app_env.update();
	}

}

////////////////////////////////////////////////////////////////////





//					汚いよ！




///////////////////////////////////////////////////////////////////
