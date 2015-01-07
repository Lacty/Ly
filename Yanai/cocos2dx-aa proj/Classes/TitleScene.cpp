
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Title::createScene()
{
    auto scene = Scene::create();
    auto layer = Title::create();
    scene->addChild(layer);
    return scene;
}


// コンストラクタ
Title::Title(){
    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を指定
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    sgin = -1;

    START = { true, Point(winSize.width / 30, winSize.height / 10 * 3),
              Size(0, 0), Point(0, 0), Size(500, 325),
              2.2,
              Color3B::WHITE,
              255, true, 0, 0, 0 };
    EXIT = { true, Point(winSize.width / 10 * 7, winSize.height / 20),
             Size(0, 0), Point(0, 325), Size(225, 185),
             2.2,
             Color3B::WHITE,
             255, true, 0, 0, 0 };
    OWATA = { true, Point(winSize.width / 2, winSize.height / 10),
              Size(0, 0), Point(600, 100), Size(200, 100),
              2,
              Color3B::WHITE,
              255, true, 0, 0, 0 };
}

bool Title::init(){

    if ( !Layer::init() )
    {
        return false;
    }

    // タッチ操作を有効にする
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = CC_CALLBACK_2(Title::onTouchBegan, this);

    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);

    // Update関数を呼ぶ
    this->scheduleUpdate();

    // 文字の表示
    auto label = LabelTTF::create("ver 1.0", "Arial", 40);
    label->setPosition(80, 40);
    this->addChild(label);

    // あたり判定用四角形を描画
    auto spr = Sprite::create();
    spr->setTextureRect(Rect(0, 0, 100, 100));
    spr->setColor(Color3B::WHITE);
    spr->setPosition(Point(100, 200));
    //this->addChild(spr);


    /* 
        画像の描画
    */
    // 「オワタ」
    start_image = Sprite::create("title_image.png");
    start_image->setPosition(START.point);
    start_image->setTextureRect(Rect(START.tx_point.x, START.tx_point.y,
                                     START.tx_size.width, START.tx_size.height));
    start_image->setScale(START.scale);
    start_image->setAnchorPoint(Point(0, 0));
    this->addChild(start_image);

    // 雲のようなもわもわ１
    cloud1 = Sprite::create("title_image.png");
    cloud1->setPosition(Point(winSize.width/20*7, winSize.height/4));
    cloud1->setTextureRect(Rect(300, 400, 100, 100));
    cloud1->setScale(2);
    this->addChild(cloud1);

    //「樹海」
    exit_image = Sprite::create("title_image.png");
    exit_image->setPosition(EXIT.point);
    exit_image->setTextureRect(Rect(EXIT.tx_point.x, EXIT.tx_point.y,
                                    EXIT.tx_size.width, EXIT.tx_size.height));
    exit_image->setScale(EXIT.scale);
    exit_image->setAnchorPoint(Point(0, 0));
    this->addChild(exit_image);

    // 雲のようなもわもわ２
    cloud2 = Sprite::create("title_image.png");
    cloud2->setPosition(Point(winSize.width/10*7-30, winSize.height/8));
    cloud2->setTextureRect(Rect(300, 350, 100, 50));
    cloud2->setScale(2);
    this->addChild(cloud2);

    // 「オワタ」本体
    owata_image = Sprite::create("player_image.png");
    owata_image->setPosition(OWATA.point);
    owata_image->setTextureRect(Rect(OWATA.tx_point.x, OWATA.tx_point.y,
                                     OWATA.tx_size.width, OWATA.tx_size.height));
    owata_image->setScale(OWATA.scale);
    this->addChild(owata_image);


    /*
        画像の(描画)サイズを取得
        画像の元サイズにスケールを掛けている
    */
    START.size.width  = START.tx_size.width  * START.scale;
    START.size.height = START.tx_size.height * START.scale;
    EXIT.size.width   = EXIT.tx_size.width   * EXIT.scale;
    EXIT.size.height  = EXIT.tx_size.height  * EXIT.scale;
    OWATA.size.width  = OWATA.tx_size.width  * OWATA.scale;
    OWATA.size.height = OWATA.tx_size.height * OWATA.scale;

    return true;
}


// タッチした時の処理
bool Title::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    touchPoint = Vec2(touch->getLocationInView().x, sgin*(touch->getLocationInView().y - winSize.height));
    log("touchPoint.x=%f, touchPoint.y=%f", touchPoint.x, touchPoint.y);

    // タッチしたときSTARTの中であれば
    // ステージ選択へ移行
    if (point_to_rect(touchPoint.x, touchPoint.y, START.point.x, START.point.y,
                      START.size.width, START.size.height)){
        Director::getInstance()->replaceScene(StageSelect::createScene());
    }

    return true;
}

void Title::update(float delta){
    START.angle += 0.08;
    EXIT.angle  += 0.1;
    start_image->setPosition(Point(START.point.x, sin(START.angle)*5+START.point.y));
    exit_image->setPosition(Point(EXIT.point.x, sin(EXIT.angle)*4+EXIT.point.y));
}
