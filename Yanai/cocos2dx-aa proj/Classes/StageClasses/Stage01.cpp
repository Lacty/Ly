
#include "Stage01.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Stage01::createScene()
{
    auto scene = Scene::create();
    auto layer = Stage01::create();
    //auto layer2 = PlayerOwata::create();
    //*owata = *layer2;
    scene->addChild(layer);
    //scene->addChild(layer2);
    return scene;
}


// コンストラクタ
Stage01::Stage01(){
    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を指定
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);


    // なんとなくクリエイトしてみる
    owata = PlayerOwata::create();
    //owata.create();
    owa = false;
}


bool Stage01::init(){

    if ( !Layer::init() )
    {
        return false;
    }
    
    // マルチタッチ操作を有効にする
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(Stage01::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Stage01::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Stage01::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    

    // Updateを呼ぶ
    this->scheduleUpdate();


    // createはしたからaddすればいいんじゃね？
    // ってことでやってみる
    this->addChild(owata);
    // 結果：できちゃった
    // owataのupdate呼んでないけどいいのかな
    // 問題はpause画面が作成できるかどうか

    /*
    Rect rect1 = Rect(0, 0, 60, 60);

    auto sprite1 = Sprite::create();
    sprite1->setTextureRect(rect1);
    sprite1->setColor(Color3B::WHITE);
    sprite1->setPosition(winSize.width/2, winSize.height/2);
    this->addChild(sprite1);

    auto sprite2 = getTag();
    */

    /*
    // この2行でPlayerOwataクラスを呼ぶことができるらしい
    auto playerLayer = PlayerOwata::create();
    addChild(playerLayer);
    */


    return true;
}

// タップした時の処理
void Stage01::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);

        iterator++;
    }
    return;
}

// タップ中（押して動かしたとき）の処理
void Stage01::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

// 指を離したときの処理
void Stage01::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        owa = false;
        iterator++;
    }
    return;
}


void Stage01::update(float delta){
    log("shot.x = %f", owata->_Shots[0].point.x);
}