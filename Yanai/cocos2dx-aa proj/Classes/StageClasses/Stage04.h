#ifndef __Stage_04_H__
#define __Stage_04_H__

#include "cocos2d.h"
#include "structure.h"

class Stage04 : public cocos2d::Layer{
private:
    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    //-----�^�b�`�@�\�̒ǉ�-----//
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    bool isTouchBegan;
    bool isTouchMoved;
    bool isTouchEnded;

    // �^�b�`�����ʒu�Ɨ������ʒu��ۑ�
    cocos2d::Point firstTouchPoint;
    cocos2d::Point lastTouchPoint;

    // �^�b�`���Ă���Ԃ̃^�C����ۑ�
    void TouchingTimeCount();
    float timeCount = 0;

    // �^�b�`�����ʒu�Ƙb�����ʒu�̋�����ۑ�
    void DistTouchBeganToEnded();
    float distTouchBeganToEnded;


    //---------(:3=---------//
    cocos2d::Sprite* player_image;
    _Object _Player;
    void PlayerMove();

    //--------�z�c---------//
    enum{
        HUTON_MAX = 20
    };
    cocos2d::Sprite* huton_image[HUTON_MAX];
    _Object _Huton[HUTON_MAX];
    void HutonScene();

public:
    Stage04();

    static cocos2d::Scene* creteScene();
    bool init();
    CREATE_FUNC(Stage04);

    void update(float delta);
};

#endif // __Stage_04_H__