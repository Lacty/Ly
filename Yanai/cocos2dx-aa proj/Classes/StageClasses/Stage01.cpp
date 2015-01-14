
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

    // クリエイト
    owata = PlayerOwata::create();

    // 床の始点と終点を決定する
    startingPoint = Point(0, winSize.height/4);
    endingPoint   = Point(winSize.width, winSize.height/4);
    // 床の線の太さを決定
    weight = 5;

    // _Goalをとりあえず初期化
    _Goal = { false,
        Point(0, 0), Size(0, 0),
        Point(0, 0), Size(300, 200),
        1,
        Color3B::WHITE, 255,
        true,
        0, 0, 0, 0
    };
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

    // owata(Player)の実装
    this->addChild(owata);

    // 床の描画
    drawFloor = DrawNode::create();
    drawFloor->drawSegment(startingPoint, endingPoint, weight, Color4F::BLACK);
    this->addChild(drawFloor);

    // 樹海の描画
    _Goal.size = Size(_Goal.tx_size.width * _Goal.scale,
                      _Goal.tx_size.height * _Goal.scale);
    _Goal.point = Point(winSize.width - _Goal.size.width - _Goal.size.width/30,
                        winSize.height/4);

    goal_image = Sprite::create("stage01_image.png");
    goal_image->setPosition(_Goal.point);
    goal_image->setTextureRect(Rect(_Goal.tx_point.x, _Goal.tx_point.y,
                                    _Goal.tx_size.width, _Goal.tx_size.height));
    goal_image->setAnchorPoint(Point(0, 0));
    goal_image->setScale(_Goal.scale);
    this->addChild(goal_image);

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

        iterator++;
    }
    return;
}


void Stage01::update(float delta){
    log("shot.x = %f", owata->_Shots[0].point.x);
}