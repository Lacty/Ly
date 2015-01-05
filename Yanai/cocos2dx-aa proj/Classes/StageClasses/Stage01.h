#ifndef __Stage_01_H__
#define __Stage_01_H__

#include "cocos2d.h"

class Stage01 : public cocos2d::Layer{
private:
    cocos2d::LabelTTF* text;
    int x;
    int y;

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    int sgin;
    cocos2d::Point touchPoint;
public:
    Stage01();

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Stage01);

    //virtual void update(float delta);

};

#endif // __Stage_01_H__