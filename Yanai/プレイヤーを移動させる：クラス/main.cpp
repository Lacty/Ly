//
// アプリ雛形
// ※ファイル分割対応版
//

#include "common.h"

#include "player/player.h"
#include "enemy/enemy.h"


int main() {
	AppEnv app_env(Window::WIDTH, Window::HEIGHT);

	Player player;
	Enemy enemy;

	while (1) {
		if (!app_env.isOpen()) return 0;
		player.update(app_env);
		enemy.update(app_env, player.get_pos());

		app_env.setupDraw();

		player.draw(app_env);
		enemy.draw(app_env);

		app_env.update();
	}
}
