#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "cocos2d.h"

class Manager : public cocos2d::Layer{

public:
    //‰Šú‰»ƒƒ\ƒbƒh
    virtual bool init();
    static cocos2d::Scene* createScene();

    CREATE_FUNC(Manager);

};

#endif /* #define (__MANAGER_H__) */