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
    _Object _Shots[SHOT_MAX];

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);


    // ‰æ–ÊƒTƒCƒY‚ğæ“¾‚·‚é•Ï”
    cocos2d::Size winSize;

public:
    PlayerOwata();

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PlayerOwata);

    virtual void update(float delta);

};

#endif // __Player_Owata_H__