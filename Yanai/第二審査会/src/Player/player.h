
#pragma once

//
//	Player
//

#include "../common.h"

class Player{
private:
	//	プレイヤー用画像
	Texture player_image;

	Object player;

	//	プレイヤーの移動制御
	void playerMove();
	//	プレイヤーのモーションのカウント
	int tex_count;
	//	マウスの位置を取得する変数
	Vec2f pos;

	enum {
		//	弾の最大数
		SHOT_MAX = 2
	};
	Object shot[SHOT_MAX];
	//	プレイヤーの弾を撃つ処理
	void playerShot();
	
	//	フレンド指定
	//	指定したクラスからプレイヤーの中にアクセスできる！
	//	プレイヤーから指定先のクラスの中はアクセスできない！
	friend class Stage_01;
	/*
	クラスの中のdrawだけ指定可
	friend void Stage_01::draw;
	*/

public:
	Player();

	void draw();
	void update();

};