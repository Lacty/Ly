//
// アプリ雛形
// ※ファイル分割対応版
//

#include "lib/appEnv.hpp"

// ↑他の.cppファイルでは、必要なヘッダファイルを
//   適時インクルードする事


// アプリのウインドウサイズ
enum Window {
  WIDTH  = 1600,
  HEIGHT = 900
};


// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);
  app_env.bgColor(Color(1, 1, 1));
  // app_env.windowPosition(Vec2i(10, 10));

  // 自キャラ情報
  Texture pork_R("res/pork3.png");                          // 右向きの画像
  Texture pork_L("res/pork2.png");                           // 左向きの画像
  Texture kage("res/kage.png");                                // 影
  Texture wing_R("res/wing_R.png");                         // 羽right
  Texture wing_L("res/wing_L.png");                         // 羽left
  float P_x = -600;                                                      // キャラクターの位置情報 x
  float P_y = -200;                                                      // キャラクターの位置情報 y
  int P_x2 = 256;
  int P_y2 = 128;
  bool right = true;                                                     // 向きを決める変数
  float move = 0;                                                         // 上下運動
  Texture coment_butagoyane("res/coment_butagoyane.png"); // ここが新しい豚小屋ね
  Texture kusoge("res/kusoge.png");                        // くそげ
  Texture nitya_R("res/pork4.png");                          //ニチャァ
  Texture nitya_L("res/pork5.png");
  Texture nityaa("res/nityaa.png");                            // 吹き出しニチャァ

  // 背景・豚小屋
  Texture ground("res/ground.png");                       // 地面
  Texture butagoya("res/butagoya.png");                // 豚小屋
  Texture cloud_1("res/cloud_1.png");                     // 雲
  float cloud_move = 0;                                             // 雲浮遊
  Texture start_rogo("res/start_rogo.png");             // startロゴ
  Texture exit("res/exit.png");                                    // exitロゴ
  Texture a_d("res/A,D.png");
  int Life = 4;                                       // Life変数

  // 隕石
  Texture meteo_a("res/meteo_a.png");                  // 隕石
  Texture fire("res/fire.png");
  Texture fire_under("res/fire_under.png");
  bool meteo_mode = false;                                     // 隕石を落とすか？の判定
  int meteo_move = 0;                                              // 隕石落下速度
  Texture bakuhatu("res/bakuhatu.png");               // 落下後の爆発
  Texture bakuhatu2("res/bakuhatu2.png");           // 落下後の爆発２
  Texture meteo_wind_r("res/meteo_wind_r1.png"); // 爆風
  Texture meteo_wind_l("res/meteo_wind_l1.png");
  Texture gareki("res/gareki.png");                          // がれき

  // ブラックアウト用の変数
  int blackout = 0;

  // 重力
  int v = 0;

  // ステージせんたく
  Texture stage_sellect("res/stage_sellect.png");

  // stage_1
  Texture stage_1("res/stage_1.png");

  //Enter押してステージ決定
  Texture enter_to_sellect_stage("res/enter_to_sellect_stage.png");

  // 豚小屋をなくしたらん豚は,新たな豚小屋を目指すのだった
  Texture select_comment_1("res/select_comment_1.png");

  // Enter
  Texture enter("res/Enter.png");
  bool click_enter = false;

  // らんらん♪
  Texture ranran("res/ranran.png");

  // Flag
  Texture flag("res/flag.png");

  int comment_move = 0;

  float vy = 0.0;
  float g = 0.1;

  bool gravity = false;
  bool is_Jump = false;

  bool Ya = false;
  float Ya_y = 0;
  float Ya_vy = 10;
  float Ya_g = 0.18;
  bool Ya_Atk = false;

  float B_x = -800;
  float B_y = -250;
  float block_x = 50;

  bool block1314 = false;
  float bvy = 0.0;
  float B_y13 = -200;
  float B_y14 = -200;

  float bbvy = 0.0;
  float B_y17 = -200;
  float B_y18 = -200;
  float B_y19 = -200;
  float B_y20 = -200;

  bool is_Punch = false;

  bool swich = false;
  float S_y = -205;

  float bun_move1 = 0;
  float bun_move2 = 0;
  float bun_move3 = 0;

  bool is_Ly = false;
  float ly_x = 800;

  Texture start_flag("res/start_flag.png");
  Texture tree("res/tree.png");
  Texture ya("res/ya.png");
  Texture block("res/block.png");
  Texture dokan("res/dokan.png");
  Texture ly("res/Ly.png");
  Texture bun("res/bu-n.png");
  Texture don("res/don.png");
  Texture ranran_hatena("res/ranran_hatena.png");
  Texture swich1("res/Swich1.png");
  Texture swich2("res/Swich2.png");

  Texture clear_logo("res/clear_logo.png");
  Texture clear_sellect("res/clear_sellect.png");

  Texture youdead("res/you_dead.png");

  Texture X4("res/X4.png");
  Texture X3("res/X3.png");
  Texture X2("res/X2.png");
  Texture X1("res/X1.png");
  Texture X0("res/X0.png");

  int timer = 0;

  right = true;

  int MODE = 0;

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
    
    // 描画準備
    app_env.setupDraw();


	switch (MODE){
	case 0:
	{
		{   // 背景
			// 地面
			drawTextureBox(-830, -400, 2048, 1024,
			0, 0, 2048, 1024,
			ground,
			Color(1, 1, 1));

			if (meteo_move < 500){

				// 豚小屋
				drawTextureBox(270, -265, 450, 450,
					0, 0, 512, 512,
					butagoya,
					Color(1, 1, 1));

				// スタートロゴ
				drawTextureBox(380, std::sin(cloud_move + 10) * 3 + 100, 256, 256,
					0, 0, 256, 256,
					start_rogo,
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
				  P_x += 2;
				  right = true;
			  }
			  if ((app_env.isPressKey('A')) && (meteo_move < 500)) {  // Aを押したら左に移動
				  P_x -= 2;
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
			  if (meteo_move > 2200){
				  drawTextureBox(P_x + 100, -100, 256, 256,
					  0, 0, 256, 256,
					  nityaa,
					  Color(1, 1, 1));
			  }

			  // 豚小屋に近づいたら吹き出し　*右を向いていて
			  if (right){
				  if ((P_x >= -250) && (P_x <= -150)){
					  if (meteo_move < 2000){
						  drawTextureBox(P_x + 100, -80, 256, 256,
							  0, 0, 256, 256,
							  coment_butagoyane,
							  Color(1, 1, 1));
					  }
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
			  if (meteo_move > 2600){
				  blackout += 1;
				  drawFillBox(-800, -450, 1600, 900, color256(0, 0, 0, blackout));
			  }
			  if (meteo_move >= 5000){
				  MODE = 1;
				  P_x = -650;
			  }

			  if (app_env.isPressKey('Z')){
				  MODE = 1;
				  P_x = -650;
			  }

			  if (app_env.isPressKey('X')){
				  MODE = 4;
				  P_x = -650;
			  }
	}
	break;

	case 1:
	{
			//
			//操作キャラの処理
			//

			// Enterを押されるまで実行
			if (click_enter){
				if (app_env.isPressKey('D')) {  // Dを押したら右に移動
					P_x += 3;
					right = true;
				}
				if (app_env.isPressKey('A')) {  // Aを押したら左に移動
					P_x -= 3;
					right = false;
				}
			}


			// 影
			drawTextureBox(P_x, P_y - 10, 256, 128,
				0, 0, 256, 128,
				kage,
				Color(1, 1, 1));

			// 左右向いた時の画像
			move += 0.05;// sinの振れ
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

			// 画面外に出ないようにする
			if (P_x <= -900){ P_x += 3; }
			if (P_x >= 660){ P_x -= 3; }

			//
			//【ロゴ】ステージ選択
			//
			drawTextureBox(-256, 200, 512, 256,
				0, 0, 512, 256,
				stage_sellect,
				Color(1, 1, 1));

			//
			//キャラクターコメント
			//
			if ((P_x < -20) && (P_x > -280)){
				drawTextureBox(P_x + 160, -100, 256, 256,
					0, 0, 256, 256,
					ranran,
					Color(1, 1, 1));
			}


			//
			//旗
			//

			drawTextureBox(-140, -220, 256, 256,
				0, 0, 256, 256,
				flag,
				Color(1, 1, 1));
			drawTextureBox(-140, -280, 256, 64,
				0, 0, 256, 64,
				stage_1,
				Color(1, 1, 1));



			//
			//コメント欄
			//

			// Black長方形
			drawFillBox(-800, -450, 1600, 150, Color(0, 0, 0));

			// Enter押したらコメントを消す
			if (app_env.isPushKey(GLFW_KEY_ENTER)){
				app_env.flushInput();
				click_enter = true;
			}

			comment_move -= 5;
			if (comment_move < -4810){
				comment_move == -4810;
			}

			// comment_moveが一定の範囲かつ
			// Enterを押されるまで実行
			if ((comment_move < 0) && (comment_move > -4800)){
				if (!click_enter){

					right = true;

					// Enter 画像
					drawTextureBox(540, -300, 256, 128,
						0, 0, 256, 128,
						enter,
						Color(1, 1, 1));

					//　コメント　画像
					drawTextureBox(600 + comment_move, -450, 3500, 210,
						0, 0, 4096, 256,
						select_comment_1,
						Color(1, 1, 1));
				}
				else {
					comment_move == -4800;
				}
			}
			else {
				click_enter = true;
			}

			//Enterを押してステージ決定
			if ((P_x < -20) && (P_x > -280)){
				drawTextureBox(-450, -430, 1024, 128,
					0, 0, 1024, 128,
					enter_to_sellect_stage,
					Color(1, 1, 1));
			}

			//
			//ステージ１にブレイク
			//
			if ((P_x < -20) && (P_x > -280)){
				if (app_env.isPressKey(GLFW_KEY_ENTER)){ 
					MODE = 2;

					// Stage1の変数の初期化
					P_x = -750;
					P_y = -200;
					vy = 0;

					right = true;

					B_x = -800;
					B_y = -250;
					block_x = 50;
					block1314 = false;
					bvy = 0.0;
					B_y13 = -200;
					B_y14 = -200;

					bbvy = 0.0;
					B_y17 = -200;
					B_y18 = -200;
					B_y19 = -200;
					B_y20 = -200;

					S_y = -205;

					bun_move1 = 0;
					bun_move2 = 0;
					bun_move3 = 0;

					Ya = false;
					Ya_y = 0;
					Ya_vy = 10;
					Ya_g = 0.18;
					Ya_Atk = false;

					is_Ly = false;
					ly_x = 800;

					is_Jump = true;

					is_Punch = false;
					swich = false;
				}
			}
	}
	break;

	case 2:
		P_y -= vy;
		vy += g;

		// 13,14ブロックの重力
		if (block1314){
			bvy += g;
			B_y13 -= bvy;
			B_y14 -= bvy;
		}

		// 17,18,19,20ブロック
		// Swichの重力
		if (swich){
			bbvy += g;
			B_y17 -= bbvy;
			B_y18 -= bbvy;
			B_y19 -= bbvy;
			B_y20 -= bbvy;
			S_y -= bbvy;
		}
	{
		if (app_env.isPressKey('D')) {  // Dを押したら右に移動
			P_x += 2;
			right = true;
		}
		if (app_env.isPressKey('A')) {  // Aを押したら左に移動
			P_x -= 2;
			right = false;
		}

		// 影
		if (is_Jump){
			drawTextureBox(P_x, P_y - 5, 256 - 128, 128 - 64,
				0, 0, 256, 128,
				kage,
				Color(1, 1, 1));
		}

		// 羽
		if (!is_Jump){
			if (right){
				drawTextureBox(P_x - 10, std::abs(std::sin(move)) * 4 + P_y + 40, 128, 64,
					0, 0, 256, 128,
					wing_R,
					Color(1, 1, 1));
			}
			else{
				drawTextureBox(P_x + 10, std::abs(std::sin(move)) * 4 + P_y + 40, 128, 64,
					0, 0, 256, 128,
					wing_L
					
					,
					Color(1, 1, 1));
			}
		}

		// sinの振れ
		// 左右向いた時の画像切り替え
		move += 0.05;
		if (right){
			drawTextureBox(P_x, std::abs(std::sin(move)) * 4 + P_y, P_x2 - 128, P_y2 - 64,
				0, 0, 256, 128,
				pork_R,
				Color(1, 1, 1));
		}
		else {
			drawTextureBox(P_x, std::abs(std::sin(move)) * 4 + P_y, P_x2 - 128, P_y2 - 64,
				0, 0, 256, 128,
				pork_L,
				Color(1, 1, 1));
		}

		if (P_x <= -880){ P_x += 2; }
		if (P_x >= 700){ P_x -= 2; }

		//StartFlag
		drawTextureBox(-800, -210, 140, 140, 0, 0, 256, 256, start_flag, Color(1, 1, 1));

		//　木
		drawTextureBox(-550, -215, 256 - 64, 512 - 128,
			0, 0, 256, 512,
			tree,
			Color(1, 1, 1));

		// 矢
		if (P_x >= -600){ Ya = true; }
		if (Ya){ Ya_y -= Ya_vy; Ya_vy += Ya_g; }
		if (Ya_y <= -220){ Ya_vy = 0; Ya_y = -220; }
		if (Ya){
			drawTextureBox(-530, Ya_y, 64, 128,
				0, 0, 128, 256,
				ya,
				Color(1, 1, 1));
			drawTextureBox(-510, Ya_y, 64, 128,
				0, 0, 128, 256,
				ya,
				Color(1, 1, 1));
			drawTextureBox(-470, Ya_y, 64, 128,
				0, 0, 128, 256,
				ya,
				Color(1, 1, 1));
		}
		// 矢あたり判定
		if ((Ya_y <= -160) && (Ya_y >= -210)){ Ya_Atk = true; }
		if (Ya_y <= -215){ Ya_Atk = false; }
		if ((P_x >= -600) && (P_x <= -450)&&(Ya_Atk)&&(is_Jump)){
			Life = Life - 1;
			MODE = 4;
		}

		// 階段
		drawTextureBox(B_x + 10 * block_x, B_y + 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 11 * block_x, B_y + 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 11 * block_x, B_y + 100, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 12 * block_x, B_y + 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 12 * block_x, B_y + 100, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 12 * block_x, B_y + 150, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));

		// block 1列目
		if ((P_x == -400) && (P_y < -150)){ P_x -= 2; }
		if ((P_x > -401) && (P_x < -349) && (P_y <= -150)){ vy = 0; }
		if ((P_x > -401) && (P_x < -349) && (P_y <= -149)){ is_Jump = true; }
		if ((P_x > -401) && (P_x < -349) && (P_y > -150)){ is_Jump = false; }
		// block 2列目
		if ((P_x == -350) && (P_y < -100)){ P_x -= 2; }
		if ((P_x > -351) && (P_x < -299) && (P_y < -100)){ vy = 0; }
		if ((P_x > -351) && (P_x < -299) && (P_y <= -99)){ is_Jump = true; }
		if ((P_x > -351) && (P_x < -299) && (P_y > -100)){ is_Jump = false; }
		// block 3列目
		if ((P_x == -300) && (P_y < -50)){ P_x -= 2; }
		if ((P_x > -301) && (P_x < -200) && (P_y < -50)){ vy = 0; }
		if ((P_x > -301) && (P_x < -200) && (P_y <= -49)){ is_Jump = true; }
		if ((P_x > -301) && (P_x < -200) && (P_y > -50)){ is_Jump = false; }
		if ((P_x == -200) && (P_y < -50)){ P_x += 2; }


		// とんでくるLy
		if ((P_x > -301) && (P_x < -200) && (P_y > -50)){ is_Ly = true; }
		if (is_Ly){
			if (ly_x <= -900){ is_Ly = false; }
			ly_x -= 25;
			drawTextureBox(ly_x, -30, 128, 64, 0, 0, 128, 64, ly, Color(1, 1, 1));
		}
		// Lyあたり判定
		if ((ly_x <= -150) && (ly_x >= -350) && (P_y >= -65)){ Life = Life - 1; MODE = 4; }


		// どかん
		drawTextureBox(-55, -220, 128, 256, 0, 0, 128, 256, dokan, Color(1, 1, 1));
		if ((P_x == -120) && (P_y < -70)){ P_x -= 2; }
		if ((P_x > -121) && (P_x < -10) && (P_y < -70)){
			vy = 0;
			P_y = -70;
			if (app_env.isPushKey('S')){ is_Punch = true; }
			// Sを押したときパンチをtrueにする
		}
		if ((P_x > -121) && (P_x < -10) && (P_y <= -69)){ is_Jump = true; }
		if ((P_x > -121) && (P_x < -10) && (P_y > -70)){ is_Jump = false; }
		if ((P_x == -10) && (P_y < -70)){ P_x += 2; }

		// 階段ー土管までの地面
		if ((P_x > -200) && (P_x < -120) && (P_y <= B_y13)){ vy = 0; P_y = B_y13; is_Jump = true; block1314 = true; }
		else if ((P_x > -200) && (P_x < -120) && (P_y >= B_y13 + 1)) { is_Jump = false; }

		//パンチ
		if (is_Punch){
			vy = -50;
			drawTextureBox(-60, -70, 128, 256, 0, 0, 128, 256, don, Color(1, 1, 1));
		}

		//土管からの地面 重力
		if (!swich){
			if ((P_y <= -200) && (P_y >= -205) && (P_x >= -10) && (P_x <= 190)){
				is_Jump = true;
				vy = 0;
				P_y = -200;
				drawTextureBox(P_x + 40, P_y + 55, 128, 128, 0, 0, 256, 256, ranran_hatena, Color(1, 1, 1));
			}
			else if (P_x >= -10){ is_Jump = false; }
		}
		else{
			if ((P_y <= B_y17) && (P_y >= B_y17 - 5) && (P_x >= -10) && (P_x <= 190)){
				is_Jump = true;
				vy = 0;
				P_y = B_y17;
				drawTextureBox(P_x + 40, P_y + 55, 128, 128, 0, 0, 256, 256, ranran_hatena, Color(1, 1, 1));
			}
			else if (P_x >= -10){ is_Jump = false; }
		}

		//スイッチ
		if ((P_x >= 60) && (P_x <= 190) && (P_y >= -220) && (P_y <= 140)){
			if (!swich){
				if (app_env.isPushKey(GLFW_KEY_ENTER)){
					swich = true;
				}
			}
		}
		if (!swich){
			drawTextureBox(170, S_y, 64, 64, 0, 0, 128, 128, swich2, Color(1, 1, 1));
		}
		else { drawTextureBox(170, S_y, 64, 64, 0, 0, 128, 128, swich1, Color(1, 1, 1)); }

		// スイッチからの地面
		if (swich){
			if ((P_y <= -200) && (P_y >= -205) && (P_x >= 290)){
				is_Jump = true;
				vy = 0;
				P_y = -200;
			}
			else if (P_x >= 290){ is_Jump = false; }
		}


		// 地面
		drawTextureBox(B_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 2 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 3 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 4 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 5 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 6 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 7 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 8 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 9 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 10 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 11 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 12 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));

		drawTextureBox(B_x + 13 * block_x, B_y13 - 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 14 * block_x, B_y14 - 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));

		drawTextureBox(B_x + 15 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 16 * block_x, B_y, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));

		drawTextureBox(B_x + 17 * block_x, B_y17 - 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 18 * block_x, B_y18 - 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 19 * block_x, B_y19 - 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));
		drawTextureBox(B_x + 20 * block_x, B_y20 - 50, 50, 50, 0, 0, 64, 64,
			block, Color(1, 1, 1));

		if (swich){
			drawTextureBox(B_x + 23 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
			drawTextureBox(B_x + 24 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
			drawTextureBox(B_x + 25 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
			drawTextureBox(B_x + 26 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
			drawTextureBox(B_x + 27 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
			drawTextureBox(B_x + 28 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
			drawTextureBox(B_x + 29 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
			drawTextureBox(B_x + 30 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
			drawTextureBox(B_x + 31 * block_x, B_y, 50, 50, 0, 0, 64, 64,
				block, Color(1, 1, 1));
		}


		//重力制御
		if ((P_y <= -200) && (P_y >= -205) && (P_x < -400)){
			is_Jump = true;
			vy = 0;
			P_y = -200;
		}
		else if (P_x < -400){ is_Jump = false; }

		//ジャンプしたときの初速
		if (is_Jump){
			if (app_env.isPushKey(GLFW_KEY_SPACE)){ vy = -3.5; }
		}

		// ブーン
		bun_move1 += 0.1;
		bun_move2 += 0.08;
		bun_move3 += 0.09;
		drawTextureBox(2 * bun_move1, std::sin(bun_move1) * 4 + 200, 512 - 256, 128 - 64, 0, 0, 512, 128, bun, Color(1, 1, 1));
		drawTextureBox(2 * bun_move2 - 250, std::sin(bun_move2) * 4 + 280, 512 - 256, 128 - 64, 0, 0, 512, 128, bun, Color(1, 1, 1));
		drawTextureBox(2 * bun_move3 - 700, std::sin(bun_move3) * 4 + 180, 512 - 256, 128 - 64, 0, 0, 512, 128, bun, Color(1, 1, 1));
		drawTextureBox(2 * bun_move2 - 1200, std::sin(bun_move1) * 4 + 220, 512 - 256, 128 - 64, 0, 0, 512, 128, bun, Color(1, 1, 1));

		//
		//コメント欄
		//

		// Black長方形
		drawFillBox(-800, -450, 1600, 150, Color(0, 0, 0));

		if (app_env.isPushKey('Z')){
			P_x = -750;
			P_y = -200;
			vy = 0;

			right = true;

			B_x = -800;
			B_y = -250;
			block_x = 50;
			block1314 = false;
			bvy = 0.0;
			B_y13 = -200;
			B_y14 = -200;

			bbvy = 0.0;
			B_y17 = -200;
			B_y18 = -200;
			B_y19 = -200;
			B_y20 = -200;

			S_y = -205;

			bun_move1 = 0;
			bun_move2 = 0;
			bun_move3 = 0;

			Ya = false;
			Ya_y = 0;
			Ya_vy = 10;
			Ya_g = 0.18;
			Ya_Atk = false;

			is_Ly = false;
			ly_x = 800;

			is_Jump = true;

			is_Punch = false;
			swich = false;
		}
		
		// クリア画面へ移動
		if (P_x >= 650){ MODE = 3; }

		// 落下死とする
		if (P_y <= -400){ Life = Life - 1; MODE = 4; }
		if (P_y >= 500){ Life = Life - 1; MODE = 4; }
	}
	break;

	case 3:
	{
			  drawTextureBox(-512, -512, 1024, 1024, 0, 0, 512, 512, clear_logo, Color(1, 1, 1));
			  drawTextureBox(400, -400, 400, 400, 0, 0, 512, 512, clear_sellect, Color(1, 1, 1));
			  if (app_env.isPushKey(GLFW_KEY_ESCAPE)){ return 0; }
			  if (app_env.isPushKey(GLFW_KEY_ENTER)){ MODE = 1; P_x = -650; }
	}
	break;

	case 4:
	{

			// You Dead
 			drawTextureBox(-128, -50, 256, 256, 0, 0, 256, 256, youdead, Color(1, 1, 1));

			// (´・ω・｀)
			drawTextureBox(-130, -160, P_x2 - 128, P_y2 - 64,
						 0, 0, 256, 128,
					     pork_R,
						 Color(1, 1, 1));

			if (Life == 4){
				drawTextureBox(0, -170, 200, 100,
							 0, 0, 256, 128,
							 X4,
							 Color(1, 1, 1));
			}
			else if (Life == 3){
				drawTextureBox(0, -170, 200, 100,
							 0, 0, 256, 128,
						     X3,
							 Color(1, 1, 1));
			}
			else if (Life == 2){
				drawTextureBox(0, -170, 200, 100,
					0, 0, 256, 128,
					X2,
					Color(1, 1, 1));
			}
			else if (Life == 1){
				drawTextureBox(0, -170, 200, 100,
					0, 0, 256, 128,
					X1,
					Color(1, 1, 1));
			}




			timer += 1;
			if (timer >= 120){
			MODE = 2;
			timer = 0;

			// 変数の初期化
			P_x = -750;
			P_y = -200;
			vy = 0;

			right = true;

			B_x = -800;
			B_y = -250;
			block_x = 50;
			block1314 = false;
			bvy = 0.0;
			B_y13 = -200;
			B_y14 = -200;

			bbvy = 0.0;
			B_y17 = -200;
			B_y18 = -200;
			B_y19 = -200;
			B_y20 = -200;

			S_y = -205;

			bun_move1 = 0;
			bun_move2 = 0;
			bun_move3 = 0;

			Ya = false;
			Ya_y = 0;
			Ya_vy = 10;
			Ya_g = 0.18;
			Ya_Atk = false;

			is_Ly = false;
			ly_x = 800;

			is_Jump = true;

			is_Punch = false;
			swich = false;
			}
	}
		break;
	}
    
    //
    // 描画処理はここでおこなう
    // 
    
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
