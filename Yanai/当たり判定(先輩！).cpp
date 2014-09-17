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
  HEIGHT = 512
};

bool Hit(int p_x1, int p_y1, int p_x2, int p_y2,
	int b_x1, int b_y1, int b_x2, int b_y2){
	if (p_x1 + p_x2 > b_x1){
		if (p_x1 < b_x1 + b_x2){
			if (p_y1 + p_y2 > b_y1){
				if (p_y1 < b_y1 + b_y2){
					// 矩形にあたっているのでtrueを返す
					return true;
				}
			}
		}
	}
	// 矩形の外なのでfalseを返す
	return false;
}
// プレイヤーの構造体
struct Player {
	int x1, y1,
		x2, y2;
};

//　プレイヤーの構造体
struct Block {
	int x1, y1,
	    x2, y2;
};

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);

  // 移動する(プレイヤー)オブジェクトを用意
  Player player = {
	  0, 0,
	  20, 20
  };

  // (ブロック)オブジェクトを用意
  Block block = {
	  0, 0,
	  40, 40
  };

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
	app_env.bgColor(Color(1, 1, 1));
    
    // 描画準備
    app_env.setupDraw();

	if (app_env.isPressKey('D')){ player.x1 += 2; }
	if (app_env.isPressKey('A')){ player.x1 -= 2; }
	if (app_env.isPressKey('W')){ player.y1 += 2; }
	if (app_env.isPressKey('S')){ player.y1 -= 2; }

	drawFillBox(block.x1, block.y1, block.x2, block.y2, Color(1, 0, 1));
    
	drawFillBox(player.x1, player.y1, player.x2, player.y2,
		Color(0, Hit(player.x1, player.y1, player.x2, player.y2, block.x1, block.y1, block.x2, block.y2), 1));


    //
    // 描画処理はここでおこなう
    // 
    
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
