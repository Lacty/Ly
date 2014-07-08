//
// アプリ雛形
//

#include "appEnv.hpp"


// アプリのウインドウサイズ
enum Window {
	WIDTH = 1024,
	HEIGHT = 512
};

// 
// メインプログラム
// 
int main() {
	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT, false, false);
	app_env.bgColor(Color(1, 1, 1));
	// app_env.windowPosition(Vec2i(10, 10));

	// 自キャラ情報
	Texture pork_R("res/pork_R.png"); // 右向きの画像
	Texture pork_L("res/pork_L.png"); // 左向きの画像
	int P_x = -128;                   // キャラクターの位置情報 x
	int P_y = -64;                    // キャラクターの位置情報 y
	bool right = true;                // 向きを決める変数

	while (1) {
		// アプリウインドウが閉じられたらプログラムを終了
		if (!app_env.isOpen()) return 0;

		// 描画準備
		app_env.setupDraw();

		// Dを押したら右に移動
		if (app_env.isPressKey('D')){
			P_x += 1;
			right = true;
		}
		// Aを押したら左に移動
		if (app_env.isPressKey('A')){
			P_x -= 1;
			right = false;
		}

		// 左右向いた画像の切り替え
		if (right){
			drawTextureBox(P_x, P_y, 256, 128,
				0, 0, 256, 128,
				pork_R,
				Color(1, 1, 1));
		}
		else{
			drawTextureBox(P_x, P_y, 256, 128,
				0, 0, 256, 128,
				pork_L,
				Color(1, 1, 1));
		}

		// 
		// ここに描画処理を書く
		//


		// 画面更新
		app_env.update();
	}

	// アプリ終了
}
