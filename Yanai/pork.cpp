//
// アプリ雛形
//

#include "appEnv.hpp"


// アプリのウインドウサイズ
enum Window {
	WIDTH = 1600,
	HEIGHT = 900
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
	Texture pork_R("res/pork3.png");          // 右向きの画像
	Texture pork_L("res/pork2.png");          // 左向きの画像
	Texture kage("res/kage.png");             // 影
	float P_x = -600;                           // キャラクターの位置情報 x
	float P_y = -200;                           // キャラクターの位置情報 y
	int P_x2 = 256;
	int P_y2 = 128;
	bool right = true;                        // 向きを決める変数
	float move = 0;                           // 上下運動
	Texture coment_butagoyane("res/coment_butagoyane.png"); // ここが新しい豚小屋ね
	Texture kusoge("res/kusoge.png");         // くそげ
	Texture nitya_R("res/pork4.png");         //ニチャァ
	Texture nitya_L("res/pork5.png");
	Texture nityaa("res/nityaa.png");         // 吹き出しニチャァ

	// 背景・豚小屋
	Texture ground("res/ground.png");         // 地面
	Texture butagoya("res/butagoya.png");     // 豚小屋
	Texture cloud_1("res/cloud_1.png");       // 雲
	float cloud_move = 0;                     // 雲浮遊
	Texture start_rogo("res/start_rogo.png"); // startロゴ
	Texture exit("res/exit.png");             // exitロゴ
	Texture a_d("res/A,D.png");

	// 隕石
	Texture meteo_a("res/meteo_a.png");       // 隕石
	Texture fire("res/fire.png");
	Texture fire_under("res/fire_under.png");
	bool meteo_mode = false;                  // 隕石を落とすか？の判定
	int meteo_move = 0;                       // 隕石落下速度
	Texture bakuhatu("res/bakuhatu.png");     // 落下後の爆発
	Texture bakuhatu2("res/bakuhatu2.png");   // 落下後の爆発２
	Texture meteo_wind_r("res/meteo_wind_r1.png"); // 爆風
	Texture meteo_wind_l("res/meteo_wind_l1.png");
	Texture gareki("res/gareki.png");         // がれき

	// 重力
	int v = 0;

