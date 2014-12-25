#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

class TestLayer : public cocos2d::Layer{

public:
    //初期化メソッド
    virtual bool init();
    static cocos2d::Scene* createScene();
    //create()を使えるようにしている
    CREATE_FUNC(TestLayer);

};

#endif /* defined(__TEST_SCENE_H__) */