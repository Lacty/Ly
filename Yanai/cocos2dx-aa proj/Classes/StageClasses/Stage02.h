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
        BLOCK_MAX = 5
    };
    _Object _Block[BLOCK_MAX];
    cocos2d::Sprite* block_image[BLOCK_MAX];
    // 弾がブロックに当たったときの処理と言いたい
    void BlockTrigger();
    void BlockMove();
    void BlockColor();
    // プレイヤーがブロックにめり込まないように処理
    void BlockToPlayer();

    //---------ワープブロック---------//
    enum {
        WARP_MAX = 4
    };
    _Object _Warp_Block[WARP_MAX];

    //-----------ゴール-----------//
    _Object _Goal;
    cocos2d::Sprite* goal_image;
    void GoalScene();

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