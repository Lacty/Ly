
#pragma once

//
//	Xe[WIð
//

#include "../common.h"

class Stage{
private:
	//	\¢ÌStageÌzñé¾
	Object Stage_[5];

	///////////////////////////////////////
	//             îó(wi)            //
	//	îó(wi)ÌÅå
	enum{
		Yaji_MAX = 20
	};
	//	îó(wi)Ì§¾x
	int alpha;
	//	îó(wi)ÌÚ®Xs[h
	int Yaji_MOVE;
	
	//	îó(wi)Ì\¢Ì
	Object Yaji[Yaji_MAX];

	//	îó(wi)­¶í
	bool Trigger;
	int trigger_count;
	int COUNT;
	/////////////////////////////////////
	/////////////////////////////////////

	bool startStage_;
	int MOVE;

	//	Xe[WIðÖ½Ìo
	void startStage();

	//	wiÌo
	void backGround();

	//	ZbgÖ
	void reset();

public:
	Stage();

	void draw(Texture&);
	void update(int&);

};