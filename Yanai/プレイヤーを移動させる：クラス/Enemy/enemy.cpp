#include "enemy.h"
#include "../isHit.h"

using namespace collision;

//	コンストラクタ
Enemy::Enemy(){
	enemy.x = 20;
	enemy.y = 40;
	enemy.width = 10;
	enemy.height = 10;
	enemy.color = Color(1, 1, 1);
}

void Enemy::draw(AppEnv& app_env){
	drawFillBox(enemy.x, enemy.y, enemy.width, enemy.height, enemy.color);
}

void Enemy::update(AppEnv& app_env, Object& player){
	if (isHit(player.x, player.y, player.width, player.height,
		enemy.x, enemy.y, enemy.width, enemy.height)){
		enemy.color = Color(1, 0, 0);
	}
	else {
		enemy.color = Color(1, 1, 1);
	}
}
