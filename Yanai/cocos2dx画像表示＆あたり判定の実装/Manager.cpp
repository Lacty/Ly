#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "TestScene.h"
#include "Manager.h"

USING_NS_CC;

Scene* Manager::createScene(){
    auto scene = Scene::create();
    auto layer = Manager::create();
    scene->addChild(layer);

    return scene;
}

bool Manager::init(){
    if (!Layer::init()){
        return false;
    }
    /*
    //��ʂ̒����ɓ_��\��
    //��ʂ̃T�C�Y���擾
    Size screenSize = Director::getInstance()->getVisibleSize();

    DrawNode* drawNode = DrawNode::create();
    drawNode->setPosition(Point(0.0f, 0.0f));
    this->addChild(drawNode);

    //�`��
    float r = 20;
    float x = screenSize.width / 2;
    float y = screenSize.height / 2;
    drawNode->drawDot(Point(x, y), r, Color4F::WHITE);
    */

    Director::getInstance()->replaceScene(HelloWorld::createScene());

    return true;
}