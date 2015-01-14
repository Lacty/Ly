#ifndef __Stage_01_H__
#define __Stage_01_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage01 : public cocos2d::Layer{
private:
    // PlayerOwataを宣言getInstanceによるSingleton
    PlayerOwata* owata = &PlayerOwata::getInstance();

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;
    
    //-----------タッチ機能-----------//
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    //------------床-------------//
    cocos2d::DrawNode* drawFloor;
    cocos2d::Point startingPoint; // 始点
    cocos2d::Point endingPoint;   // 終点
    int weight;                   // 太さ

    //-----------ゴール-----------//
    _Object _Goal;
    cocos2d::Sprite* goal_image;


    //cocos2d::Point touchPoint;
public:
    Stage01();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(Stage01);

    void update(float delta);

};

#endif // __Stage_01_H__