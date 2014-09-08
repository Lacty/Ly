
#include "lib/appEnv.hpp"
#pragma once

//
// ゲーム本編(case 2)
//

void game(AppEnv& app_env, Media& kirby, Media& minecraft, Texture& ground, int& meteo_move, Texture& butagoya,
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
	float& circle_g, float& W_g, float& g, Media& se_jump, Texture& wing_R, Texture& wing_L, Texture& start_flag, Texture& tree,
	Texture& ya, Media& se_ya, int& Life, bool& is_Uekara, Texture& block, bool& is_Yokokara, Texture& ly, Texture& dokan,
	Media& se_dokan, Texture& don, Texture& ranran_hatena, Media& se_switch, Texture& swich1, Texture& swich2, Texture& GOAL,
	Texture& bun, Texture& syougai, bool& is_Dokankara, bool& is_Icanfly){

	//BGM
	minecraft.stop();
	if (!kirby.isPlaying()) {
		kirby.play();
		kirby.gain(0.5);
	}

	// キャラクターにかかる重力
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
		if ((is_Jump) && (app_env.isPushKey(GLFW_KEY_SPACE))){
			se_jump.play();
		}


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
		if ((Ya_y <= -160) && (Ya_y >= -210)){ Ya_Atk = true; se_ya.play(); }
		if (Ya_y <= -215){ Ya_Atk = false; }
		if ((P_x >= -600) && (P_x <= -450) && (Ya_Atk)){
			Life = Life - 1;
			is_Uekara = true;
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
		if ((ly_x <= -150) && (ly_x >= -350) && (P_y >= -65)){
			Life = Life - 1;
			is_Yokokara = true;
			MODE = 4;
		}


		// どかん
		drawTextureBox(-55, -220, 128, 256, 0, 0, 128, 256, dokan, Color(1, 1, 1));
		if ((P_x == -120) && (P_y < -70)){ P_x -= 2; }
		if ((P_x > -121) && (P_x < -10) && (P_y < -70)){
			vy = 0;
			P_y = -70;
			if (app_env.isPushKey('S')){ is_Punch = true; se_dokan.play(); }
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

		//スイッチ&SE
		if ((P_x >= 60) && (P_x <= 190) && (P_y >= -220) && (P_y <= 140)){
			if (!swich){
				if (app_env.isPushKey(GLFW_KEY_ENTER)){
					swich = true;
					// SE
					se_switch.play();
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
				P_x -= 2.5;
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

			drawTextureBox(600, -200, 200, 200,
				0, 0, 256, 256,
				GOAL,
				Color(1, 1, 1));
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
		if (bun_move1 >= 400){ bun_move1 = -450; }
		bun_move1 += 0.1;
		if (bun_move2 >= 520){ bun_move2 = -300; }
		bun_move2 += 0.08;
		if (bun_move3 >= 750){ bun_move3 = -100; }
		bun_move3 += 0.09;
		if (bun_move4 >= 1000){ bun_move4 = 100; }
		bun_move4 += 0.1;
		drawTextureBox(2 * bun_move1, std::sin(bun_move1) * 4 + 200, 512 - 256, 128 - 64, 0, 0, 512, 128, bun, Color(1, 1, 1));
		drawTextureBox(2 * bun_move2 - 250, std::sin(bun_move2) * 4 + 280, 512 - 256, 128 - 64, 0, 0, 512, 128, bun, Color(1, 1, 1));
		drawTextureBox(2 * bun_move3 - 700, std::sin(bun_move3) * 4 + 180, 512 - 256, 128 - 64, 0, 0, 512, 128, bun, Color(1, 1, 1));
		drawTextureBox(2 * bun_move4 - 1200, std::sin(bun_move4) * 4 + 220, 512 - 256, 128 - 64, 0, 0, 512, 128, bun, Color(1, 1, 1));

		//
		//コメント欄
		//

		// Black長方形
		drawFillBox(-800, -450, 1600, 150, Color(0, 0, 0));

		// 障害をよけて進もう
		drawTextureBox(-490, -460, 900, 238,
			0, 0, 1024, 256,
			syougai,
			Color(1, 1, 1));

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

			is_Uekara = false;
			is_Yokokara = false;
			is_Dokankara = false;
			is_Icanfly = false;
		}

		// クリア画面へ移動
		if (P_x >= 650){
			MODE = 3; P_x = -750;
			P_y = -200;
			vy = 0;

			right = true;
		}

		// 落下死とする
		if (P_y <= -400){
			Life = Life - 1;
			is_Icanfly = true;
			MODE = 4;
		}
		if (P_y >= 500){
			Life = Life - 1;
			is_Dokankara = true;
			MODE = 4;
		}
}