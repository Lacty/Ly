#ifndef __Stage_Select_SCENE_H__
#define __Stage_Select_SCENE_H__

#include "cocos2d.h"
#include "structure.h"

class StageSelect : public cocos2d::Layer{
private:
    /* �摜�p�ϐ���
       init�̒��Ő錾���Ă���
       ��̉摜�𕡐���Ăԏꍇinit�ł��̉񐔕��ǂݍ��ނׂ� */

    int STAGE_NUMBER;

    _Object _Stage[5];
    _Object _Number;
    cocos2d::Sprite* num_image;
    
    // �摜�؂���p
    int cut_texture;

    _Object _Arrow[2];
    cocos2d::Sprite* upside_arrow_image;
    cocos2d::Sprite* downside_arrow_image;

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    int  sgin;
    cocos2d::Point touchPoint;

public:
    StageSelect();

    static cocos2d::Scene* createScene();
    bool init();         // �`�敔��
    CREATE_FUNC(StageSelect);

    // �����[�v�s���鏈������
    void update(float delta);
};

#endif // __Stage_Select_SCENE_H__