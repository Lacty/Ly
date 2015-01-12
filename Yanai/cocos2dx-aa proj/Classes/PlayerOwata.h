#ifndef __Player_Owata_H__
#define __Player_Owata_H__

#include "cocos2d.h"
#include "structure.h"

class PlayerOwata : public cocos2d::Layer{
private:
    cocos2d::Sprite* owata_image;
    _Object _Owata;
    bool isPushRight;
    bool isPushLeft;
    void owataMove();
    void owataSetTextureRect();

    enum{
        // ”­ËÅ‘å”
        SHOT_MAX = 2
    };
    
    void owataShot();
    cocos2d::Sprite* gun_image[SHOT_MAX];

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    bool isTouchShotButton;

    // ‰æ–ÊƒTƒCƒY‚ğæ“¾‚·‚é•Ï”
    cocos2d::Size winSize;


    PlayerOwata();
public:
    static PlayerOwata& getInstance();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(PlayerOwata);

    void update(float delta);

    float* getShotPosX(int n);

    _Object _Shots[SHOT_MAX];
};

#endif // __Player_Owata_H__