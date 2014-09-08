//
// アプリ雛形
// ※ファイル分割対応版
//

#include "lib/appEnv.hpp"
#include "title.h"
#include "stage.h"
#include "game.h"
#include "dead.h"

// ↑他の.cppファイルでは、必要なヘッダファイルを
//   適時インクルードする事


// アプリのウインドウサイズ
enum Window {
  WIDTH  = 1600,
  HEIGHT = 900
};

void Water(Texture& water, float x, float y){
	drawTextureBox(x, y, 64, 64,
		0, 0, 128, 128,
		water,
		Color(1, 1, 1));
}

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
  float P_x2 = 256;
  float P_y2 = 128;
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
  Texture cloud_buta("res/cloud_buta.png");                     // 雲
  Texture cloud_ko("res/cloud_ko.png");
  Texture cloud_ya("res/cloud_ya.png");
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
  float blackout = 0;
  bool GO_MODE2 = false;

  // 重力
  int v = 0;

  // ステージせんたく
  Texture stage_sellect("res/stage_sellect.png");

  // stage_1,2
  Texture stage_1("res/stage_1.png");
  Texture stage_2("res/stage_2.png");

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

  // 水の変数
  float W_x[30] { 750, 790, 830, 870, 910, 950, 990, 1030, 1070, 1110,
	  1150, 1190, 1230, 1270, 1310, 1350, 1390, 1430, 1470, 1510,
	  1550, 1590, 1630, 1670, 1710, 1750, 1790, 1830, 1870, 1910};
  float W_y[30] {-200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, };
  float W_vy[30]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  float W_g = 0.1;

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
  float bun_move4 = 0;

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
  Texture water("res/water.png");
  Texture GOAL("res/GOAL.png");

  Texture youdead("res/you_dead.png");

  Texture X4("res/X4.png");
  Texture X3("res/X3.png");
  Texture X2("res/X2.png");
  Texture X1("res/X1.png");
  Texture X0("res/X0.png");
  bool is_Uekara = false;
  Texture uekara("res/uekara.png");
  bool is_Dokankara = false;
  Texture dokankara("res/dokankara.png");
  bool is_Icanfly = false;
  Texture icanfly("res/icanfly.png");
  bool is_Yokokara = false;
  Texture yokokara("res/yokokara.png");
  Texture konokusoge("res/konokusoge.png");
  Texture go_stagesentaku("res/sutagesentaku.png");

  Texture syougai("res/syougai.png");

  Texture GameClear("res/GameClear.png");
  float circle_x = 0;
  float circle_y = 0;
  float circle_size = 30;
  float circle_vy = 2;
  float circle_g = 0.1;

  int timer = 0;

  right = true;

  // BGM,SE
  // タイトル画面
  Media minecraft("res/Minecraft.wav");
  float gain_minecraft = 1.00;
  Media se_bom("res/se_bom.wav");
  // プレイ画面
  Media kirby("res/Kirby.wav");
  float gain_kirby = 1.00;
  Media se_jump("res/se_jump.wav");
  Media se_ya("res/se_ya.wav");
  Media se_dokan("res/se_dokan.wav");
  Media se_switch("res/se_switch.wav");

  Texture nowfreeplaying("res/nowfreeplaying.png");

  int MODE = 0;

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;

    // 描画準備
    app_env.setupDraw();


	switch (MODE){
	case 0:
	{
			  title(app_env, kirby, minecraft, ground, meteo_move, butagoya,
				  cloud_move, start_rogo, cloud_ya, cloud_ko, cloud_buta,
				  P_x, P_y,right, kage, move, P_x2, P_y2,
				  pork_R, pork_L, nitya_R, nitya_L, nityaa, coment_butagoyane,
				  kusoge, meteo_mode, meteo_a, fire, fire_under,
				  se_bom, bakuhatu, meteo_wind_l, gareki, exit, a_d,
				  blackout, MODE);
	}
	break;

	case 1:
	{
			  stage(app_env, kirby, minecraft, ground, meteo_move, butagoya,
				  cloud_move, start_rogo, cloud_ya, cloud_ko, cloud_buta,
				  P_x, P_y, right, kage, move, P_x2, P_y2,
				  pork_R, pork_L, nitya_R, nitya_L, nityaa, coment_butagoyane,
				  kusoge, meteo_mode, meteo_a, fire, fire_under,
				  se_bom, bakuhatu, meteo_wind_l, gareki, exit, a_d,
				  blackout, MODE, GO_MODE2, click_enter, stage_sellect, ranran, flag,
				  stage_1, stage_2, comment_move, select_comment_1, enter, enter_to_sellect_stage,
				  gain_minecraft, vy, B_x, B_y, block_x, block1314, bvy, B_y13, B_y14,
				  bbvy, B_y17, B_y18, B_y19, B_y20, S_y, bun_move1, bun_move2,
				  bun_move3, bun_move4, Ya, Ya_y, Ya_vy, Ya_g, Ya_Atk, is_Ly, ly_x,
				  is_Jump, is_Punch, swich, circle_x, circle_y, circle_size, circle_vy,
				  circle_g, W_g);
	}
	break;

	case 2:
	{
			  game(app_env, kirby, minecraft, ground, meteo_move, butagoya,
				  cloud_move, start_rogo, cloud_ya, cloud_ko, cloud_buta,
				  P_x, P_y, right, kage, move, P_x2, P_y2,
				  pork_R, pork_L, nitya_R, nitya_L, nityaa, coment_butagoyane,
				  kusoge, meteo_mode, meteo_a, fire, fire_under,
				  se_bom, bakuhatu, meteo_wind_l, gareki, exit, a_d,
				  blackout, MODE, GO_MODE2, click_enter, stage_sellect, ranran, flag,
				  stage_1, stage_2, comment_move, select_comment_1, enter, enter_to_sellect_stage,
				  gain_minecraft, vy, B_x, B_y, block_x, block1314, bvy, B_y13, B_y14,
				  bbvy, B_y17, B_y18, B_y19, B_y20, S_y, bun_move1, bun_move2,
				  bun_move3, bun_move4, Ya, Ya_y, Ya_vy, Ya_g, Ya_Atk, is_Ly, ly_x,
				  is_Jump, is_Punch, swich, circle_x, circle_y, circle_size, circle_vy,
				  circle_g, W_g, g, se_jump, wing_R, wing_L, start_flag, tree,
				  ya, se_ya, Life, is_Uekara, block, is_Yokokara, ly, dokan,
				  se_dokan, don, ranran_hatena, se_switch, swich1, swich2, GOAL,
				  bun, syougai, is_Dokankara, is_Icanfly);
			  // 水への重力
			  if (swich){
				  for (int i = 0; i < 30; ++i) {
					  W_y[i] -= W_vy[i];
					  W_vy[i] += W_g;
				  }
			  }
			  // 水の処理
			  if (swich){
				  for (int i = 0; i < 30; ++i){
					  W_x[i] -= 1.5;
					  if ((W_y[i] <= -200) && (W_y[i] >= -205) && (W_x[i] >= 350)){
						  W_vy[i] = 0;
						  W_y[i] = -200;
						  W_x[i] -= 2;
					  }
					  Water(water, W_x[i], W_y[i]);

					  if (W_y[i] <= -400){
						  W_x[i] = 750;
						  W_y[i] = -200;
						  W_vy[i] = 0;
					  }
				  }
			  }
	}
	break;

	//
	// クリア画面
	//
	case 3:
	{
			  // BGM down
			  gain_kirby -= 0.01;
			  kirby.gain(gain_kirby);

			  circle_size -= circle_vy;
			  circle_vy += circle_g;
			  drawFillCircle(circle_x, circle_y, circle_size, circle_size, 1000, color256(200, 256, 200));
			  drawFillCircle(circle_x, circle_y, circle_size +  30, circle_size +  30, 1000, color256(256, 256, 256));
			  drawFillCircle(circle_x, circle_y, circle_size + 180, circle_size + 180, 1000, color256(256, 200, 200));
			  drawFillCircle(circle_x, circle_y, circle_size + 230, circle_size + 230, 1000, color256(256, 256, 256));
			  drawFillCircle(circle_x, circle_y, circle_size + 290, circle_size + 290, 1000, color256(200, 200, 256));
			  drawFillCircle(circle_x, circle_y, circle_size + 320, circle_size + 320, 1000, color256(256, 256, 256));
			  drawFillCircle(circle_x, circle_y, circle_size + 360, circle_size + 360, 1000, color256(200, 256, 256));
			  drawFillCircle(circle_x, circle_y, circle_size + 420, circle_size + 420, 1000, color256(256, 256, 256));
			  drawFillCircle(circle_x, circle_y, circle_size + 500, circle_size + 500, 1000, color256(256, 200, 256));
			  drawFillCircle(circle_x, circle_y, circle_size + 530, circle_size + 530, 1000, color256(256, 256, 256));
			  drawFillCircle(circle_x, circle_y, circle_size + 580, circle_size + 580, 1000, color256(200, 180, 220));
			  if (circle_size <= -2000){
				  circle_vy = 0;
				  drawTextureBox(-64, -400, 128, 64,
					  0, 0, 256, 128,
					  enter,
					  Color(1, 1, 1));
			  }

			  drawTextureBox(-512, -256, 1024, 512,
				  0, 0, 1024, 512,
				  GameClear,
				  Color(1, 1, 1));
			  if (app_env.isPushKey(GLFW_KEY_ESCAPE)){ return 0; }
			  if (app_env.isPushKey(GLFW_KEY_ENTER)){ MODE = 1; P_x = -650; }
	}
	break;

	//
	// Drad画面
	//
	case 4:
	{
			  dead(app_env, kirby, minecraft, ground, meteo_move, butagoya,
				  cloud_move, start_rogo, cloud_ya, cloud_ko, cloud_buta,
				  P_x, P_y, right, kage, move, P_x2, P_y2,
				  pork_R, pork_L, nitya_R, nitya_L, nityaa, coment_butagoyane,
				  kusoge, meteo_mode, meteo_a, fire, fire_under,
				  se_bom, bakuhatu, meteo_wind_l, gareki, exit, a_d,
				  blackout, MODE, GO_MODE2, click_enter, stage_sellect, ranran, flag,
				  stage_1, stage_2, comment_move, select_comment_1, enter, enter_to_sellect_stage,
				  gain_minecraft, vy, B_x, B_y, block_x, block1314, bvy, B_y13, B_y14,
				  bbvy, B_y17, B_y18, B_y19, B_y20, S_y, bun_move1, bun_move2,
				  bun_move3, bun_move4, Ya, Ya_y, Ya_vy, Ya_g, Ya_Atk, is_Ly, ly_x,
				  is_Jump, is_Punch, swich, circle_x, circle_y, circle_size, circle_vy,
				  circle_g, W_g, g, se_jump, wing_R, wing_L, start_flag, tree,
				  ya, se_ya, Life, is_Uekara, block, is_Yokokara, ly, dokan,
				  se_dokan, don, ranran_hatena, se_switch, swich1, swich2, GOAL,
				  bun, syougai, is_Dokankara, is_Icanfly, youdead, X4, X3,
				  X2, X1, X0, uekara, yokokara, dokankara, icanfly,
				   konokusoge, gain_kirby, go_stagesentaku, timer);
	}
		break;

	case 5:
	{
			  drawTextureBox(-512, -128, 1024, 256,
				  0, 0, 1024, 256,
				  nowfreeplaying,
				  Color(1, 1, 1));
			  if (app_env.isPushKey(GLFW_KEY_ENTER)){
				  MODE = 1;
			  }
	}
	}
    
    //
    // 描画処理はここでおこなう
    // 
    
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
