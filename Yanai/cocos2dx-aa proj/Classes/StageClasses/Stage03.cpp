
#include "StageSelectScene.h"
#include "Stage03.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Stage03::createScene()
{
    auto scene = Scene::create();
    auto layer = Stage03::create();
    scene->addChild(layer);
    return scene;
}


// �R���X�g���N�^
Stage03::Stage03(){
    // ��ʃT�C�Y���擾
    winSize = Director::getInstance()->getVisibleSize();

    // �w�i�F���w��
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    // owata�̃N���G�C�g
    owata = PlayerOwata::create();
}


bool Stage03::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }

    // �}���`�^�b�`�����L���ɂ���
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(Stage03::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Stage03::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Stage03::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // Update���Ă�
    this->scheduleUpdate();

    // owata(Player)�̎���
    this->addChild(owata);

    return true;
}

// �^�b�v�������̏���
void Stage03::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);


        iterator++;
    }
    return;
}

// �^�b�v���i�����ē��������Ƃ��j�̏���
void Stage03::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

// �w�𗣂����Ƃ��̏���
void Stage03::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

void Stage03::PlayerUpdate(){
    owata->owata_image->setPosition(owata->_Owata.point);
}

void Stage03::update(float delta){

    PlayerUpdate();
}