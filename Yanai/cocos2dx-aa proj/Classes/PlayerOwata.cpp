
#include "PlayerOwata.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* PlayerOwata::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayerOwata::create();
    scene->addChild(layer);
    return scene;
}


// �R���X�g���N�^
PlayerOwata::PlayerOwata(){

    // ��ʃT�C�Y���擾
    winSize = Director::getInstance()->getVisibleSize();

    // _Owata���Ƃ肠����������
    _Owata = { true,
        Point(winSize / 2), Size(0, 0),
        Point(0, 0), Size(200, 100),
        1,
        Color3B::WHITE, 255,
        true,
        0, 0, 0, 3 };

    // _Shots���Ƃ肠����������
    for (int i = 0; i < SHOT_MAX; i++){
        _Shots[i] = { false,
            Point(0, 0), Size(0, 0),
            Point(0, 100), Size(100, 100),
            1,
            Color3B::WHITE, 255,
            true,
            0, 0, 0, 16 };
    }

    isTouchShotButton = false;

}

PlayerOwata &PlayerOwata::getInstance(){
    // ����̂݃C���X�^���X�𐶐�
    static PlayerOwata singleton;
    return singleton;
}

bool PlayerOwata::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }

    // �}���`�^�b�`�����L���ɂ���
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true); // ����s�\�Ƃ肠����true
    listener->onTouchesBegan = CC_CALLBACK_2(PlayerOwata::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(PlayerOwata::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(PlayerOwata::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    // Update���Ă�
    this->scheduleUpdate();


    // �I���^�̕`��
    owata_image = Sprite::create("player_image.png");
    // �X�e�[�^�X�̏�����
    owata_image->setPosition(_Owata.point);
    owata_image->setTextureRect(Rect(_Owata.tx_point.x, _Owata.tx_point.y,
                                     _Owata.tx_size.width, _Owata.tx_size.height));
    owata_image->setScale(_Owata.scale);
    owata_image->setAnchorPoint(Point(0, 0));
    this->addChild(owata_image);

    // ���ۂɕ`�悳��Ă���摜�̃T�C�Y���擾
    _Owata.size = Size(_Owata.tx_size.width  * _Owata.scale,
                       _Owata.tx_size.height * _Owata.scale);


    // �e�̕`��
    for (int i = 0; i < SHOT_MAX; i++){
        gun_image[i] = Sprite::create("player_image.png");
        gun_image[i]->setPosition(_Shots[i].point);
        gun_image[i]->setTextureRect(Rect(_Shots[i].tx_point.x, _Shots[i].tx_point.y,
                                          _Shots[i].tx_size.width, _Shots[i].tx_size.height));
        gun_image[i]->setAnchorPoint(Point(0, 0));
        gun_image[i]->setScale(_Shots[i].scale);
        this->addChild(gun_image[i]);

        gun_image[i]->setTag(i);
    }

    // ���ۂɕ`�悵�Ă���e�̉摜�T�C�Y���擾
    for (int i = 0; i < SHOT_MAX; i++){
        _Shots[i].size = Size(_Shots[i].tx_size.width * _Shots[i].scale,
                              _Shots[i].tx_size.height * _Shots[i].scale);
    }

    return true;
}


// �^�b�v�������̏���
void PlayerOwata::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);
        
        /*
            �ړ��̏��������̂܂܏�����"�^�b�v������"�̊֐����Ȃ��̂�
            �������v���悤�ɂ����Ȃ�����
            _Owata.point.x += _Owata.speed;
        */
        if (point_to_rect(location.x, location.y, 0, 0, winSize.width / 4, winSize.height)){
            isPushRight  = false;
            isPushLeft   = true;
            _Owata.right = false;
        }
        if (point_to_rect(location.x, location.y, winSize.width / 4, 0, winSize.width / 4, winSize.height)){
            isPushRight  = true;
            isPushLeft   = false;
            _Owata.right = true;
        }


        /* 
            ��ʉE�[���^�b�v�����Ƃ��̏���
        */
        if (point_to_rect(location.x, location.y, winSize.width / 4 * 3, 0, winSize.width / 4, winSize.height)){
            // ShotButton���^�b�`�����Ɣ���
            isTouchShotButton = true;
        }
        
        iterator++;
    }
    return;
}


// �^�b�v���i�����ē��������Ƃ��j�̏���
void PlayerOwata::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        
        if (point_to_rect(location.x, location.y, 0, 0, winSize.width / 4, winSize.height)){
            isPushRight  = false;
            isPushLeft   = true;
            _Owata.right = false;
        }
        if (point_to_rect(location.x, location.y, winSize.width / 4, 0, winSize.width / 4, winSize.height)){
            isPushRight  = true;
            isPushLeft   = false;
            _Owata.right = true;
        }
        if (point_to_rect(location.x, location.y, winSize.width / 2, 0, winSize.width/4, winSize.height)){
            isPushRight  = false;
            isPushLeft   = false;
        }

        /*
        ��ʉE�[���^�b�v�����Ƃ��̏���
        */
        if (point_to_rect(location.x, location.y, winSize.width / 4 * 3, 0, winSize.width / 4, winSize.height)){
            // ShotButton����w�𗣂�����
            isTouchShotButton = false;
        }

        iterator++;
    }
    return;
}


