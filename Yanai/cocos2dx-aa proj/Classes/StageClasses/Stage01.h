#ifndef __Stage_01_H__
#define __Stage_01_H__

#include "cocos2d.h"
#include "structure.h"

#include "PlayerOwata.h"

class Stage01 : public cocos2d::Layer{
private:
    // PlayerOwataを宣言getInstanceによるSingleton
    PlayerOwata* owata = &PlayerOwata::getInstance();

    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;
    
    //-----------タッチ機能-----------//
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    //----------チュートリアル----------//
    cocos2d::Sprite* tutorial_image;
    _Object _Tutorial;

    //------------床-------------//
    cocos2d::DrawNode* drawFloor;
    cocos2d::Point startingPoint; // 始点
    cocos2d::Point endingPoint;   // 終点
    int weight;                   // 太さ

    //---------矢印ブロック---------//
    _Object _Block[2];
    cocos2d::Sprite* block_image[2];
    // 弾がブロックに当たったときの処理と言いたい
    void BlockTrigger();
    void BlockMove();
    void BlockColor();
    // プレイヤーがブロックにめり込まないように処理
    void BlockToPlayer();

    //-----------ゴール-----------//
    _Object _Goal;
    cocos2d::Sprite* goal_image;
    void GoalScene();

    //--------終わらせてよー-------//
    // Goal後の演出・owataにコメント
    cocos2d::Sprite* comment_image;

    //------------Pause-----------//
    cocos2d::Sprite* pause_image;
    cocos2d::LayerColor* pause_bg;
    _Object _Pause;
    void Pause();

    //---------プレイヤーの更新処理---------//
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