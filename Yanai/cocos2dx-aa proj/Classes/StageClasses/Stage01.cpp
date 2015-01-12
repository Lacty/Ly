
#include "Stage01.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Stage01::createScene()
{
    auto scene = Scene::create();
    auto layer = Stage01::create();
    //auto layer2 = PlayerOwata::create();
    //*owata = *layer2;
    scene->addChild(layer);
    //scene->addChild(layer2);
    return scene;
}


// �R���X�g���N�^
Stage01::Stage01(){
    // ��ʃT�C�Y���擾
    winSize = Director::getInstance()->getVisibleSize();

    // �w�i�F���w��
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);


    // �Ȃ�ƂȂ��N���G�C�g���Ă݂�
    owata = PlayerOwata::create();
    //owata.create();
    owa = false;
}


bool Stage01::init(){

    if ( !Layer::init() )
    {
        return false;
    }
    
    // �}���`�^�b�`�����L���ɂ���
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(Stage01::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Stage01::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Stage01::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    

    // Update���Ă�
    this->scheduleUpdate();


    // create�͂�������add����΂����񂶂�ˁH
    // ���Ă��Ƃł���Ă݂�
    this->addChild(owata);
    // ���ʁF�ł��������
    // owata��update�Ă�łȂ����ǂ����̂���
    // ����pause��ʂ��쐬�ł��邩�ǂ���

    /*
    Rect rect1 = Rect(0, 0, 60, 60);

    auto sprite1 = Sprite::create();
    sprite1->setTextureRect(rect1);
    sprite1->setColor(Color3B::WHITE);
    sprite1->setPosition(winSize.width/2, winSize.height/2);
    this->addChild(sprite1);

    auto sprite2 = getTag();
    */

    /*
    // ����2�s��PlayerOwata�N���X���ĂԂ��Ƃ��ł���炵��
    auto playerLayer = PlayerOwata::create();
    addChild(playerLayer);
    */


    return true;
}

// �^�b�v�������̏���
void Stage01::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);

        iterator++;
    }
    return;
}

// �^�b�v���i�����ē��������Ƃ��j�̏���
void Stage01::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

// �w�𗣂����Ƃ��̏���
void Stage01::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        owa = false;
        iterator++;
    }
    return;
}


void Stage01::update(float delta){
    log("shot.x = %f", owata->_Shots[0].point.x);
}