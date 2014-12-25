
#include "TestScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* TestLayer::createScene(){
    //メソッドの中身を記載
    
    auto scene = Scene::create();
    auto layer = TestLayer::create();
    scene->addChild(layer);

    return scene;

}


bool TestLayer::init(){

    if (!Layer::init()){

        return false;
    }

    //init()メソッドの中身を記載
    
    //画面の中央に点を表示
    //画面のサイズを取得
    Size screenSize = Director::getInstance()->getVisibleSize();

    DrawNode* drawNode = DrawNode::create();
    drawNode->setPosition(Point(0.0f, 0.0f));
    this->addChild(drawNode);

    //描画
    float r = 5;
    float x = screenSize.width / 2;
    float y = screenSize.height / 2;
    drawNode->drawDot(Point(x, y), r, Color4F::WHITE);

    //Director::getInstance()->replaceScene(HelloWorld::createScene());

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Director::getInstance()->replaceScene(HelloWorld::createScene());
        return true;
    };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

