#ifndef __Title_SCENE_H__
#define __Title_SCENE_H__

#include "cocos2d.h"
#include "structure.h"

class Title : public cocos2d::Layer{
private:
    // �摜�p�ϐ�
    cocos2d::Sprite* start_image;
    cocos2d::Sprite* exit_image;
    cocos2d::Sprite* owata_image;
    cocos2d::Sprite* cloud1;
    cocos2d::Sprite* cloud2;

    // �{�^���ނ̍\����
    _Object START;
    _Object EXIT;
    _Object OWATA;

    cocos2d::Size winSize;
    cocos2d::LayerColor *_bg;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    // �������]�p
    int  sgin;
    cocos2d::Point touchPoint;

public:
    Title();

    static cocos2d::Scene* createScene();
    virtual bool init(); // �`�敔��
    CREATE_FUNC(Title);

    // �����[�v�s���鏈������
    virtual void update(float delta);
};

#endif // __Title_SCENE_H__
