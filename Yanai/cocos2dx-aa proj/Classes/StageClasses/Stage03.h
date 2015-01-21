#ifndef __Stage_03_H__
#define __Stage_03_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage03 : public cocos2d::Layer{
private:
    // PlayerOwataを宣言getInstanceによるSingleton
    PlayerOwata* owata = &PlayerOwata::getInstance();

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    //-----------タッチ機能-----------//
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    //----------PlayerUpdate---------//
    void PlayerUpdate();

public:
    Stage03();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(Stage03);

    void update(float delta);

};

#endif // __Stage_03_H__