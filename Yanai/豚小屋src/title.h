
#include "lib/appEnv.hpp"
#pragma once

//
// タイトル(case 0)
//

void title(AppEnv& app_env, Media& kirby, Media& minecraft, Texture& ground, int& meteo_move, Texture& butagoya,
	      float& cloud_move, Texture& start_rogo, Texture& cloud_ya, Texture& cloud_ko, Texture& cloud_buta,
		  float& P_x, float& P_y, bool& right, Texture& kage, float& move, float& P_x2, float& P_y2,
		  Texture& pork_R, Texture& pork_L, Texture& nitya_R, Texture& nitya_L, Texture& nityaa, Texture& coment_butagoyane,
		  Texture& kusoge, bool& meteo_mode, Texture& meteo_a, Texture& fire, Texture& fire_under,
		  Media& se_bom, Texture& bakuhatu, Texture& meteo_wind_l, Texture& gareki, Texture& exit, Texture& a_d,
		  float& blackout, int& MODE){

	{//BGM,SE
		kirby.stop();
		if (!minecraft.isPlaying()) {
			minecraft.play();
		}
	}
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
		cloud_ya,
		Color(1, 1, 1));

	drawTextureBox(-450, std::sin(cloud_move + 1) * 5 + 170, 256, 256,
		0, 0, 256, 256,
		cloud_ko,
		Color(1, 1, 1));

	drawTextureBox(-750, std::sin(cloud_move + 4) * 5 + 170, 256, 256,
		0, 0, 256, 256,
		cloud_buta,
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
			return;
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
		// 隕石爆発SE
		if ((meteo_move > 500) && (meteo_move < 750)){
			// SE
			se_bom.play();
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
		blackout = 0;
	}

	if (app_env.isPressKey('Z')){
		MODE = 1;
		P_x = -650;
		blackout = 0;
	}

	if (app_env.isPressKey('X')){
		MODE = 4;
		P_x = -650;
	}

	if (app_env.isPressKey('C')){
		MODE = 3;
	}
}