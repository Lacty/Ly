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
        BLOCK_MAX = 2
    };
    _Object _Block[BLOCK_MAX];
    cocos2d::Sprite* block_image[BLOCK_MAX];

    //---------���[�v�u���b�N---------//
    enum {
        WARP_MAX = 4,
        A = 0,
        B = 1,
        C = 2,
        D = 3
    };
    _Object _WarpBlock[WARP_MAX];
    cocos2d::Sprite* warp_image[WARP_MAX];
    cocos2d::Sprite* abcd_image[WARP_MAX];
    void WarpTrigger();

    //----------�㉺����u���b�N----------//
    enum {
        MOVING_BLOCK_MAX = 2
    };
    _Object _MovingBlock[MOVING_BLOCK_MAX];
    cocos2d::Sprite* moving_block_image[MOVING_BLOCK_MAX];

    //------------�I-------------//
    _Object _Target;
    cocos2d::Sprite* target_image;


    //---------�e�u���b�N�̂����蔻��Ȃ�---------//
    void BlockTrigger();
    void BlockMove();
    void BlockColor();
    // �v���C���[�ƃu���b�N�̂����蔻��
    void BlockToPlayer();

    //-----------�S�[��-----------//
    _Object _Goal;
    cocos2d::Sprite* goal_image;
    void GoalScene();

    //--------���傗������-------//
    // Goal��̉��o�Eowata�ɃR�����g
    cocos2d::Sprite* comment_image;

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