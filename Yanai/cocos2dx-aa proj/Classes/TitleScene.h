#ifndef __Title_SCENE_H__
#define __Title_SCENE_H__

#include "cocos2d.h"
#include "structure.h"

class Title : public cocos2d::Layer{
private:
    // 画像用変数
    cocos2d::Sprite* start_image;
    cocos2d::Sprite* exit_image;
    cocos2d::Sprite* owata_image;
    cocos2d::Sprite* cloud1;
    cocos2d::Sprite* cloud2;

    // ボタン類の構造体
    _Object START;
    _Object EXIT;
    _Object OWATA;

    cocos2d::Size winSize;
    cocos2d::LayerColor *_bg;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    // 符号反転用
    int  sgin;
    cocos2d::Point touchPoint;

public:
    Title();

    static cocos2d::Scene* createScene();
    virtual bool init(); // 描画部分
    CREATE_FUNC(Title);

    // 毎ループ行われる処理部分
    virtual void update(float delta);
};

#endif // __Title_SCENE_H__
