//
// アプリ雛形
// ※ファイル分割対応版
//

#include "lib/appEnv.hpp"

// ↑他の.cppファイルでは、必要なヘッダファイルを
//   適時インクルードする事


// アプリのウインドウサイズ
enum Window {
  WIDTH  = 512,
  HEIGHT = 256
};

struct Object{
	Object(int x, int y, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	int x, y;
	int width, height;
};

Object player(-10, -10, 10, 10);

void PlayerMove(AppEnv& app_env, Object& player){
	if (app_env.isPressKey('D')){ player.x += 1; }
	if (app_env.isPressKey('A')){ player.x -= 1; }
}

int mode = 1;

void draw(){
	// 地面
	drawLine(-256, -10, 
		    256, -10,
			1, 
			Color(0, 0, 0));


	// キャラクター(modeで変更)
	if (mode == 1){
		drawFillBox(player.x, player.y,
			player.width, player.height,
			Color(0, 1, 1));
	}

	if (mode == 2){
		drawFillBox(player.x, player.y,
			player.width, player.height,
			Color(1, 0, 1));
	}
}

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);
  app_env.bgColor(Color(1, 1, 1));

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
    app_env.setupDraw();

	PlayerMove(app_env, player);

	if (app_env.isPressKey('R')){ mode = 2; }
	if (app_env.isPressKey('E')){ mode = 1; }

	draw();
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
