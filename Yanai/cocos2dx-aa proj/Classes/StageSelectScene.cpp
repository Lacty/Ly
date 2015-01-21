
#include "StageSelectScene.h"
#include "TitleScene.h"
#include "StageClasses/Stage01.h"
#include "StageClasses/Stage02.h"
#include "StageClasses/Stage03.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* StageSelect::createScene()
{
    auto scene = Scene::create();
    auto layer = StageSelect::create();
    scene->addChild(layer);
    return scene;
}


// コンストラクタ
StageSelect::StageSelect(){
    STAGE_NUMBER = 1;
    cut_texture  = 0;

    // 画面のサイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を変更
    auto _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);
    sgin = -1;

    // _Stage構造体をとりあえず初期化
    for (int i = 0; i < 5; i++){
        _Stage[i] = { true,
            Point(0, 0), Size(0, 0),
            Point(0, 0), Size(100, 100),
            2,
            Color3B::WHITE, 255,
            true,
            0, 0, 0, 0
        };
    }

    // _Numberをとりあえず初期化
    _Number = { true,
        Point(0, 0), Size(0, 0),
        Point(0, 0), Size(100, 100),
        4,
        Color3B::WHITE,
        true,
        0, 0, 0, 0
    };

    // _Arrowをとりあえず初期化
    for (int i = 0; i < 2; i++){
        _Arrow[i] = { true,
            Point(0, 0), Size(0, 0),
            Point(0, 0), Size(200, 200),
            3,
            Color3B::BLACK,
            true,
            0, 0, 0, 0
        };
    }

}

bool StageSelect::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }

    // タッチ操作を有効にする
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = CC_CALLBACK_2(StageSelect::onTouchBegan, this);

    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);

    // Updateを呼ぶ
    this->scheduleUpdate();


    /*  "STAGE"の描画
        描画する画像のサイズを取得
        "STAGE"の表示位置＆
        切り取り位置をそれぞれ指定
    */
    for (int i = 0; i < 5; i++){
        _Stage[i].size = Size(_Stage[i].tx_size.width * _Stage[i].scale,
                              _Stage[i].tx_size.height * _Stage[i].scale);
    }

    for (int i = 0; i < 5; i++){
        _Stage[i].point = Point(_Stage[i].size.width / 2 + (_Stage[i].size.width / 2 * i),
                                (winSize.height / 2 - _Stage[i].size.height / 2) + (_Stage[i].size.height / 2 * i));
    }
    /*
        画像の切り取り位置を指定
        画像の回転角度を指定
    */
    _Stage[0].tx_point = Point(0, 0);
    _Stage[0].angle    = -40;

    _Stage[1].tx_point = Point(100, 0);
    _Stage[1].angle    = -40;

    _Stage[2].tx_point = Point(200, 0);
    _Stage[2].angle    = -40;

    _Stage[3].tx_point = Point(0, 200);
    _Stage[3].angle    = -40;

    _Stage[4].tx_point = Point(100, 200);
    _Stage[4].angle    = -40;
    
    // 描画
    for (int i = 0; i < 5; i++){
        Sprite* stage_image = Sprite::create("system_image.png");
        stage_image->setPosition(_Stage[i].point);
        stage_image->setTextureRect(Rect(_Stage[i].tx_point.x, _Stage[i].tx_point.y,
                                         _Stage[i].tx_size.width, _Stage[i].tx_size.height));
        stage_image->setScale(_Stage[i].scale);
        stage_image->setAnchorPoint(Point(0, 0));
        stage_image->setRotation(_Stage[i].angle);
        this->addChild(stage_image);
    }


    /*  "数字"の描画
        描画する画像のサイズを取得
        _Numberのステータスを変更
    */
    _Number.size = Size(_Number.tx_size.width*_Number.scale,
                        _Number.tx_size.height*_Number.scale);
    _Number.point = Point(winSize.width/2 - _Number.size.width/2,
                          winSize.height/2 - _Number.size.height/2);

    // 描画
    num_image = Sprite::create("system_image.png");
    num_image->setPosition(_Number.point);
    num_image->setScale(_Number.scale);
    num_image->setAnchorPoint(Point(0, 0));
    this->addChild(num_image);


    /*  ステージ選択用矢印の描画
        描画する画像のサイズを取得
        _Arrowのステータスを変更
    */
    for (int i = 0; i < 2; i++){
        _Arrow[i].size = Size(_Arrow[i].tx_size.width * _Arrow[i].scale,
                              _Arrow[i].tx_size.height * _Arrow[i].scale);
    }
    _Arrow[0].point = Point(winSize.width - _Arrow[0].size.width,
                            winSize.height - _Arrow[0].size.height+50);
    _Arrow[1].point = Point(0, -50);
    _Arrow[0].tx_point = Point(200, 300);
    _Arrow[1].tx_point = Point(0, 300);
    // 画像が変に見えたから、少しだけ傾けておく
    _Arrow[1].angle = 3;

    /* 上の矢印の描画 */
    upside_arrow_image = Sprite::create("system_image.png");
    upside_arrow_image->setPosition(_Arrow[0].point);
    upside_arrow_image->setTextureRect(Rect(_Arrow[0].tx_point.x, _Arrow[0].tx_point.y,
                                            _Arrow[0].tx_size.width, _Arrow[0].tx_size.height));
    upside_arrow_image->setScale(_Arrow[0].scale);
    upside_arrow_image->setRotation(_Arrow[0].angle);
    upside_arrow_image->setAnchorPoint(Point(0, 0));
    this->addChild(upside_arrow_image);
    
    /* 下の矢印の描画 */
    downside_arrow_image = Sprite::create("system_image.png");
    downside_arrow_image->setPosition(_Arrow[1].point);
    downside_arrow_image->setTextureRect(Rect(_Arrow[1].tx_point.x, _Arrow[1].tx_point.y,
                                              _Arrow[1].tx_size.width, _Arrow[1].tx_size.height));
    downside_arrow_image->setScale(_Arrow[1].scale);
    downside_arrow_image->setRotation(_Arrow[1].angle);
    downside_arrow_image->setAnchorPoint(Point(0, 0));
    this->addChild(downside_arrow_image);

    return true;
}


