
#include "lib/appEnv.hpp"
#pragma once

//
// ゲーム本編(case 2)
//

void dead(AppEnv& app_env, Media& kirby, Media& minecraft, Texture& ground, int& meteo_move, Texture& butagoya,
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
	Texture& bun, Texture& syougai, bool& is_Dokankara, bool& is_Icanfly, Texture& youdead, Texture& X4, Texture& X3,
	Texture& X2, Texture& X1, Texture& X0, Texture& uekara, Texture& yokokara, Texture& dokankara, Texture& icanfly,
	Texture& konokusoge, float& gain_kirby, Texture& go_stagesentaku, int& timer){

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
		if (is_Uekara){
			drawTextureBox(-256, -400, 521, 128,
				0, 0, 1024, 256,
				uekara,
				Color(1, 1, 1));
		}
		if (is_Yokokara){
			drawTextureBox(-256, -380, 512, 128,
				0, 0, 1024, 256,
				yokokara,
				Color(1, 1, 1));
		}
		if (is_Dokankara){
			drawTextureBox(-256, -380, 512, 128,
				0, 0, 1024, 256,
				dokankara,
				Color(1, 1, 1));
		}
		if (is_Icanfly){
			drawTextureBox(-200, -380, 512, 128,
				0, 0, 1024, 256,
				icanfly,
				Color(1, 1, 1));
		}
	}
	else if (Life == 2){
		drawTextureBox(0, -170, 200, 100,
			0, 0, 256, 128,
			X2,
			Color(1, 1, 1));
		if (is_Uekara){
			drawTextureBox(-256, -400, 521, 128,
				0, 0, 1024, 256,
				uekara,
				Color(1, 1, 1));
		}
		if (is_Yokokara){
			drawTextureBox(-256, -380, 512, 128,
				0, 0, 1024, 256,
				yokokara,
				Color(1, 1, 1));
		}
		if (is_Dokankara){
			drawTextureBox(-256, -380, 512, 128,
				0, 0, 1024, 256,
				dokankara,
				Color(1, 1, 1));
		}
		if (is_Icanfly){
			drawTextureBox(-200, -380, 512, 128,
				0, 0, 1024, 256,
				icanfly,
				Color(1, 1, 1));
		}
	}
	else if (Life == 1){
		drawTextureBox(0, -170, 200, 100,
			0, 0, 256, 128,
			X1,
			Color(1, 1, 1));
		if (is_Uekara){
			drawTextureBox(-256, -400, 521, 128,
				0, 0, 1024, 256,
				uekara,
				Color(1, 1, 1));
		}
		if (is_Yokokara){
			drawTextureBox(-256, -380, 512, 128,
				0, 0, 1024, 256,
				yokokara,
				Color(1, 1, 1));
		}
		if (is_Dokankara){
			drawTextureBox(-256, -380, 512, 128,
				0, 0, 1024, 256,
				dokankara,
				Color(1, 1, 1));
		}
		if (is_Icanfly){
			drawTextureBox(-200, -380, 512, 128,
				0, 0, 1024, 256,
				icanfly,
				Color(1, 1, 1));
		}
	}
	else if (Life == 0){
		drawTextureBox(0, -170, 200, 100,
			0, 0, 256, 128,
			X0,
			Color(1, 1, 1));
		drawTextureBox(-500, -350, 1024, 128,
			0, 0, 2048, 256,
			konokusoge,
			Color(1, 1, 1));

		// BGM down
		gain_kirby -= 0.01;
		kirby.gain(gain_kirby);

		// ブラックアウト
		blackout += 1.2;
		drawFillBox(-800, -450, 1600, 900, color256(0, 0, 0, blackout));
		if (blackout >= 100){
			drawTextureBox(-256, -128, 512, 256,
				0, 0, 512, 256,
				go_stagesentaku,
				color256(255, 255, 255));

			if (blackout >= 256){
				MODE = 1;

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

				circle_size = 30;
				circle_vy = 2;
				circle_g = 0.1;

				Life = 4;

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

				gain_minecraft = 1;
			}

		}
	}



	if (!Life == 0){
		timer += 1;
		if (timer >= 120){
			MODE = 2;
			timer = 0;
			is_Uekara = false;
			is_Yokokara = false;
			is_Dokankara = false;
			is_Icanfly = false;
		}
	}

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
}