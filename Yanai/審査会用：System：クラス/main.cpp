//
// アプリ雛形
// ※ファイル分割対応版
//

#include "common.h"
#include "System/system.h"


int main() {
	AppEnv app_env(Window::WIDTH, Window::HEIGHT);

	System system;

	while (1) {
		if (!app_env.isOpen()) return 0;
		app_env.bgColor(color256(150, 150, 150));

		system.update(app_env);

		app_env.setupDraw();

		system.draw();

		app_env.update();
	}
}
