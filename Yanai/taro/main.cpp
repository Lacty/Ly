//
// アプリ雛形
// ※ファイル分割対応版
//

#include "lib/defines.hpp"
// ↑これは必ず最初にincludeする

#include "lib/appEnv.hpp"
#include <iostream>
// ↑必要なヘッダファイルは適時インクルードする

#include "nimiGame.h"


// アプリのウインドウサイズ
enum Window {
  WIDTH  = 1000,
  HEIGHT = 600
};

// アプリウインドウの準備
AppEnv app_env(Window::WIDTH, Window::HEIGHT,
	false, false);

#include "score.h"

// 
// メインプログラム
// 
int main() {
	//	数字の画像
	Texture number_image("res/num.png");

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
    app_env.setupDraw();


	nimiGame(app_env, number_image);

	std::cout << nimiScore << std::endl;

    //
    // 描画処理はここでおこなう
    // 
    
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
