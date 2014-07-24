//
// アプリ雛形
//

#include "appEnv.hpp"


// アプリのウインドウサイズ
enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};

// マウスが枠に入っているかの判定
bool mouse(Vec2f mouse_pos, float x, float y,
	float width, float height) {
	if (mouse_pos.x() > x){
		if (mouse_pos.x() < (x + width)){
			if (mouse_pos.y() > y){
				if (mouse_pos.y() < (y + height)){
					// 矩形の中にあるのでtrueを返す
					return true;
				}
			}
		}
	}
	//　矩形の外なのでfalseを返す
	return false;
}

float x = -20;
float y = -20;

float click_posx = 0;
float click_posy = 0;

bool click = false;

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT, false, false);

  // app_env.windowPosition(Vec2i(10, 10));

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
    app_env.setupDraw();

	Vec2f mouse_pos = app_env.mousePosition();

	// 押した瞬間
	if ((mouse(mouse_pos, x, y, 40, 40)) && (app_env.isPushButton(Mouse::LEFT))){
		click_posx = x - mouse_pos.x();
		click_posy = y - mouse_pos.y();
		click = true;
	}

	if (app_env.isPressButton(Mouse::LEFT)){
		if (click){
			x = mouse_pos.x() + click_posx;
			y = mouse_pos.y() + click_posy;
		}
	}

	if (app_env.isPullButton(Mouse::LEFT)){
		click = false;
	}


	drawFillBox(x, y, 40, 40, Color(mouse(mouse_pos, x, y, 40, 40), 1, 1));


    // 
    // ここに描画処理を書く
    //

    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
