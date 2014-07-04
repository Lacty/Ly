//
// アプリ雛形
//

#include "appEnv.hpp"


// アプリのウインドウサイズ
enum Window {
	WIDTH = 512,
	HEIGHT = 512
};

// 得点を表示
void dispPlayPoint(int play_point){
	Texture miku_point("res/miku_point.png");
	Texture miku_point_1("res/miku_point_1.png");
	float x = -Window::WIDTH / 2 + 50;
	float y = -Window::HEIGHT / 2 + 25;

	// 10の位を大きなミクで表示
	int ten_points = play_point / 10;
	while (ten_points > 0) {
		drawTextureBox(x - 25, y - 65, 128, 128,
			0, 0,128, 128,
			miku_point,
			Color(1, 1, 1));

		x += 15 * 2 + 5;
		ten_points -= 1;
	}

	// 1の位を小さなミクで表示
	int one_points = play_point % 10;
	while (one_points > 0) {
		drawTextureBox(x, y - 45, 80, 80,
			0, 0, 128, 128,
			miku_point_1,
			Color(1, 1, 1));

		x += 10 * 2 + 5;
		one_points -= 1;
	}
}

bool mouse(Vec2f mouse_pos, float x, float y,
	float width, float height){
	if (mouse_pos.x() > x) {
		if (mouse_pos.x() < (x + width)){
			if (mouse_pos.y() > y){
				if (mouse_pos.y() < (y + height)){
					// 矩形の中にあるのでtrueを返す
					return true;
				}
			}
		}
	}
	// 矩形の外なのでfalseを返す
	return false;
}

