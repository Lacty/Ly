
#include "StageSelectScene.h"
#include "Stage04.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Stage04::creteScene()
{
    auto scene = Scene::create();
    auto layer = Stage04::create();
    scene->addChild(layer);
    return scene;
}


// コンストラクタ
Stage04::Stage04(){
    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を指定
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    // _Playerの初期化
    _Player = { true,
        Point(0, 0), Size(400, 200),
        Point(200, 0), Size(400, 200),
        1,
        Color3B::WHITE, 255,
        true,
        0, 0, 0, 0
    };

    // _Hutonの初期化
    for (int i = 0; i < HUTON_MAX; i++){
        _Huton[i] = { false,
            Point(winSize.width + 150, winSize.height/2), Size(0, 0),
            Point(0, 200), Size(300, 200),
            1,
            Color3B::WHITE, 255,
            true,
            0, 0, 0, 0
        };
    }

    isTouchBegan = false;
    isTouchMoved = false;
    isTouchEnded = false;
}


bool Stage04::init(){

    if ( !Layer::init() )
    {
        return false;
    }

    // タッチ機能の追加
    auto listener = EventListenerTouchOneByOne::create();
    listener->setEnabled(true);
    listener->onTouchBegan = CC_CALLBACK_2(Stage04::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Stage04::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Stage04::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // updateを呼ぶ
    this->scheduleUpdate();

    //--------(:3=---------//
    _Player.point = Point(_Player.size.width/2, winSize.height/2);
    player_image = Sprite::create("stage04_image.png");
    player_image->setPosition(_Player.point);
    player_image->setTextureRect(Rect(_Player.tx_point.x, _Player.tx_point.y,
                                      _Player.tx_size.width, _Player.tx_size.height));
    player_image->setColor(_Player.col);
    this->addChild(player_image);

    //---------布団---------//
    for (int i = 0; i < HUTON_MAX; i++){
        _Huton[0].point = Point(winSize.width/4*3, winSize.height/2);

        huton_image[i] = Sprite::create("stage04_image.png");
        huton_image[i]->setPosition(_Huton[i].point);
        huton_image[i]->setTextureRect(Rect(_Huton[i].tx_point.x, _Huton[i].tx_point.y,
                                            _Huton[i].tx_size.width, _Huton[i].tx_size.height));
        huton_image[i]->setColor(_Huton[i].col);
        this->addChild(huton_image[i]);
    }


    return true;
}

bool Stage04::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    auto location = touch->getLocation();
    log("location.x = %f, location.y = %f", location.x, location.y);

    if (_Player.active){
        // 画面左半分内のみの移動制限
        if (location.x < winSize.width/2){
            _Player.point.x = location.x;
            firstTouchPoint = location;
        }

        isTouchBegan = true;
    }

    return true;
}

void Stage04::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
    auto location = touch->getLocation();

    if (_Player.active){
        // 画面左半分内のみの移動制限
        if (location.x < winSize.width / 2){
            _Player.point.x = location.x;
        }
    }
}

void Stage04::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
    auto location = touch->getLocation();

    if (_Player.active){
        lastTouchPoint = location;
        isTouchEnded = true;
        _Player.active = false;
    }

}

void Stage04::TouchingTimeCount(){

    if (!isTouchEnded){
        if (isTouchBegan){
            timeCount += 1;
            log("timeCount = %f", timeCount);
        }
    }
}

void Stage04::DistTouchBeganToEnded(){
    if (isTouchEnded){
        distTouchBeganToEnded = lastTouchPoint.x - firstTouchPoint.x;
        log("distTouchBeganToEnded = %f", distTouchBeganToEnded);
    }
}

void Stage04::PlayerMove(){
    player_image->setPosition(_Player.point);
}

void Stage04::update(float delta){
    PlayerMove();
    TouchingTimeCount();
    DistTouchBeganToEnded();
}