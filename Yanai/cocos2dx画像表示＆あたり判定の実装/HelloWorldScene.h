#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);


    virtual void update(float delta);

    HelloWorld();

    cocos2d::LabelTTF *label;
    cocos2d::Sprite *button_image1;
    cocos2d::Sprite *button_image2;
    bool imageVisible;

    cocos2d::Point image1;
    cocos2d::Point image2;
    cocos2d::Size image_1;
    cocos2d::Size image_2;

    float tex_x;
    float tex_y;
};

#endif // __HELLOWORLD_SCENE_H__
