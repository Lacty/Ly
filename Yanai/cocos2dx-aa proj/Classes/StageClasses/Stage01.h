#ifndef __Stage_01_H__
#define __Stage_01_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage01 : public cocos2d::Layer{
private:

    // ���߂���PlayerOwata���Ă�ł݂�
    // *����Ƃ����݂����H
    PlayerOwata* owata = &PlayerOwata::getInstance();
    //cocos2d::Scene* owata;
    bool owa;

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    

    //cocos2d::Point touchPoint;
public:
    Stage01();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(Stage01);

    void update(float delta);

    float owata_x;
};

#endif // __Stage_01_H__