
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
    // activeがtrueになってから流れるようにするために
    // 始めはfalseにしておく
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

    timeTouchCount = 0;
    timeCount = 0;

    isInit = false;

    hutonTrigger1 = false;
    hutonTrigger2 = false;
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

        isTouchMoved = true;
    }
}

void Stage04::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
    auto location = touch->getLocation();

    if (_Player.active){
        if (location.x >= winSize.width / 2){
            lastTouchPoint = location;
            isTouchEnded = true;
            _Player.active = false;
        } else {
            timeTouchCount = 0;
            isTouchMoved = false;
        }
    }

}

void Stage04::TouchingTimeCount(){
    if (!isTouchEnded){
        if (isTouchMoved){
            timeTouchCount += 1;
            log("timeTouchCount = %f", timeTouchCount);
        }
    }
}

void Stage04::DistTouchBeganToEnded(){
    if (isTouchEnded && !isInit){
        distTouchBeganToEnded = (lastTouchPoint.x - firstTouchPoint.x) > 400 ?
            400 : lastTouchPoint.x - firstTouchPoint.x;
        log("distTouchBeganToEnded = %f", distTouchBeganToEnded);
    }
}

void Stage04::HutonScene(){
    // 指を離したときに初めの布団をactiveにする
    if (isTouchEnded && !isInit){
        _Huton[0].active = true;
        isInit = true;
    }

    // Hutonのスピード
    for (int i = 0; i < HUTON_MAX; i++){
        _Huton[i].speed = (distTouchBeganToEnded - timeTouchCount*8) > 0 ?
            distTouchBeganToEnded - timeTouchCount * 8 : 0;
    }
    if (distTouchBeganToEnded > 0){
        distTouchBeganToEnded--;
    }
    //timeCount++;
    log("distTouchBeganToEnded = %f", distTouchBeganToEnded);

    for (int i = 0; i < HUTON_MAX; i++){
        if (_Huton[i].active){
            _Huton[i].point.x -= _Huton[i].speed;
            
            if (_Huton[i].point.x <= _Player.point.x){
                _Huton[i].point.x = _Player.point.x;

                _Huton[i].tx_size = Size(500, 200); // 切り取り位置の変更
                _Huton[i].point.y += 6;             // 画像の移動
                _Huton[i].visi -= 6;                // 透過度の変更

                // 布団が消える処理
                if (_Huton[i].visi <= 0){
                    _Huton[i].point = Point(winSize.width + 150, winSize.height/2);
                    _Huton[i].tx_size = Point(300, 200);
                    _Huton[i].visi = 255;
                    _Huton[i].active = false;
                }
            }
        }
    }
}

// 布団を流すトリガー
void Stage04::HutonTrigger(){
    for (int i = 0; i < HUTON_MAX; i++){
        if (_Huton[i].active){
            if (_Huton[i].point.x < winSize.width / 4 * 3){
                hutonTrigger1 = true;
            }
            else{
                hutonTrigger1 = false;
            }
        }
        if (_Huton[i].point.x > winSize.width / 4 * 3){
            if (!_Huton[i].active){
                hutonTrigger2 = true;
            }
            else{
                hutonTrigger2 = false;
            }
        }
        if (hutonTrigger1 && hutonTrigger2){
            if (!_Huton[i].active){
                _Huton[i].active = true;
                hutonTrigger1 = false;
                hutonTrigger2 = false;
                break;
            }
        }
    }
}

void Stage04::PlayerScene(){
    if (!_Player.active){
        _Player.tx_point = Point(0, 0);
        _Player.tx_size = Size(600, 200);
    }
}

void Stage04::HutonUpdate(){
    for (int i = 0; i < HUTON_MAX; i++){
        huton_image[i]->setPosition(_Huton[i].point);
        huton_image[i]->setTextureRect(Rect(_Huton[i].tx_point.x, _Huton[i].tx_point.y,
                                            _Huton[i].tx_size.width, _Huton[i].tx_size.height));
        huton_image[i]->setOpacity(_Huton[i].visi); // 透過度
    }
}

void Stage04::PlayerUpdate(){
    player_image->setPosition(_Player.point);
    player_image->setTextureRect(Rect(_Player.tx_point.x, _Player.tx_point.y,
                                      _Player.tx_size.width, _Player.tx_size.height));
}

void Stage04::update(float delta){
    TouchingTimeCount();
    DistTouchBeganToEnded();

    PlayerScene();
    PlayerUpdate();

    HutonScene();
    HutonTrigger();
    HutonUpdate();
}