// 
// メインプログラム
// 
int main() {

	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT,
		false, // フルスクリーンモード
		false);

	// ハイスコア	チェック
	int hi_score = 0;
	{
		std::ifstream fstr("score.txt");
		if (fstr)
			fstr >> hi_score;
	}

	Texture title_bg("res/title_bg.png");
	Texture logo("res/logo.png");
	Texture click_to_start("res/click_to_start.png");
	Texture game_bg("res/game_bg.png");
	Texture result("res/result.png");
	Texture click_to_title("res/click_to_title.png");
	Texture haetataki_1("res/haetataki_1.png");
	Texture haetataki_2("res/haetataki_2.png");
	Texture miku("res/miku.png");
	Texture miku_hit("res/miku_hit.png");
	Texture hiscore("res/hi_score.png");

	float click_start = 0;
	float click_title = 0;
	float click_tika = 0;
	bool chika = false;

	//　ミクの自動で表示位置を変える変数
	int miku_count = 0;

	// 「はえたたき?」の準備
	Media title("res/title.wav");
	// 「しゅーりょー」の準備
	Media end("res/end.wav");
	// 「スタート」の準備
	Media start("res/start.wav");
	// 「hit」音
	Media hit("res/hit.wav");

	// ウィンドウの位置を変える
	// app_env.windowPosition(Vec2i(10, 10));

	while (1) {
		// 再生
		title.play();
		while (1) {
			// アプリウインドウが閉じられたらプログラムを終了
			if (!app_env.isOpen()) return 0;

			// 描画準備
			app_env.setupDraw();

			// タイトル
			{
				drawTextureBox(-256, -256, 512, 512,
					0, 0, 512, 512,
					title_bg,
					Color(1, 1, 1));

				drawTextureBox(-256, -256, 512, 512,
					0, 0, 512, 512,
					logo,
					Color(1, 1, 1));
				
				if (!chika){
					// 左クリックを押して開始
					click_start += 0.12;
					drawTextureBox(-256, std::sin(click_start) * 15 - 200, 512, 128,
						0, 0, 512, 128,
						click_to_start,
						Color(1, 1, 1));
				}
				else{
					click_tika += 1;

					//　チカチカする処理
					if (click_tika > 2){
						if (click_tika < 4){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 6){
						if (click_tika < 8){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 10){
						if (click_tika < 12){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 14){
						if (click_tika < 16){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 18){
						if (click_tika < 20){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 22){
						if (click_tika < 24){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 26){
						if (click_tika < 28){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 30){
						if (click_tika < 32){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 34){
						if (click_tika < 36){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 38){
						if (click_tika < 40){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 42){
						if (click_tika < 44){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 46){
						if (click_tika < 48){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 50){
						if (click_tika < 52){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 54){
						if (click_tika < 56){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 58){
						if (click_tika < 60){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 62){
						if (click_tika < 64){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}
					if (click_tika > 66){
						if (click_tika < 68){
							drawTextureBox(-256, -200, 512, 128,
								0, 0, 512, 128,
								click_to_start,
								Color(1, 1, 1));
						}
					}

					if (click_tika >= 70){ 
						chika = false;
						break;
					}
				}

				dispPlayPoint(hi_score);

				//　左クリックでスタート
				if (app_env.isPressButton(Mouse::LEFT)){
					title.stop();
					chika = true;
					click_tika = 0;
					start.play();
					// 入力をリセット
					app_env.flushInput();
				}
				
			}
			// 
			// ここに描画処理を書く
			//

			// 画面更新
			app_env.update();
		}

		////////////////
		// プレイ画面 //
		////////////////
		int play_time = 60 * 10;

		int play_point = 0;

		// 乱数テーブル初期化
		app_env.random().setSeed(miku_count);

		// ランダム(表示)
		int miku_x = app_env.random().fromFirstToLast(-200, 200);
		int miku_y = app_env.random().fromFirstToLast(-200, 200);

		//　ランダム(ぶるぶる)
		int miku_x1 = app_env.random().fromFirstToLast(-5, 5);
		int miku_y1 = app_env.random().fromFirstToLast(-5, 5);

		// ミク_hitのブルブルする時間の変数
		bool miku_buru = false;

		miku_count = 0;

		while (1) {
			// アプリウインドウが閉じられたらプログラムを終了
			if (!app_env.isOpen()) return 0;

			// 描画準備
			app_env.setupDraw();

			// マウスの位置を変数にコピー
			Vec2f mouse_pos = app_env.mousePosition();

			// 背景
			drawTextureBox(-256, -256, 512, 512,
				0, 0, 512, 512,
				game_bg,
				Color(1, 1, 1));

			// 残り時間の表示
			{
				// 表示位置
				float x = -100;
				float y = -Window::HEIGHT / 2 + 460;

				// 表示サイズ
				float width = (play_time * 200) / (60 * 10);
				float height = 30;

				//　時間が減ったら色を赤にする変数を用意
				float red = 0.3;
				float green = 0.5;
				float blue = 0.8;

				// 残り時間を矩形で表示
				drawFillBox(-100, y, 200, 30, Color(0.8, 0.8, 0.8));
				if (play_time < 180) {
					red = 1;
					green = 0;
					blue = 0;
				};
				drawFillBox(x, y, width, height, Color(red, green, blue));
				// 枠線
				drawBox(x, y, 200, height, 2, Color(1, 1, 1));
			}

			// ミクの表示位置のランダム
			miku_count += 1;
			if (miku_count >= 120){
				miku_x = app_env.random().fromFirstToLast(-200, 200);
				miku_y = app_env.random().fromFirstToLast(-200, 200);
				miku_count = 0;
			}

			// ミクの描画
			if (!miku_buru){
				drawTextureBox(miku_x - 100, miku_y - 100, 200, 200,
					0, 0, 256, 256,
					miku,
					Color(1, 1, 1));
			}
			else{
				miku_x1 = app_env.random().fromFirstToLast(-5, 5);
				miku_y1 = app_env.random().fromFirstToLast(-5, 5);
				drawTextureBox(miku_x - 100 + miku_x1, miku_y - 100 + miku_y1, 200, 200,
					0, 0, 256, 256,
					miku_hit,
					Color(1, 1, 1));

				if (miku_count > 20){
					miku_x = app_env.random().fromFirstToLast(-200, 200);
					miku_y = app_env.random().fromFirstToLast(-200, 200);
					miku_buru = false;
					miku_count = 0;
				}
			}

			if (mouse(mouse_pos, miku_x - 100, miku_y - 100, 200, 200)) {
				if (app_env.isPushButton(Mouse::LEFT)){
					app_env.flushInput();
					miku_buru = true;
					// 得点を加算
					play_point += 1;
					miku_count = 0;
					hit.play();
				}
			}

			// haetataki1,2 マウスについてくる
			if (app_env.isPushButton(Mouse::LEFT)){
				drawTextureBox(mouse_pos.x() - 180, mouse_pos.y() - 210, 256, 256,
					0, 0, 250, 250,
					haetataki_2,
					Color(1, 1, 1));
			}
			else{
				drawTextureBox(mouse_pos.x() - 180, mouse_pos.y() - 210, 256, 256,
					0, 0, 250, 250,
					haetataki_1,
					Color(1, 1, 1));
			}

			// 得点表示
			dispPlayPoint(play_point);

			// プレイタイムを減らす
			play_time -= 1;

			// プレイ時間が１０秒以下になったらブレイク
			if (play_time < 0) { break; }

			// 画面更新
			app_env.update();
		}

		//////////////
		// 結果画面 //
		//////////////
		float kirakira = 0;
		end.play();
		while (1) {
			// アプリウインドウが閉じられたらプログラムを終了
			if (!app_env.isOpen()) return 0;

			// 描画準備
			app_env.setupDraw();

			// 背景
			drawTextureBox(-256, -256, 512, 512,
				0, 0, 512, 512,
				title_bg,
				Color(1, 1, 1));

			drawTextureBox(-256, -256, 512, 512,
				0, 0, 512, 512,
				result,
				Color(1, 1, 1));

			click_title += 0.06;
			drawTextureBox(-256, std::sin(click_title) * 15 - 100, 512, 64,
				0, 0, 512, 64,
				click_to_title,
				Color(1, 1, 1));

			// ハイスコア更新チェック
			if (play_point > hi_score){
				kirakira += 1;
				if (kirakira > 0){
					if (kirakira < 2){
						drawTextureBox(-256, -185, 512, 64,
							0, 0, 512, 64,
							hiscore,
							Color(1, 0, 0));
					}
				}
				if (kirakira > 2){
					if (kirakira < 4){
						drawTextureBox(-256, -185, 512, 64,
							0, 0, 512, 64,
							hiscore,
							Color(1, 0.5, 0));
					}
				}
				if (kirakira > 4){
					if (kirakira < 6){
						drawTextureBox(-256, -185, 512, 64,
							0, 0, 512, 64,
							hiscore,
							Color(1, 1, 0));
					}
				}
				if (kirakira > 6){
					if (kirakira < 8){
						drawTextureBox(-256, -185, 512, 64,
							0, 0, 512, 64,
							hiscore,
							Color(0, 1, 0));
					}
				}
				if (kirakira > 8){
					if (kirakira < 10){
						drawTextureBox(-256, -185, 512, 64,
							0, 0, 512, 64,
							hiscore,
							Color(0, 1, 0.5));
					}
				}
				if (kirakira > 10){
					if (kirakira < 12){
						drawTextureBox(-256, -185, 512, 64,
							0, 0, 512, 64,
							hiscore,
							Color(0, 1, 1));
					}
				}
				if (kirakira > 12){
					if (kirakira < 14){
						drawTextureBox(-256, -185, 512, 64,
							0, 0, 512, 64,
							hiscore,
							Color(0, 0, 1));
					}
				}
				if (kirakira > 14){
					if (kirakira < 16){
						drawTextureBox(-256, -185, 512, 64,
							0, 0, 512, 64,
							hiscore,
							Color(1, 1, 1));
					}
				}
				if (kirakira > 14){
					kirakira = 0;
				}

				std::ofstream fstr("score.txt");
				if (fstr){
					fstr << play_point << std::endl;
				}
			}

			dispPlayPoint(play_point);
			if (app_env.isPressButton(Mouse::RIGHT)){
				app_env.flushInput();
				end.stop();
				break;
			};

			// 画面更新
			app_env.update();
		}
		hi_score = play_point;
		// 入力のフラッシュ
		app_env.flushInput();
	}
	// アプリ終了
}