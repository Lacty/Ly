//
// アプリ雛形
//

#include "appEnv.hpp"
#include <ctime>

// アプリのウインドウサイズ
enum Window {
  WIDTH  = 1024,
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
  Texture kage("res/kage.png");     // 影
  int P_x = -128;                   // キャラクターの位置情報 x
  int P_y = -64;                    // キャラクターの位置情報 y
  bool right = true;                // 向きを決める変数
  float move = 0;                   // 上下運動

  // ふきだし
  Texture ranran("res/ranran.png"); // らんらん♪
  Texture sonna("res/sonna.png");   // そんなー
  int time = 0;                     // 次の吹き出し判定までのタイム
  int huki_time = 0;                // 吹き出し表示時間
  bool hukidasi = false;            // 吹き出しを表示させるための判定

  // ランダム関数
  Random random;
  random.setSeed(u_int(std::time(nullptr)));
  

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
	app_env.setupDraw();

	{//操作キャラの処理
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


		// 左右向いた時の画像切り替え
		drawTextureBox(P_x, P_y - 10, 256, 128,
			0, 0, 256, 128,
			kage,
			Color(1, 1, 1));
		// sinの振れを＋する
		move += 0.05;
		if (right){
			drawTextureBox(P_x, std::abs(std::sin(move)) * 4 + P_y, 256, 128,
				0, 0, 256, 128,
				pork_R,
				Color(1, 1, 1));
		}
		else {
			drawTextureBox(P_x, std::abs(std::sin(move)) * 4 + P_y, 256, 128,
				0, 0, 256, 128,
				pork_L,
				Color(1, 1, 1));
		}

		//　吹き出しの処理
		if (!hukidasi){
			time += 1;
			if (time > 180){
				if (random.fromFirstToLast(0, 1)) {
					time = 0;
					hukidasi = true;
				}
			}
		}
		else {
			time += 1;
			if (time > 90){
				hukidasi = false;
				time = 0;
			}
			drawTextureBox(P_x + 120, P_y + 120, 256, 128,
				0, 0, 256, 128,
				ranran,
				Color(1, 1, 1));
		}
	}

    // 
    // ここに描画処理を書く
    //

    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
