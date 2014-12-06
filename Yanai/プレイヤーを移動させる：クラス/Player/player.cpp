#include "player.h"


// コンストラクタ
Player::Player(){
	player.x = 0;
	player.y = 0;
	player.width = 32;
	player.height = 32;
	player.color = Color(1, 1, 1);

	MOVE = 2;
}


void Player::draw(AppEnv& app_env){
	drawFillBox(player.x, player.y, player.width, player.height, player.color);
}


void Player::update(AppEnv& app_env){
	if (app_env.isPressKey('D')){
		player.x += MOVE;
	}
	if (app_env.isPressKey('A')){
		player.x -= MOVE;
	}
	if (app_env.isPressKey('W')){
		player.y += MOVE;
	}
	if (app_env.isPressKey('S')){
		player.y -= MOVE;
	}
}


Object Player::get_pos() const {
	return player;
}
