#ifndef __Stage_01_H__
#define __Stage_01_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage01 : public cocos2d::Layer{
private:
    /* プレイヤーに関係するもの
    cocos2d::Sprite* owata_image;
    _Object _Owata;
    bool isPushRight;
    bool isPushLeft;
    void owataMove();
    void owataSetTextureRect();

    enum{
        // 発射最大数
        SHOT_MAX = 2
    };
    _Object _Shots[SHOT_MAX];
    */

    // ためしにPlayerOwataを呼んでみる
    // *つけるといいみたい？
    PlayerOwata* owata;

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    

    //cocos2d::Point touchPoint;
public:
    Stage01();

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Stage01);

    virtual void update(float delta);

};

#endif // __Stage_01_H__