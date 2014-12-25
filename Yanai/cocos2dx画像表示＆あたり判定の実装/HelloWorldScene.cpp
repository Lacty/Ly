#include "HelloWorldScene.h"
#include "TestScene.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


//コンストラクタ
HelloWorld::HelloWorld(){
    imageVisible = true;

    image1.x = 50;
    image1.y = 100;
    image2.x = 200;
    image2.y = 100;

    tex_x = 320.0f;
    tex_y = 240.0f;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    //Update関数を呼ぶ
    this->scheduleUpdate();


    // 画面サイズを取得
    Size screenSize = Director::getInstance()->getVisibleSize();

    // 背景色を設定
    auto _bg = LayerColor::create(Color4B::GRAY);
    // レイヤーに追加
    this->addChild(_bg);
    
    /*
    // 描画用ノードを作成
    DrawNode* drawNode = DrawNode::create();
    drawNode->setPosition(Point(0.0f, 0.0f));
    this->addChild(drawNode);

    // 描画
    float r = 10.0f;
    float x = screenSize.width/2-screenSize.width/5;
    float y = screenSize.height/2;
    drawNode->drawDot(Point(x,y), r, Color4F::WHITE);

    // 三角形
    Point p0(screenSize.width / 2, screenSize.height / 2 + 50);
    Point p1(screenSize.width / 2 - 50, screenSize.height / 2 - 50);
    Point p2(screenSize.width / 2 + 50, screenSize.height / 2 - 50);
    drawNode->drawTriangle(p0, p1, p2, Color4F::GREEN);

    Point p3(0, screenSize.height);
    Point p4(0, 0);
    Point p5(screenSize.width, 0);
    Point p6(screenSize.width, screenSize.height);
    drawNode->drawDot(p3, r, Color4F::WHITE);
    drawNode->drawDot(p4, r, Color4F::WHITE);
    drawNode->drawDot(p5, r, Color4F::WHITE);
    drawNode->drawDot(p6, r, Color4F::WHITE);
    */

    /*シーンの切り替え
    //TestLayer test;
    //Scene *pScene = TestLayer::createScene();
    //TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    //Director::getInstance()->replaceScene(transition);
    //Director::getInstance()->replaceScene(TestLayer::createScene());
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Director::getInstance()->replaceScene(TestLayer::createScene());
        return true;
    };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    */

    //labelは宣言してるのでautoを外す
    label = LabelTTF::create("Marry Christmas", "Arial", 40);
    label->setPosition(Point(tex_x, tex_y));
    this->addChild(label);

    //画像を表示
    button_image1 = Sprite::create("CloseNormal.png");
    //アンカーポイントを左下に固定
    button_image1->setAnchorPoint(Point(0, 0));
    button_image1->setPosition(Point(image1));
    this->addChild(button_image1);
    //画像サイズを取得
    image_1 = button_image1->getContentSize();

    button_image2 = Sprite::create("CloseSelected.png");
    button_image2->setAnchorPoint(Point(0, 0));
    button_image2->setPosition(Point(image2));
    this->addChild(button_image2);
    //画像のサイズを取得
    image_2 = button_image2->getContentSize();

    CCLOG("",image_1);

    return true;
}

void HelloWorld::update(float delta){
    label->setPosition(Point(tex_x, tex_y));
    tex_x++;

    button_image1->setPosition(Point(image1));
    image1.x++;
    button_image1->setVisible(imageVisible);
    
    if (rect_to_rect(image1.x, image1.y, image_1.width, image_1.height,
        image2.x, image2.y, image_2.width, image_2.height)){
        imageVisible = false;
    }
    else{
        imageVisible = true;
    }
}