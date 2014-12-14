//
// アプリ雛形
// ※ファイル分割対応版
//

#include "common.h"
#include "System/system.h"
#include "app.h"


int main() {
	App::create();
	//AppEnv app_env(Window::WIDTH, Window::HEIGHT);

	App::app_env->bgColor(color256(150, 150, 150));

	System system;

	while (1) {
		if (!App::app_env->isOpen()) return 0;

		system.update();

		App::app_env->setupDraw();

		system.draw();

		App::app_env->update();
	}
}
