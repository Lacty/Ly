#ifndef __Player_Owata_H__
#define __Player_Owata_H__

#include "cocos2d.h"
#include "structure.h"

class PlayerOwata : public cocos2d::Layer{
private:
    //------�v���C���[�̃X�e�[�^�X�֌W------//
    void owataMove();
    void owataSetTextureRect();

    //------------�e�֌W------------//
    enum{
        // ���ˍő吔
        SHOT_MAX = 2
    };
    void owataShot();
    _Object _ShotButton;
    cocos2d::Sprite* shot_button_image;

    //----------�^�b�`�@�\----------//
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    bool isTouchShotButton;


    //------------�����L�[-----------//
    enum {
        BUTTON_MAX = 2,
        RIGHT      = 0,
        LEFT       = 1
    };
    cocos2d::Sprite* button_image[BUTTON_MAX];
    _Object _Button[BUTTON_MAX];
    void setButtonColor();

    // ��ʃT�C�Y���擾����ϐ�
    cocos2d::Size winSize;

    // ����new����Ȃ��悤��private�ɒu��
    PlayerOwata();

public:
    // Singleton
    static PlayerOwata& getInstance();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(PlayerOwata);

    void update(float delta);


    // ���ŐG���悤�ɍ\���̂�public�ɒu��
    _Object _Owata;
    _Object _Shots[SHOT_MAX];

    // �v���C���[�̉摜&�ړ��{�^���̐����Public�ɒu��
    cocos2d::Sprite* owata_image;
    cocos2d::Sprite* gun_image[SHOT_MAX];
    bool isPushRight;
    bool isPushLeft;

    // pause��ʗp�ϐ�
    bool pause;
};

#endif // __Player_Owata_H__