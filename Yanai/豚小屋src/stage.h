
#include "lib/appEnv.hpp"
#pragma once

//
// ステージ選択(case 1)
//

void stage(AppEnv& app_env, Media& kirby, Media& minecraft, Texture& ground, int& meteo_move, Texture& butagoya,
	float& cloud_move, Texture& start_rogo, Texture& cloud_ya, Texture& cloud_ko, Texture& cloud_buta,
	float& P_x, float& P_y, bool& right, Texture& kage, float& move, float& P_x2, float& P_y2,
	Texture& pork_R, Texture& pork_L, Texture& nitya_R, Texture& nitya_L, Texture& nityaa, Texture& coment_butagoyane,
	Texture& kusoge, bool& meteo_mode, Texture& meteo_a, Texture& fire, Texture& fire_under,
	Media& se_bom, Texture& bakuhatu, Texture& meteo_wind_l, Texture& gareki, Texture& exit, Texture& a_d,
	float& blackout, int& MODE, bool GO_MODE2, bool& click_enter, Texture& stage_sellect, Texture& ranran, Texture& flag, 
	Texture& stage_1, Texture& stage_2, int& comment_move, Texture& select_comment_1, Texture& enter, Texture& enter_to_sellect_stage,
	float& gain_minecraft, float& vy, float& B_x, float& B_y, float& block_x, bool& block1314, float& bvy, float& B_y13, float& B_y14,
	float& bbvy, float& B_y17, float& B_y18, float& B_y19, float& B_y20, float& S_y, float& bun_move1, float& bun_move2,
	float& bun_move3, float& bun_move4, bool& Ya, float& Ya_y, float& Ya_vy, float& Ya_g, bool& Ya_Atk, bool& is_Ly, float& ly_x,
	bool& is_Jump, bool& is_Punch, bool& swich, float& circle_x, float& circle_y, float& circle_size, float& circle_vy,
	float& circle_g, float& W_g){

	// BGM
	kirby.stop();
	if (!minecraft.isPlaying()) {
		minecraft.play();
		minecraft.gain(1);
	}
	//
	//操作キャラの処理
	//

	// Enterを押されるまで実行
	if (!GO_MODE2){
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
	// stage_1
	drawTextureBox(-140, -220, 256, 256,
		0, 0, 256, 256,
		flag,
		Color(1, 1, 1));
	drawTextureBox(-140, -280, 256, 64,
		0, 0, 256, 64,
		stage_1,
		Color(1, 1, 1));

	// stage_2
	drawTextureBox(180, -220, 256, 256,
		0, 0, 256, 256,
		flag,
		Color(1, 1, 1));
	drawTextureBox(180, -280, 256, 64,
		0, 0, 256, 64,
		stage_2,
		Color(1, 1, 1));

	// MODE5 へ
	// stage2は課金してください
	if ((P_x < 300) && (P_x > 40)){
		if (app_env.isPushKey(GLFW_KEY_ENTER)){
			MODE = 5;
		}
	}



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
	if ((P_x < 300) && (P_x > 40)){
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
			GO_MODE2 = true;
		}
		if (GO_MODE2){
			minecraft.gain(gain_minecraft);
			gain_minecraft -= 0.01;


			blackout += 2;
			drawFillBox(-800, -450, 1600, 900, color256(0, 0, 0, blackout));


			if (blackout >= 256){
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
				bun_move4 = 0;

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

				blackout = 0;

				GO_MODE2 = false;

				circle_size = 30;
				circle_vy = 2;
				circle_g = 0.1;

				float W_x[30] = { 750, 790, 830, 870, 910, 950, 990, 1030, 1070, 1110,
					1150, 1190, 1230, 1270, 1310, 1350, 1390, 1430, 1470, 1510,
					1550, 1590, 1630, 1670, 1710, 1750, 1790, 1830, 1870, 1910 };
				float W_y[30] = { -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, -200, };
				float W_vy[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				W_g = 0.1;

				gain_minecraft = 1;
			}
		}
	}
}