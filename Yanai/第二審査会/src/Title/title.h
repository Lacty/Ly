
#pragma once

//
//	タイトル演出
//

#include "../common.h"

class Title{
private:
	//	構造体Startの配列宣言
	Object Start[5];
	//	矢印の切り取り位置変更用変数
	int cut_y;
	//	移動用変数
	int MOVE;

	//	マウス用変数
	Vec2f mouse_pos;
	bool isClick;
	float click_posx;
	float click_posy;

	bool modeSwitch;

	//	リセット用関数
	void reset();
public:
	Title();

	void draw(Texture&);
	void update(int&);

};