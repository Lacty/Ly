//
//	Player
//

#include "player.h"
#include "../app.h"


//	コンストラクタ
Player::Player(){
	player_image = (Texture(PLAYER_IMAGE));
	player = { -WIDTH/2, -100, 80, 40, 0, 0, 200, 100, Color(1, 1, 1),
		false, true, -0.2, 0, 2 };
	tex_count = 0;
	for (int i = 0; i < SHOT_MAX; i++){
		shot[i] = { 0, 0, 40, 20,
			400, 200, 100, 100,
			Color(1, 1, 1), false, true };
		shot[i].speed = { 10 };
	}
}

//	Playerの描画
void Player::draw(){
	//	オワタの画像
	drawTextureBox(player.x, player.y, player.width, player.height,
		player.start_tx, player.start_ty,
		player.texture_width, player.texture_height,
		player_image,
		player.col);
	//	弾の画像
	for (int i = 0; i < SHOT_MAX; i++){
		if (shot[i].active){
			drawTextureBox(shot[i].x, shot[i].y, shot[i].width, shot[i].height,
				shot[i].start_tx, shot[i].start_ty,
				shot[i].texture_width, shot[i].texture_height,
				player_image,
				shot[i].col);
		}
	}

}

//	Playerの処理部分
void Player::update(){
	playerMove();
	playerShot();
}

void Player::playerMove(){
	pos = App::app_env->mousePosition();

	//	マウスがオワタより右にある時
	//	オワタを右に移動させる
	if ((player.x + player.width) < pos.x()){
		player.x += player.speed;
	}
	//	マウスがオワタの中心から右にあれば
	//	オワタを右に向かせる
	if ((player.x + player.width / 2) < pos.x()){
		if (!player.right){
			player.right = true;
			player.start_tx = 0;
			player.start_ty = 0;
		}
	}
	//	マウスがオワタより左にある時
	//	オワタを左に移動させる
	if (player.x > pos.x()){
		player.x -= player.speed;
	}
	//	マウスがオワタの中心から左にあれば
	//	オワタを左に向かせる
	if ((player.x + player.width / 2) > pos.x()){
		if (player.right){
			player.right = false;
			player.start_tx = 600;
			player.start_ty = 0;
		}
	}


	//	オワタの重力
	player.vy += player.g;
	player.y += player.vy;
}


void Player::playerShot(){
	if (App::app_env->isPushButton(LEFT)){
		for (int i = 0; i < SHOT_MAX; i++){
			if (!shot[i].active){
				//	キャラクターが左右どちらを向いているか保存
				if (player.right){
					shot[i].right = true;
				}
				else{
					shot[i].right = false;
				}

				//	弾を一つ射出
				shot[i].active = true;

				//	初期位置はキャラクターを参照
				shot[i].x = player.x;
				shot[i].y = player.y;
				break;
			}
		}
	}

	//	弾を撃った方向に移動させる
	for (int i = 0; i < SHOT_MAX; i++){
		if (shot[i].active){
			if (shot[i].right){
				shot[i].x += shot[i].speed;
				//	画像の切り取り位置も変更
				shot[i].start_tx = 400;
			}
			else {
				shot[i].x -= shot[i].speed;
				//	画像の切り取り位置も変更
				shot[i].start_tx = 500;
			}
		}
	}

	//	弾が画面外にでたら消す処理
	for (int i = 0; i < SHOT_MAX; i++){
		if (shot[i].x > WIDTH / 2){
			shot[i].active = false;
		}
		if (shot[i].x < (-WIDTH / 2) - shot[i].width){
			shot[i].active = false;
		}
	}
}
