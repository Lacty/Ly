#ifndef __Stage_03_H__
#define __Stage_03_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage03 : public cocos2d::Layer{
private:
    // PlayerOwataを宣言getInstanceによるSingleton
    PlayerOwata* owata = &PlayerOwata::getInstance();

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    //-----------タッチ機能-----------//
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    //------------床-------------//
    cocos2d::DrawNode* drawFloor[2];
    cocos2d::Point floorStartingPoint[2]; // 始点
    cocos2d::Point floorEndingPoint[2];   // 終点
    int floorWeight;                      // 太さ

    //-----------WallBlock-----------//
    cocos2d::Sprite* wall_image;
    _Object _WallBlock;

    //----------Button---------//
    _Object _Button;
    cocos2d::Sprite* button_image;

    //----------Block----------//
    enum {
        BLOCK_MAX = 4
    };
    _Object _Block[BLOCK_MAX];
    cocos2d::Sprite* block_image[BLOCK_MAX];

    //---------ワープブロック---------//
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

    //----------看板(就職)----------//
    cocos2d::Sprite* signboard_image;
    _Object _SignBoard;
    void SignBoard();

    //---------各ブロックのあたり判定など---------//
    void BlockTrigger();
    void BlockMove();
    void BlockColor();
    // プレイヤーとブロックのあたり判定
    void BlockToPlayer();

    //----------PlayerUpdate---------//
    void PlayerUpdate();

    //------現実からは逃げられない------//
    cocos2d::Sprite* real_image;

    //------------Pause-----------//
    cocos2d::Sprite* pause_image;
    cocos2d::LayerColor* pause_bg;
    _Object _Pause;
    void Pause();

public:
    Stage03();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(Stage03);

    void update(float delta);

};

#endif // __Stage_03_H__