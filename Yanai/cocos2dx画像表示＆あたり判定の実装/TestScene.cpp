
#include "TestScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* TestLayer::createScene(){
    //���\�b�h�̒��g���L��
    
    auto scene = Scene::create();
    auto layer = TestLayer::create();
    scene->addChild(layer);

    return scene;

}


bool TestLayer::init(){

    if (!Layer::init()){

        return false;
    }

    //init()���\�b�h�̒��g���L��
    
    //��ʂ̒����ɓ_��\��
    //��ʂ̃T�C�Y���擾
    Size screenSize = Director::getInstance()->getVisibleSize();

    DrawNode* drawNode = DrawNode::create();
    drawNode->setPosition(Point(0.0f, 0.0f));
    this->addChild(drawNode);

    //�`��
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

