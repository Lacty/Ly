//
// アプリ雛形
//

#include "appEnv.hpp"


// アプリのウインドウサイズ
enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT, false, false);

  // app_env.windowPosition(Vec2i(10, 10));

  int x = -20;
  int x2 = 40;

  int move = 0;
  int move_y = 0;

  bool hit = true;
  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
    app_env.setupDraw();

	if (app_env.isPressKey('D')){
		move += 1;
	}
	if (app_env.isPressKey('A')){
		move -= 1;
	}
	if (app_env.isPressKey('W')){
		move_y += 1;
	}
	if (app_env.isPressKey('S')){
		move_y -= 1;
	}


	if ((move >= 100-40) && (move <= 140)&&(move_y <= 40)&&(move_y >= -40-40)){
		hit = false;
	}
	else { hit = true; }
	if ((move >= 60-40) && (move <= 100)&&(move_y <= 40)&&(move_y >= -40-40)){
		hit = false;
	}



	drawFillBox(x, -20, x2, 40, Color(hit, 1, 0));

	drawFillBox(-20 + move - 100, -20 + move_y, 80, 80, Color(1, 1, 1));

    // 
    // ここに描画処理を書く
    //

    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
