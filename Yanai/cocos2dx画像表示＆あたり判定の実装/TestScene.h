#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

class TestLayer : public cocos2d::Layer{

public:
    //���������\�b�h
    virtual bool init();
    static cocos2d::Scene* createScene();
    //create()���g����悤�ɂ��Ă���
    CREATE_FUNC(TestLayer);

};

#endif /* defined(__TEST_SCENE_H__) */