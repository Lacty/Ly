//
//	Stage_01
//

#include "../common.h"
#include "Stage_01.h"
#include "../isHit.h"
#include "../App.h"

using namespace collision;

//	コンストラクタ
Stage_01::Stage_01(){
	for (int i = 0; i < 20; i++){
		floor[i] = { -WIDTH / 2 + (i * 40), -200, 40, 40,
			0, 0, 40, 40, color256(0, 0, 0),
			true, true, 0.1, 0, 2 };
	}
	block[0] = { 0, -160, 40, 40,
		0, 0, 40, 40, color256(100, 200, 100),
		true, true, 0, 0, 0 };
	block[1] = { 250, -160, 40, 40,
		0, 0, 40, 40, color256(100, 200, 100),
		true, true, 0, 0, 0 };
	goal = { WIDTH / 2 - 40, -160, 40, 40,
		0, 0, 40, 40, color256(200, 100, 100),
		true, true, 0, 0, 0 };
	reset = false;
}

//	Stage_01の描画
void Stage_01::draw(Player& player){
	for (int i = 0; i < 20; i++){
		drawFillBox(floor[i].x, floor[i].y, floor[i].width, floor[i].height,
			floor[i].col);
	}
	for (int i = 0; i < 2; i++){
		drawFillBox(block[i].x, block[i].y, block[i].width, block[i].height,
			block[i].col);
	}
	drawFillBox(goal.x, goal.y, goal.width, goal.height, goal.col);
	player.draw();
}

//	Stage_01の処理部分
void Stage_01::update(Player& player, int& MODE){
	if (!reset){
		Reset01(player);
		reset = true;
	}
	player.update();
	Floor(player);
	Block(player);
	Goal(player, MODE);
}

//	床の判定
void Stage_01::Floor(Player& player){
	for (int i = 0; i < 20; i++){

		//	重力制御
		//	ブロックの上にいたら重力加速度を0に初期化
		if (player.player.x < (floor[i].x + floor[i].width)){
			if ((player.player.x + player.player.width) > floor[i].x){
				if (player.player.y < (floor[i].y + floor[i].height)){
					if (player.player.y >(floor[i].y + floor[i].height) - 10){
						//	床すり抜け防止に-10
						player.player.y = (floor[i].y + floor[i].height);
						player.player.vy = 0;
					}
				}
			}
		}
		//	壁のあたり判定
		if (player.player.y < (floor[i].y + floor[i].height)){
			if ((player.player.y + player.player.height) > floor[i].y){
				if (player.player.x < (floor[i].x + floor[i].width)){
					if (player.player.x >(floor[i].x + floor[i].width) - 10){
						//	壁"右"すり抜け防止に-10
						player.player.x = (floor[i].x + floor[i].width);
					}
				}
			}
		}
		if (player.player.y < (floor[i].y + floor[i].height)){
			if ((player.player.y + player.player.height) > floor[i].y){
				if ((player.player.x + player.player.width) > floor[i].x){
					if ((player.player.x + player.player.width) < floor[i].x + 10){
						//	壁"左"すり抜け防止に+10
						player.player.x = floor[i].x - player.player.width;
					}
				}
			}
		}
	}
}

void Stage_01::Block(Player& player){
	//	壁のあたり判定
	for (int i = 0; i < 2; i++){
		if (player.player.y < (block[i].y + block[i].height)){
			if ((player.player.y + player.player.height) > block[i].y){
				if (player.player.x < (block[i].x + block[i].width)){
					if (player.player.x >(block[i].x + block[i].width) - 10){
						//	壁"右"すり抜け防止に-10
						player.player.x = (block[i].x + block[i].width);
					}
				}
			}
		}
		if (player.player.y < (block[i].y + block[i].height)){
			if ((player.player.y + player.player.height) > block[i].y){
				if ((player.player.x + player.player.width) > block[i].x){
					if ((player.player.x + player.player.width) < block[i].x + 10){
						//	壁"左"すり抜け防止に+10
						player.player.x = block[i].x - player.player.width;
					}
				}
			}
		}
	}

	//	矢とブロックのあたり判定
	for (int b = 0; b < 2; b++){
		for (int s = 0; s < 2; s++){
			if (player.shot[s].active){
				if (rect_to_rect(player.shot[s].x, player.shot[s].y, player.shot[s].width, player.shot[s].height,
					block[b].x, block[b].y, block[b].width, block[b].height)){
					player.shot[s].active = false;
					block[b].active = false;
				}
			}
		}
	}

	//	ブロックがfalseになったら
	//	ブロックの位置を上に上げる
	for (int i = 0; i < 2; i++){
		if (!block[i].active){
			block[i].y = -100;
			block[i].col = color256(100, 100, 200);
		}
	}
}

//	ゴールの処理
void Stage_01::Goal(Player& player, int& MODE){
	if (rect_to_rect(player.player.x, player.player.y, player.player.width, player.player.height,
		goal.x, goal.y, goal.width, goal.height)){
		reset = false;
		MODE = 14;
	}
}

//	リセット
void Stage_01::Reset01(Player& player){
	block[0] = { 0, -160, 40, 40,
		0, 0, 40, 40, color256(100, 200, 100),
		true, true, 0, 0, 0 };
	block[1] = { 250, -160, 40, 40,
		0, 0, 40, 40, color256(100, 200, 100),
		true, true, 0, 0, 0 };
	player.player = { -WIDTH / 2, -100, 80, 40, 0, 0, 200, 100, Color(1, 1, 1),
		false, true, -0.2, 0, 2 };
	for (int i = 0; i < 2; i++){
		player.shot[i].active = false;
	}
}