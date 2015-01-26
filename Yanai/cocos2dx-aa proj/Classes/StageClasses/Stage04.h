#ifndef __Stage_04_H__
#define __Stage_04_H__

#include "cocos2d.h"
#include "structure.h"

class Stage04 : public cocos2d::Layer{
private:
    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    //-----タッチ機能の追加-----//
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    bool isTouchBegan;
    bool isTouchMoved;
    bool isTouchEnded;
    bool isInit;

    // タッチした位置と離した位置を保存
    cocos2d::Point firstTouchPoint;
    cocos2d::Point lastTouchPoint;

    // タッチしている間のタイムを保存
    void TouchingTimeCount();
    float timeTouchCount;
    float timeCount;

    // タッチした位置と話した位置の距離を保存
    void DistTouchBeganToEnded();
    float distTouchBeganToEnded;


    //---------(:3=---------//
    cocos2d::Sprite* player_image;
    _Object _Player;
    void PlayerScene();
    void PlayerUpdate();

    //--------布団---------//
    enum{
        HUTON_MAX = 30
    };
    cocos2d::Sprite* huton_image[HUTON_MAX];
    _Object _Huton[HUTON_MAX];
    void HutonScene();
    void HutonUpdate();
    void HutonTrigger();
    bool hutonTrigger1;
    bool hutonTrigger2;

public:
    Stage04();

    static cocos2d::Scene* creteScene();
    bool init();
    CREATE_FUNC(Stage04);

    void update(float delta);
};

#endif // __Stage_04_H__