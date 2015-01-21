
#include "StageSelectScene.h"
#include "Stage03.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Stage03::createScene()
{
    auto scene = Scene::create();
    auto layer = Stage03::create();
    scene->addChild(layer);
    return scene;
}


// コンストラクタ
Stage03::Stage03(){
    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を指定
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    // owataのクリエイト
    owata = PlayerOwata::create();
}


bool Stage03::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }

    // マルチタッチ操作を有効にする
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(Stage03::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Stage03::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Stage03::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // Updateを呼ぶ
    this->scheduleUpdate();

    // owata(Player)の実装
    this->addChild(owata);

    return true;
}

// タップした時の処理
void Stage03::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);


        iterator++;
    }
    return;
}

// タップ中（押して動かしたとき）の処理
void Stage03::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

// 指を離したときの処理
void Stage03::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

void Stage03::PlayerUpdate(){
    owata->owata_image->setPosition(owata->_Owata.point);
}

void Stage03::update(float delta){

    PlayerUpdate();
}