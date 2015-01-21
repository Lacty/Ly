#ifndef __Player_Owata_H__
#define __Player_Owata_H__

#include "cocos2d.h"
#include "structure.h"

class PlayerOwata : public cocos2d::Layer{
private:
    //------プレイヤーのステータス関係------//
    void owataMove();
    void owataSetTextureRect();

    //------------弾関係------------//
    enum{
        // 発射最大数
        SHOT_MAX = 2
    };
    void owataShot();
    _Object _ShotButton;
    cocos2d::Sprite* shot_button_image;

    //----------タッチ機能----------//
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    bool isTouchShotButton;


    //------------方向キー-----------//
    enum {
        BUTTON_MAX = 2,
        RIGHT      = 0,
        LEFT       = 1
    };
    cocos2d::Sprite* button_image[BUTTON_MAX];
    _Object _Button[BUTTON_MAX];
    void setButtonColor();

    // 画面サイズを取得する変数
    cocos2d::Size winSize;

    // 他でnewされないようにprivateに置く
    PlayerOwata();

public:
    // Singleton
    static PlayerOwata& getInstance();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(PlayerOwata);

    void update(float delta);


    // 他で触れるように構造体をpublicに置く
    _Object _Owata;
    _Object _Shots[SHOT_MAX];

    // プレイヤーの画像&移動ボタンの制御もPublicに置く
    cocos2d::Sprite* owata_image;
    cocos2d::Sprite* gun_image[SHOT_MAX];
    bool isPushRight;
    bool isPushLeft;

    // pause画面用変数
    bool pause;
};

#endif // __Player_Owata_H__