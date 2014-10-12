//
// アプリ雛形
// ※ファイル分割対応版
//

#include "lib/appEnv.hpp"

// ↑他の.cppファイルでは、必要なヘッダファイルを
//   適時インクルードする事


// アプリのウインドウサイズ
enum Window {
  WIDTH  = 650,
  HEIGHT = 850
};

struct Player{
	float x, y;
};

void backGround(int& scroll, Texture& bg){

	scroll -= 3;

	drawTextureBox(-325, -425, 650, 850,
		0, scroll, 650, 850,
		bg,
		Color(1, 1, 1));
}

void draw(Texture& ziki, Player& player){
	drawTextureBox(player.x, player.y, 100, 100,
		0, 0, 256, 256,
		ziki,
		Color(1, 1, 1));
}

void playerMovement(AppEnv& app_env, Player& player, float& move){
	if (app_env.isPressKey('A')) player.x -= move;
	if (app_env.isPressKey('D')) player.x += move;
	if (player.x <= -WIDTH/2) player.x = -WIDTH/2;
	if (player.x >= WIDTH/2 - 64) player.x = WIDTH/2 - 64;
}

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);

  // 背景をスクロールさせる変数
  // 背景の画像
  int scroll = 0;
  Texture bg("res/1-1.png");

  // プレイヤーの動かすための変数
  float move = 2;
  // 自機の画像
  Texture ziki("res/ziki.png");

  // プレイヤーのオブジェクトを作成
  Player player = {
	-32, -410
  };

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
    app_env.setupDraw();

	// 背景処理
	backGround(scroll, bg);

	// 自機の移動処理
	playerMovement(app_env, player, move);

	// 描画
	draw(ziki, player);

	drawPoint(0, -380, 1, Color(1, 1, 1));
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