	while (1) {
		// アプリウインドウが閉じられたらプログラムを終了
		if (!app_env.isOpen()) return 0;

		// 描画準備
		app_env.setupDraw();

		{ // 背景
			drawTextureBox(-830, -400, 2048, 1024,
				0, 0, 2048, 1024,
				ground,                     // 地面
				Color(1, 1, 1));

			if (meteo_move < 500){
				drawTextureBox(270, -265, 450, 450,
					0, 0, 512, 512,
					butagoya,               // 豚小屋
					Color(1, 1, 1));

				drawTextureBox(380, std::sin(cloud_move + 10) * 3 + 100, 256, 256,
					0, 0, 256, 256,
					start_rogo,             // スタートロゴ
					Color(1, 1, 1));
			}

			cloud_move += 0.04;
			drawTextureBox(0, std::sin(cloud_move) * 5 + 200, 256, 256,
				0, 0, 256, 256,
				cloud_1,
				Color(1, 1, 1));

			drawTextureBox(-450, std::sin(cloud_move + 1) * 5 + 170, 256, 256,
				0, 0, 256, 256,
				cloud_1,
				Color(1, 1, 1));

			drawTextureBox(-750, std::sin(cloud_move + 4) * 5 + 170, 256, 256,
				0, 0, 256, 256,
				cloud_1,
				Color(1, 1, 1));
		}

		{   //操作キャラの処理

			if ((app_env.isPressKey('D')) && (meteo_move < 500)) {  // Dを押したら右に移動
				P_x += 1;
				right = true;
			}
			if ((app_env.isPressKey('A')) && (meteo_move < 500)) {  // Aを押したら左に移動
				P_x -= 1;
				right = false;
			}

			// 影
			drawTextureBox(P_x, P_y - 10, 256, 128,
				0, 0, 256, 128,
				kage,
				Color(1, 1, 1));

			// 左右向いた時の画像切り替え
			// sinの振れ
			move += 0.05;
			if (meteo_move < 2200){
				if (right){
					drawTextureBox(P_x, std::abs(std::sin(move)) * 4 + P_y, P_x2, P_y2,
						0, 0, 256, 128,
						pork_R,
						Color(1, 1, 1));
				}
				else {
					drawTextureBox(P_x, std::abs(std::sin(move)) * 4 + P_y, P_x2, P_y2,
						0, 0, 256, 128,
						pork_L,
						Color(1, 1, 1));
				}
			}
			else if (right){
				drawTextureBox(P_x, std::abs(std::sin(move)) * 4 + P_y, P_x2, P_y2,
					0, 0, 256, 128,
					nitya_R,
					Color(1, 1, 1));
			}
			else {
				drawTextureBox(P_x, std::abs(std::sin(move)) * 4 + P_y, P_x2, P_y2,
					0, 0, 256, 128,
					nitya_L,
					Color(1, 1, 1));
			}

			// 吹き出しニチャァ
			if (meteo_move >2200){
				drawTextureBox(P_x + 100, -100, 256, 256,
					0, 0, 256, 256,
					nityaa,
					Color(1, 1, 1));
			}

			// 豚小屋に近づいたら吹き出し　*右を向いていて
			if (right){
				if ((P_x >= -250) && (P_x <= -150)){
					drawTextureBox(P_x + 100, -80, 256, 256,
						0, 0, 256, 256,
						coment_butagoyane,
						Color(1, 1, 1));
				}
			}

			// くそげ
			if (P_x <= -860){
				drawTextureBox(P_x + 140, -80, 256, 256,
					0, 0, 256, 256,
					kusoge,
					Color(1, 1, 1));
			}

			// 左端にいったらEXIT
			if (P_x <= -1000){
				app_env.flushInput();
				return 0;
			}
		}

		{ // 隕石の処理
			if (P_x > -180){
				meteo_mode = true;
			}

			// 隕石落下
			if (meteo_mode){
				meteo_move += 10;
				if (meteo_move < 500){
					drawTextureBox(230, 200 - meteo_move, 512, 512,
						0, 0, 512, 512,
						meteo_a,
						Color(1, 1, 1));
					drawTextureBox(170, 350 - meteo_move, 600, 600,
						0, 0, 512, 512,
						fire,
						Color(1, 1, 1));
					drawTextureBox(230, 130 - meteo_move, 512, 512,
						0, 0, 512, 512,
						fire_under,
						Color(1, 1, 1));
				}
			}


			// 隕石落下後の処理
			if ((meteo_move > 500) && (meteo_move < 750)){
				drawTextureBox(270, -265, 512, 512,
					0, 0, 512, 512,
					bakuhatu,
					Color(1, 1, 1));
				drawTextureBox(130, -240, 400, 400,
					0, 0, 512, 512,
					meteo_wind_l,
					Color(1, 1, 1));
			}
			else if ((meteo_move > 750) && (meteo_move < 1100)){
				drawTextureBox(230, -265, 550, 550,
					0, 0, 512, 512,
					bakuhatu,
					Color(1, 1, 1));
				drawTextureBox(100, -240, 440, 440,
					0, 0, 512, 512,
					meteo_wind_l,
					Color(1, 1, 1));
			}
			else if ((meteo_move > 1100) && (meteo_move < 1600)){
				drawTextureBox(200, -265, 630, 630,
					0, 0, 512, 512,
					bakuhatu,
					Color(1, 1, 1));
				drawTextureBox(0, -240, 512, 512,
					0, 0, 512, 512,
					meteo_wind_l,
					Color(1, 1, 1));
			}
			else if (meteo_move > 1600){
				drawTextureBox(270, -256, 512, 512,
					0, 0, 512, 512,
					gareki,
					Color(1, 1, 1));
			}

		}

		{  //　状況・アドバイスコメント欄

			// Black長方形
			drawFillBox(-800, -450, 1600, 150, Color(0, 0, 0));

			// ←EXIT
			drawTextureBox(-800, -440, 512, 128,
				0, 0, 512, 128,
				exit,
				Color(1, 1, 1));
			//　AとDで移動可能だよ！
			drawTextureBox(-200, -440, 512, 128,
				0, 0, 512, 128,
				a_d,
				Color(1, 1, 1));
		}

		//　ブラックアウト
		drawFillBox(-800, -450, 1600, 900, Color(0, 0, 0));
		
		// 
		// ここに描画処理を書く
		//


		// 画面更新
		app_env.update();
	}

	// アプリ終了
}
