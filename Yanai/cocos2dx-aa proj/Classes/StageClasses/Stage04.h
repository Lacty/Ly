#ifndef __Stage_04_H__
#define __Stage_04_H__

#include "cocos2d.h"
#include "structure.h"

class Stage04 : public cocos2d::Layer{
private:
    cocos2d::Size winSize;
    cocos2d::LayerColor* _bg;

    //-----タッチ機能の追加-----//
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    bool isTouchBegan;
    bool isTouchMoved;
    bool isTouchEnded;
    bool isInit;

    // タッチした位置と離した位置を保存
    cocos2d::Point firstTouchPoint;
    cocos2d::Point lastTouchPoint;

    // タッチしている間のタイムを保存
    void TouchingTimeCount();
    float timeTouchCount;
    float timeCount;

    // タッチした位置と話した位置の距離を保存
    void DistTouchBeganToEnded();
    float distTouchBeganToEnded;


    //---------(:3=---------//
    cocos2d::Sprite* player_image;
    _Object _Player;
    void PlayerScene();
    void PlayerUpdate();


    //--------布団---------//
    enum{
        HUTON_MAX = 40
    };
    cocos2d::Sprite* huton_image[HUTON_MAX];
    _Object _Huton[HUTON_MAX];
    void HutonScene();
    void HutonUpdate();
    void HutonTrigger();
    bool hutonTrigger1;
    bool hutonTrigger2;
    int randNum[HUTON_MAX]; // ランダムな値を取得


    enum {
        // スコアの桁数
        NUM_MAX = 3
    };
    _Object _Score[NUM_MAX];
    cocos2d::Sprite* score_image[NUM_MAX];
    void ScoreSetTextureRect();
    int play_score;

    // 背景用の雲
    enum{
        CLOUD_MAX = 4
    };
    _Object _Cloud[CLOUD_MAX];
    cocos2d::Sprite* cloud_image[CLOUD_MAX];
    void CloudMove();


    //-----ゲーム終了後-----//
    // 画面にかぶせる背景
    _Object _Result_bg;
    cocos2d::LayerColor* result_bg;
    int result_bg_Opacity;
    void ResultTrigger();
    void ResultSetVisible();

    // リスタート
    _Object _ReStart;
    cocos2d::Sprite* restart_image;
    void ReStartSetVisible();
    void ReStartSetColor();
    bool isTouchReStart;

    // ステージ選択に戻る
    _Object _BackToStageSelect;
    cocos2d::Sprite* backtoSS_image;
    void BackToStageSelectSetVisible();
    void BackToStageSelectSetColor();
    bool isTouchBackToStageSelect;

public:
    Stage04();

    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(Stage04);

    void update(float delta);
};

#endif // __Stage_04_H__