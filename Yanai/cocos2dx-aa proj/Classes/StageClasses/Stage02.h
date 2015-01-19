#ifndef __Stage_02_H__
#define __Stage_02_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage02 : public cocos2d::Layer{
private:
    // PlayerOwata��錾getInstance�ɂ��Singleton
    PlayerOwata* owata = &PlayerOwata::getInstance();

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    //-----------�^�b�`�@�\-----------//
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    //------------��-------------//
    cocos2d::DrawNode* drawFloor[2];
    cocos2d::Point startingPoint[2]; // �n�_
    cocos2d::Point endingPoint[2];   // �I�_
    int weight;                      // ����

    //---------���u���b�N---------//
    enum {
        BLOCK_MAX = 5
    };
    _Object _Block[BLOCK_MAX];
    cocos2d::Sprite* block_image[BLOCK_MAX];
    // �e���u���b�N�ɓ��������Ƃ��̏����ƌ�������
    void BlockTrigger();
    void BlockMove();
    void BlockColor();
    // �v���C���[���u���b�N�ɂ߂荞�܂Ȃ��悤�ɏ���
    void BlockToPlayer();

    //---------���[�v�u���b�N---------//
    enum {
        WARP_MAX = 4
    };
    _Object _Warp_Block[WARP_MAX];

    //-----------�S�[��-----------//
    _Object _Goal;
    cocos2d::Sprite* goal_image;
    void GoalScene();

    //---------�v���C���[�̍X�V����---------//
    void PlayerUpdate();

    //------------Pause-----------//
    cocos2d::Sprite* pause_image;
    cocos2d::LayerColor* pause_bg;
    _Object _Pause;
    void Pause();

public:
    Stage02();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(Stage02);

    void update(float delta);
};

#endif // __Stage_02_H__