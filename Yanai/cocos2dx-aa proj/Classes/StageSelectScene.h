#ifndef __Stage_Select_SCENE_H__
#define __Stage_Select_SCENE_H__

#include "cocos2d.h"
#include "structure.h"

class StageSelect : public cocos2d::Layer{
private:
    /* 画像用変数は
       initの中で宣言している
       一つの画像を複数回呼ぶ場合initでその回数分読み込むべし */

    int STAGE_NUMBER;

    _Object _Stage[5];
    _Object _Number;
    cocos2d::Sprite* num_image;
    
    /* TODO:変数名の変更
            処理の内容が理解しにくい */
    // 画像切り取り用
    int cut_texture;

    _Object _Arrow[2];
    cocos2d::Sprite* upside_arrow_image;
    cocos2d::Sprite* downside_arrow_image;

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    int  sgin;
    cocos2d::Point touchPoint;

public:
    StageSelect();

    static cocos2d::Scene* createScene();
    virtual bool init();         // 描画部分
    CREATE_FUNC(StageSelect);

    // 毎ループ行われる処理部分
    virtual void update(float delta);
};

#endif // __Stage_Select_SCENE_H__