// �w�𗣂����Ƃ��̏���
void PlayerOwata::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        
        if (point_to_rect(location.x, location.y, 0, 0, winSize.width / 2, winSize.height)){
            isPushRight = false;
            isPushLeft  = false;
        }

        /*
        ��ʉE�[���^�b�v�����Ƃ��̏���
        */
        if (point_to_rect(location.x, location.y, winSize.width / 4 * 3, 0, winSize.width / 4, winSize.height)){
            // ShotButton����w�𗣂�����
            isTouchShotButton = false;
        }

        iterator++;
    }
    return;
}


// �I���^�̈ړ�����
void PlayerOwata::owataMove(){
    // ��ʊO�ɏo�Ȃ��悤�Ɉړ�����
    if (_Owata.point.x < 0){
        isPushLeft = false;
    }
    if ((_Owata.point.x + _Owata.size.width) > winSize.width){
        isPushRight = false;
    }

    // ������Ă�������Ɉړ�������
    if (isPushRight){
        _Owata.point.x += _Owata.speed;
    }
    if (isPushLeft){
        _Owata.point.x -= _Owata.speed;
    }

    // �I���^�̈ʒu�𔽉f������
    owata_image->setPosition(_Owata.point);
}

// �I���^�̉摜�؂�ւ�
void PlayerOwata::owataSetTextureRect(){

    if (_Owata.right){
        _Owata.tx_point = Point(0, 0);
    }
    else{
        _Owata.tx_point = Point(200, 0);
    }

    // �؂�ւ����摜�̐؂�o���ʒu�𔽉f������
    owata_image->setTextureRect(Rect(_Owata.tx_point.x, _Owata.tx_point.y,
                                     _Owata.tx_size.width, _Owata.tx_size.height));
}


// �e�𔭎˂�����֐�
void PlayerOwata::owataShot(){
    // ShotButton���^�b�v���ꂽ��
    if (isTouchShotButton){
        for (int i = 0; i < SHOT_MAX; i++){
            // ��������ĂȂ��e��T��
            if (!_Shots[i].active){

                // �������ꂽ������e�����������
                _Shots[i].active = true;

                // ��������e�����E�ǂ���������Ă��邩�ۑ�
                if (_Owata.right){
                    _Shots[i].right = true;
                } else{
                    _Shots[i].right = false;
                }

                // ��������e�̈ʒu���L�����N�^�[�ɍ��킹��
                // �ˏo����e�̕����ɂ��킹�Ĉʒu��ύX
                if (_Shots[i].right){
                    _Shots[i].point = Point(_Owata.point.x, _Owata.point.y);
                } else{
                    _Shots[i].point = Point(_Owata.point.x, _Owata.point.y);
                }

                // ���̒e�𐶐����Ȃ��悤�Ƀu���C�N
                isTouchShotButton = false;
                break;
            }
        }
    }

    // �e�̈ړ�����
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].active){
            if (_Shots[i].right){
                _Shots[i].point.x += _Shots[i].speed;
            } else{
                _Shots[i].point.x -= _Shots[i].speed;
            }
        }
    }

    // ��ʊO�ɂł���e������
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].point.x < 0){
            _Shots[i].active = false;
        }
        // ��ʉ����T�C�Y - �e�̉摜����
        if (_Shots[i].point.x > winSize.width - _Shots[i].size.width){
            _Shots[i].active = false;
        }
    }

    // �e��"�\��""��\��"��e�̐����ɂ���ĕύX
    // "visi"��int�^�Ȃ̂�true,false�ł͂Ȃ������Ŕ��肳����
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].active){
            _Shots[i].visi = 1; /* true */
        } else{
            _Shots[i].visi = 0; /* false */
        }
    }

    // �e�̉摜�؂���ʒu��ύX
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].right){
            _Shots[i].tx_point = Point(400, 100);
        } else{
            _Shots[i].tx_point = Point(500, 100);
        }
    }

    // �ύX�����X�e�[�^�X�𔽉f������
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].active){
            gun_image[i]->setPosition(_Shots[i].point);
            gun_image[i]->setTextureRect(Rect(_Shots[i].tx_point.x, _Shots[i].tx_point.y,
                                              _Shots[i].tx_size.width, _Shots[i].tx_size.height));
        }
        gun_image[i]->setVisible(_Shots[i].visi);
    }

}

float* PlayerOwata::getShotPosX(int n){
    return &_Shots[n].point.x;
}

void PlayerOwata::update(float delta){
    
    // �֐��Ăяo��
    owataMove();
    owataSetTextureRect();
    owataShot();

}