
#include "Stage01.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Stage01::createScene()
{
    auto scene = Scene::create();
    auto layer = Stage01::create();
    scene->addChild(layer);
    return scene;
}


// コンストラクタ
Stage01::Stage01(){
    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を指定
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    sgin = -1;
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
    
    // 文字の表示
    x = 0;
    y = 0;

    text = LabelTTF::create("Stage01", "Arial", 50);
    text->setPosition(Point(x, y));
    this->addChild(text);

    return true;
}


void Stage01::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        touchPoint = touch->getLocation();

        iterator++;
    }
    log("touchPoint.x=%f, touchPoint.y=%f", touchPoint.x, touchPoint.y);
    x = touchPoint.x;
    y = touchPoint.y;
    text->setPosition(x, y);
    return;
}

void Stage01::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        touchPoint = touch->getLocation();

        iterator++;
    }
    return;
}

void Stage01::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        touchPoint = touch->getLocation();

        iterator++;
    }
    return;
}