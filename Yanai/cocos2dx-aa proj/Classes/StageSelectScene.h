#ifndef __Stage_Select_SCENE_H__
#define __Stage_Select_SCENE_H__

#include "cocos2d.h"
#include "structure.h"

class StageSelect : public cocos2d::Layer{
private:
    /* �摜�p�ϐ�
       init�̒��Ő錾���Ă���
       ��̉摜�𕡐���Ăԏꍇinit�ł��̉񐔕��ǂݍ��ނׂ� */

    /*
        �ǂ̃X�e�[�W�ɐi�ނ��p�̕ϐ�
    */
    int STAGE_NUMBER;

    //�uStage�v�����p
    _Object _Stage[5];

    // �����p
    _Object _Number;
    cocos2d::Sprite* num_image;
    int cut_texture;             // �摜�؂���p

    // ���p
    _Object _Arrow[2];
    cocos2d::Sprite* upside_arrow_image;
    cocos2d::Sprite* downside_arrow_image;


    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    int sgin;                    // �������]�p
    cocos2d::Point touchPoint;

public:
    StageSelect();

    static cocos2d::Scene* createScene();
    virtual bool init();         // �`�敔��
    CREATE_FUNC(StageSelect);

    // �����[�v�s���鏈������
    virtual void update(float delta);
};

#endif // __Stage_Select_SCENE_H__