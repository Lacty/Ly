
#pragma once

//
//	ステージ選択
//

#include "../common.h"

class Stage{
private:
	//	構造体Stageの配列宣言
	Object Stage_[5];

	///////////////////////////////////////
	//             矢印(背景)            //
	//	矢印(背景)の最大数
	enum{
		Yaji_MAX = 20
	};
	//	矢印(背景)の透明度
	int alpha;
	//	矢印(背景)の移動スピード
	int Yaji_MOVE;
	
	//	矢印(背景)の構造体
	Object Yaji[Yaji_MAX];

	//	矢印(背景)発生器
	bool Trigger;
	int trigger_count;
	int COUNT;
	/////////////////////////////////////
	/////////////////////////////////////

	bool startStage_;
	int MOVE;

	//	ステージ選択へ来た時の演出
	void startStage();

	//	背景の演出
	void backGround();

	//	リセット関数
	void reset();

public:
	Stage();

	void draw(Texture&);
	void update(int&);

};