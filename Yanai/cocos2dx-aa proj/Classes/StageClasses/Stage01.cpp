
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

    /*
    // _Owataをとりあえず初期化
    _Owata = { true,
               Point(0, 0), Size(0, 0),
               Point(0, 0), Size(200, 100),
               1,
               Color3B::WHITE, 255,
               true,
               0, 0, 0, 3 };

    // _Shotsをとりあえず初期化
    for (int i = 2; i < 2; i++){
        _Shots[i] = { true,
                      Point(0, 0), Size(0, 0),
                      Point(0, 0), Size(0, 0),
                      1,
                      Color3B::WHITE, 255,
                      true,
                      0, 0, 0, 0 };
    }
    */


    // なんとなくクリエイトしてみる
    owata = PlayerOwata::create();
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
    // オワタの描画
    owata_image = Sprite::create("player_image.png");
    // ステータスの初期化
    owata_image->setPosition(_Owata.point);
    owata_image->setTextureRect(Rect(_Owata.tx_point.x, _Owata.tx_point.y,
                                     _Owata.tx_size.width, _Owata.tx_size.height));
    owata_image->setScale(_Owata.scale);
    owata_image->setAnchorPoint(Point(0, 0));
    this->addChild(owata_image);

    // 実際に描画されている画像のサイズを取得
    _Owata.size = Size(_Owata.tx_size.width  * _Owata.scale,
                       _Owata.tx_size.height * _Owata.scale);
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
        /*
        if (point_to_rect(location.x, location.y, 0, 0, winSize.width / 4, winSize.height)){
            //_Owata.point.x -= _Owata.speed;
            isPushRight  = false;
            isPushLeft   = true;
            _Owata.right = false;
        }
        if (point_to_rect(location.x, location.y, winSize.width / 4, 0, winSize.width / 4, winSize.height)){
            //_Owata.point.x += _Owata.speed;
            isPushRight  = true;
            isPushLeft   = false;
            _Owata.right = true;
        }
        */
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

        /*
        if (point_to_rect(location.x, location.y, 0, 0, winSize.width / 4, winSize.height)){
            //_Owata.point.x -= _Owata.speed;
            isPushRight  = false;
            isPushLeft   = true;
            _Owata.right = false;
        }
        if (point_to_rect(location.x, location.y, winSize.width / 4, 0, winSize.width / 4, winSize.height)){
            //_Owata.point.x += _Owata.speed;
            isPushRight  = true;
            isPushLeft   = false;
            _Owata.right = true;
        }
        if (point_to_rect(location.x, location.y, winSize.width / 2, 0, winSize.width/4, winSize.height)){
            isPushRight  = false;
            isPushLeft   = false;
        }
        */

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

        /*
        if (point_to_rect(location.x, location.y, 0, 0, winSize.width / 2, winSize.height)){
            isPushRight = false;
            isPushLeft  = false;
        }
        */

        iterator++;
    }
    return;
}

/*
// オワタの移動制御
void Stage01::owataMove(){
    // 画面外に出ないように移動制御
    if (_Owata.point.x < 0){
        isPushLeft  = false;
    }
    if ((_Owata.point.x + _Owata.size.width) > winSize.width){
        isPushRight = false;
    }

    // 押されている方向に移動させる
    if (isPushRight){
        _Owata.point.x += _Owata.speed;
    }
    if (isPushLeft){
        _Owata.point.x -= _Owata.speed;
    }

    // オワタの位置を反映させる
    owata_image->setPosition(_Owata.point);
}

// オワタの画像切り替え
void Stage01::owataSetTextureRect(){

    if (_Owata.right){
        _Owata.tx_point = Point(0, 0);
    } else{
        _Owata.tx_point = Point(200, 0);
    }

    // 切り替えた画像の切り出し位置を反映させる
    owata_image->setTextureRect(Rect(_Owata.tx_point.x, _Owata.tx_point.y,
                                     _Owata.tx_size.width, _Owata.tx_size.height));
}
*/


void Stage01::update(float delta){
    /*
    // 関数呼び出し
    owataMove();
    owataSetTextureRect();
    */
}