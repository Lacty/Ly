﻿//
// アプリ雛形
//

#include "appEnv.hpp"

// アプリのウインドウサイズ
enum Window {
  WIDTH  = 256,
  HEIGHT = 256
};

struct Object{
	Object(float x, float y, float radius, float division,
	float gr, float vy)
	{
		this->x = x;
		this->y = y;
		this->radius = radius;
		this->division = division;
		this->gr = gr;
		this->vy = vy;
	}
	float x, y;
	float radius;      // 半径
	float division;    // この値が大きいと円が滑らかになる
	float gr, vy;
};

Object earth(0, 0, 50, 300, 0, 0);
Object player(0, 55, 5, 100, 0.4, 0);

void PlayerMove(AppEnv& app_env, float& ground, float& angle){
	player.x = ground * cos(angle) / 2;
	player.y = ground * sin(angle) / 2;
	
	// 角度を進める
	const if (app_env.isPressKey('D')){ angle -= 0.03; }
	const if (app_env.isPressKey('A')){ angle += 0.03; }

	// ジャンプさせる
	const if (app_env.isPushKey(GLFW_KEY_SPACE)){ player.vy = -5; }
}

void PlayerGravity(AppEnv& app_env, float& ground){
	ground -= player.vy;
	player.vy += player.gr;

	if (ground <= 110){ ground = 110; }
}

void draw(){
	drawFillCircle(earth.x, earth.y, earth.radius, earth.radius,
		          earth.division, color256(200, 200, 200));

	drawFillCircle(player.x, player.y, player.radius, player.radius,
		player.division, Color(0, 0, 0));
}

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT, false, false);
  app_env.bgColor(Color(1, 1, 1));

  // app_env.windowPosition(Vec2i(10, 10));

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
    app_env.setupDraw();


	float angle = 1.55;                                  // キャラの角度（位置）
	const float ground = earth.radius + player.radius/2;     // 中心円の半径＋キャラクターの半径
	                                                   // 変化しないのでconstにしてみた＆表記方法を変更

	PlayerMove(app_env, ground, angle);

	PlayerGravity(app_env, ground);

	draw();

    // 
    // ここに描画処理を書く
    //

    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}