// タッチした時の処理
bool StageSelect::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    touchPoint = Vec2(touch->getLocationInView().x, sgin*(touch->getLocationInView().y - winSize.height));
    log("touchPoint.x=%f, touchPoint.y=%f", touchPoint.x, touchPoint.y);

    // 矢印をタッチしたら選択ステージが切り替わるようにする
    if (STAGE_NUMBER < 10){
        if (point_to_rect(touchPoint.x, touchPoint.y,
                          _Arrow[0].point.x, _Arrow[0].point.y, _Arrow[0].size.width, _Arrow[0].size.height)){
            cut_texture += 1;
        }
    }
    if (STAGE_NUMBER > 1){
        if (point_to_rect(touchPoint.x, touchPoint.y,
                          _Arrow[1].point.x, _Arrow[1].point.y, _Arrow[1].size.width, _Arrow[1].size.height)){
            cut_texture -= 1;
        }
    }

    //--------------シーン移行--------------//
    if (point_to_rect(touchPoint.x, touchPoint.y,
                      _Number.point.x, _Number.point.y, _Number.size.width, _Number.size.height)){
        switch (STAGE_NUMBER){
        case 1:{
            Director::getInstance()->replaceScene(Stage01::createScene());
        }break;

        case 2:{
            Director::getInstance()->replaceScene(Stage02::createScene());
        }break;

        case 3:{
            Director::getInstance()->replaceScene(Stage03::createScene());
        }break;
        }
    }

    //Director::getInstance()->replaceScene(Title::createScene());
    return true;
}

void StageSelect::update(float delta){
    // STAGE_NUMBERに描画した数字と同じ数値を代入させる
    STAGE_NUMBER = cut_texture + 1;

    // 選択されたステージの数値を描画させるために
    // 画像の切り取り位置を変更
    _Number.tx_point = Point(cut_texture * 100, 100);
    num_image->setTextureRect(Rect(_Number.tx_point.x, _Number.tx_point.y,
                                   _Number.tx_size.width, _Number.tx_size.height));
    
    // 矢印の色を変更
    upside_arrow_image->setColor(_Arrow[0].col);
    downside_arrow_image->setColor(_Arrow[1].col);
}
