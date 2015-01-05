#ifndef __Stage_Select_SCENE_H__
#define __Stage_Select_SCENE_H__

#include "cocos2d.h"
#include "structure.h"

class StageSelect : public cocos2d::Layer{
private:
    /* 画像用変数
       initの中で宣言している
       一つの画像を複数回呼ぶ場合initでその回数分読み込むべし */

    /*
        どのステージに進むか用の変数
    */
    int STAGE_NUMBER;

    //「Stage」文字用
    _Object _Stage[5];

    // 数字用
    _Object _Number;
    cocos2d::Sprite* num_image;
    int cut_texture;             // 画像切り取り用

    // 矢印用
    _Object _Arrow[2];
    cocos2d::Sprite* upside_arrow_image;
    cocos2d::Sprite* downside_arrow_image;


    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    int sgin;                    // 符号反転用
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