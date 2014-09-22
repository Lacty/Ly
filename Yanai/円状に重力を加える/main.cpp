//
// アプリ雛形
//

#include "appEnv.hpp"

#define PI    3.14159265   // 円周率

// アプリのウインドウサイズ
enum Window {
  WIDTH  = 256,
  HEIGHT = 256
};

struct Object{
	Object(float x, float y, float radius, float division)
	{
		this->x = x;
		this->y = y;
		this->radius = radius;
		this->division = division;
	}
	float x, y;
	float radius;
	float division;
};

Object earth(0, 0, 50, 300);
Object player(0, 55, 5, 100);

float angle = 1.55;
float ground = 110;
float gr = 0.15;
float vy = 0.0;
void PlayerMove(AppEnv& app_env){
	player.x = ground * cos(angle) / 2;
	player.y = ground * sin(angle) / 2;
	
	// 角度を進める
	if (app_env.isPressKey('D')){ angle -= 0.03; }
	if (app_env.isPressKey('A')){ angle += 0.03; }

	// ジャンプさせる
	if (app_env.isPushKey(GLFW_KEY_SPACE)){ vy = -3.5; }
}

void PlayerGravity(AppEnv& app_env){
	ground -= vy;
	vy += gr;

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

	PlayerMove(app_env);

	PlayerGravity(app_env);

	draw();


    // 
    // ここに描画処理を書く
    //

    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
