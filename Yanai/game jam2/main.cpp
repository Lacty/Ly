#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "Map.h"
#include "Player.h"


enum Window {
  WIDTH  = 1024,
  HEIGHT = 680
};



int main() {
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);

  Texture background("res/background.png");
  Texture ouzi_image("res/ouzisama.png");

  while (1) {
    if (!app_env.isOpen()) return 0;

    app_env.setupDraw();

	Map();
	MapMove();
	drawMap(background);
	drawPlayer(app_env, ouzi_image);

    app_env.update();
  }
  
}
