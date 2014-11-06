//
// アプリ雛形
// ※ファイル分割対応版
//

#include "lib/defines.hpp"
// ↑これは必ず最初にincludeする

#include "lib/appEnv.hpp"
// ↑必要なヘッダファイルは適時インクルードする

// アプリのウインドウサイズ
enum Window {
	WIDTH = 1000,
	HEIGHT = 600
};

// アプリウインドウの準備
AppEnv app_env(Window::WIDTH, Window::HEIGHT,
	false, false);

//プレイヤー関係
#include "player.h"
//マップ配置
#include "map.h"
//エフェクト関係
#include "efect.h"

// 
// メインプログラム
// 
int main() {

	//エフェクト初期化
	setupEfect();

	while (1) {
		// アプリウインドウが閉じられたらプログラムを終了
		if (!app_env.isOpen()) return 0;

		// 描画準備
		app_env.setupDraw();

		//エフェクト表示
		drawEfect();

		//マップ配置
		map_set();

		//自機関数呼び出し
		player();


		// 画面更新
		app_env.update();
	}

	// アプリ終了
}
