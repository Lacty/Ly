//
// �A�v�����`
//

#include "appEnv.hpp"


// �A�v���̃E�C���h�E�T�C�Y
enum Window {
	WIDTH = 512,
	HEIGHT = 512
};

// ���_��\��
void dispPlayPoint(int play_point){
	Texture miku_point("res/miku_point.png");
	Texture miku_point_1("res/miku_point_1.png");
	float x = -Window::WIDTH / 2 + 50;
	float y = -Window::HEIGHT / 2 + 25;

	// 10�̈ʂ�傫�ȃ~�N�ŕ\��
	int ten_points = play_point / 10;
	while (ten_points > 0) {
		drawTextureBox(x - 25, y - 65, 128, 128,
			0, 0,128, 128,
			miku_point,
			Color(1, 1, 1));

		x += 15 * 2 + 5;
		ten_points -= 1;
	}

	// 1�̈ʂ������ȃ~�N�ŕ\��
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
					// ��`�̒��ɂ���̂�true��Ԃ�
					return true;
				}
			}
		}
	}
	// ��`�̊O�Ȃ̂�false��Ԃ�
	return false;
}

// 
// ���C���v���O����
// 
int main() {

	// �A�v���E�C���h�E�̏���
	AppEnv app_env(Window::WIDTH, Window::HEIGHT,
		false, // �t���X�N���[�����[�h
		false);

	// �n�C�X�R�A	�`�F�b�N
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

	//�@�~�N�̎����ŕ\���ʒu��ς���ϐ�
	int miku_count = 0;

	// �u�͂�������?�v�̏���
	Media title("res/title.wav");
	// �u����[���[�v�̏���
	Media end("res/end.wav");
	// �u�X�^�[�g�v�̏���
	Media start("res/start.wav");
	// �uhit�v��
	Media hit("res/hit.wav");

	// �E�B���h�E�̈ʒu��ς���
	// app_env.windowPosition(Vec2i(10, 10));

	while (1) {
		// �Đ�
		title.play();
		while (1) {
			// �A�v���E�C���h�E������ꂽ��v���O�������I��
			if (!app_env.isOpen()) return 0;

			// �`�揀��
			app_env.setupDraw();

			// �^�C�g��
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
					// ���N���b�N�������ĊJ�n
					click_start += 0.12;
					drawTextureBox(-256, std::sin(click_start) * 15 - 200, 512, 128,
						0, 0, 512, 128,
						click_to_start,
						Color(1, 1, 1));
				}
				else{
					click_tika += 1;

					//�@�`�J�`�J���鏈��
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

				//�@���N���b�N�ŃX�^�[�g
				if (app_env.isPressButton(Mouse::LEFT)){
					title.stop();
					chika = true;
					click_tika = 0;
					start.play();
					// ���͂����Z�b�g
					app_env.flushInput();
				}
				
			}
			// 
			// �����ɕ`�揈��������
			//

			// ��ʍX�V
			app_env.update();
		}

		////////////////
		// �v���C��� //
		////////////////
		int play_time = 60 * 10;

		int play_point = 0;

		// �����e�[�u��������
		app_env.random().setSeed(miku_count);

		// �����_��(�\��)
		int miku_x = app_env.random().fromFirstToLast(-200, 200);
		int miku_y = app_env.random().fromFirstToLast(-200, 200);

		//�@�����_��(�Ԃ�Ԃ�)
		int miku_x1 = app_env.random().fromFirstToLast(-5, 5);
		int miku_y1 = app_env.random().fromFirstToLast(-5, 5);

		// �~�N_hit�̃u���u�����鎞�Ԃ̕ϐ�
		bool miku_buru = false;

		miku_count = 0;

		while (1) {
			// �A�v���E�C���h�E������ꂽ��v���O�������I��
			if (!app_env.isOpen()) return 0;

			// �`�揀��
			app_env.setupDraw();

			// �}�E�X�̈ʒu��ϐ��ɃR�s�[
			Vec2f mouse_pos = app_env.mousePosition();

			// �w�i
			drawTextureBox(-256, -256, 512, 512,
				0, 0, 512, 512,
				game_bg,
				Color(1, 1, 1));

			// �c�莞�Ԃ̕\��
			{
				// �\���ʒu
				float x = -100;
				float y = -Window::HEIGHT / 2 + 460;

				// �\���T�C�Y
				float width = (play_time * 200) / (60 * 10);
				float height = 30;

				//�@���Ԃ���������F��Ԃɂ���ϐ���p��
				float red = 0.3;
				float green = 0.5;
				float blue = 0.8;

				// �c�莞�Ԃ���`�ŕ\��
				drawFillBox(-100, y, 200, 30, Color(0.8, 0.8, 0.8));
				if (play_time < 180) {
					red = 1;
					green = 0;
					blue = 0;
				};
				drawFillBox(x, y, width, height, Color(red, green, blue));
				// �g��
				drawBox(x, y, 200, height, 2, Color(1, 1, 1));
			}

			// �~�N�̕\���ʒu�̃����_��
			miku_count += 1;
			if (miku_count >= 120){
				miku_x = app_env.random().fromFirstToLast(-200, 200);
				miku_y = app_env.random().fromFirstToLast(-200, 200);
				miku_count = 0;
			}

			// �~�N�̕`��
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
					// ���_�����Z
					play_point += 1;
					miku_count = 0;
					hit.play();
				}
			}

			// haetataki1,2 �}�E�X�ɂ��Ă���
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

			// ���_�\��
			dispPlayPoint(play_point);

			// �v���C�^�C�������炷
			play_time -= 1;

			// �v���C���Ԃ��P�O�b�ȉ��ɂȂ�����u���C�N
			if (play_time < 0) { break; }

			// ��ʍX�V
			app_env.update();
		}

		//////////////
		// ���ʉ�� //
		//////////////
		float kirakira = 0;
		end.play();
		while (1) {
			// �A�v���E�C���h�E������ꂽ��v���O�������I��
			if (!app_env.isOpen()) return 0;

			// �`�揀��
			app_env.setupDraw();

			// �w�i
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

			// �n�C�X�R�A�X�V�`�F�b�N
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

			// ��ʍX�V
			app_env.update();
		}
		hi_score = play_point;
		// ���͂̃t���b�V��
		app_env.flushInput();
	}
	// �A�v���I��
}