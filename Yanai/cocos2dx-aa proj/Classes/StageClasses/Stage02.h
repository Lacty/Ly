#ifndef __Stage_02_H__
#define __Stage_02_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage02 : public cocos2d::Layer{
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
    cocos2d::Point startingPoint[2]; // 始点
    cocos2d::Point endingPoint[2];   // 終点
    int weight;                      // 太さ

    //---------矢印ブロック---------//
    enum {
        BLOCK_MAX = 2
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

    //----------上下するブロック----------//
    enum {
        MOVING_BLOCK_MAX = 2
    };
    _Object _MovingBlock[MOVING_BLOCK_MAX];
    cocos2d::Sprite* moving_block_image[MOVING_BLOCK_MAX];

    //------------的-------------//
    _Object _Target;
    cocos2d::Sprite* target_image;


    //---------各ブロックのあたり判定など---------//
    void BlockTrigger();
    void BlockMove();
    void BlockColor();
    // プレイヤーとブロックのあたり判定
    void BlockToPlayer();

    //-----------ゴール-----------//
    _Object _Goal;
    cocos2d::Sprite* goal_image;
    void GoalScene();

    //--------ちょｗｗｗｗ-------//
    // Goal後の演出・owataにコメント
    cocos2d::Sprite* comment_image;

    //---------プレイヤーの更新処理---------//
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