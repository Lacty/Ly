#ifndef __Stage_01_H__
#define __Stage_01_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage01 : public cocos2d::Layer{
private:
    // PlayerOwata��錾getInstance�ɂ��Singleton
    PlayerOwata* owata = &PlayerOwata::getInstance();

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;
    
    //-----------�^�b�`�@�\-----------//
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    //----------�`���[�g���A��----------//
    cocos2d::Sprite* tutorial_image;
    _Object _Tutorial;

    //------------��-------------//
    cocos2d::DrawNode* drawFloor;
    cocos2d::Point startingPoint; // �n�_
    cocos2d::Point endingPoint;   // �I�_
    int weight;                   // ����

    //---------���u���b�N---------//
    _Object _Block[2];
    cocos2d::Sprite* block_image[2];
    // �e���u���b�N�ɓ��������Ƃ��̏����ƌ�������
    void BlockTrigger();
    void BlockMove();
    void BlockColor();
    // �v���C���[���u���b�N�ɂ߂荞�܂Ȃ��悤�ɏ���
    void BlockToPlayer();

    //-----------�S�[��-----------//
    _Object _Goal;
    cocos2d::Sprite* goal_image;
    void GoalScene();

    //--------�I��点�Ă�[-------//
    // Goal��̉��o�Eowata�ɃR�����g
    cocos2d::Sprite* comment_image;

    //------------Pause-----------//
    cocos2d::Sprite* pause_image;
    cocos2d::LayerColor* pause_bg;
    _Object _Pause;
    void Pause();

    //---------�v���C���[�̍X�V����---------//
    void PlayerUpdate();


    //cocos2d::Point touchPoint;
public:
    Stage01();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(Stage01);

    void update(float delta);

};

#endif // __Stage_01_H__