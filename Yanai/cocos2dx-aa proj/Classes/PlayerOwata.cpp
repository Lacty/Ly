
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
        Point(0, winSize.height/4), Size(0, 0),
        Point(0, 0), Size(200, 100),
        1,
        Color3B::WHITE, 1,
        true,
        0, 0, 0, 3
    };

    // _Shots���Ƃ肠����������
    for (int i = 0; i < SHOT_MAX; i++){
        _Shots[i] = { false,
            Point(0, 0), Size(0, 0),
            Point(0, 100), Size(100, 100),
            1,
            Color3B::WHITE, 255,
            true,
            0, 0, 0, 20
        };
    }

    // _ShotButton���Ƃ肠����������
    _ShotButton = { false,
        Point(0, 0), Size(0, 0),
        Point(700, 300), Size(200, 100),
        1.8,
        Color3B::WHITE,
        true,
        0, 0, 0, 0
    };

    // _Button���Ƃ肠����������
    for (int i = 0; i < BUTTON_MAX; i++){
        _Button[i] = { true,
            Point(0, 0), Size(0, 0),
            Point(500 - (i*200), 200), Size(200, 100),
            1.8,
            Color3B::WHITE, 255,
            true,
            0, 0, 0, 0
        };
    }

    // _Dead�̏�����
    _Dead = { false,
        Point(0, 0), Size(0, 0),
        Point(0, 200), Size(200, 200),
        1.5,
        Color3B::WHITE, 0,
        true,
        0, 0, 0, 0
    };

    isPushLeft  = false;
    isPushRight = false;
    isTouchShotButton = false;
    pause = false;
}


/*
    Singleton
    ���̃N���X�𑼂Ő������Ȃ��悤�ɂ��鏈��
*/
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


    //--------�I���^�̕`��--------//
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


    //----------�e�̕`��----------//
    for (int i = 0; i < SHOT_MAX; i++){
        gun_image[i] = Sprite::create("player_image.png");
        gun_image[i]->setPosition(_Shots[i].point);
        gun_image[i]->setTextureRect(Rect(_Shots[i].tx_point.x, _Shots[i].tx_point.y,
                                          _Shots[i].tx_size.width, _Shots[i].tx_size.height));
        gun_image[i]->setAnchorPoint(Point(0, 0));
        gun_image[i]->setScale(_Shots[i].scale);
        this->addChild(gun_image[i]);
    }

    // ���ۂɕ`�悵�Ă���摜�T�C�Y���擾
    for (int i = 0; i < SHOT_MAX; i++){
        _Shots[i].size = Size(_Shots[i].tx_size.width * _Shots[i].scale,
                              _Shots[i].tx_size.height * _Shots[i].scale);
    }

    //----------ShotButton�̕`��----------//
    // ���ۂɕ`�悵�Ă���摜�̃T�C�Y���擾
    _ShotButton.size = Size(_ShotButton.tx_size.width * _ShotButton.scale,
                            _ShotButton.tx_size.height * _ShotButton.scale);

    // �`��ʒu�̕ύX
    _ShotButton.point = Point(winSize.width - (_ShotButton.size.width/20 * 21), _ShotButton.size.height/15);

    shot_button_image = Sprite::create("system_image.png");
    shot_button_image->setPosition(_ShotButton.point);
    shot_button_image->setTextureRect(Rect(_ShotButton.tx_point.x, _ShotButton.tx_point.y,
                                           _ShotButton.tx_size.width, _ShotButton.tx_size.height));
    shot_button_image->setAnchorPoint(Point(0, 0));
    shot_button_image->setScale(_ShotButton.scale);
    this->addChild(shot_button_image);


    //---------�����L�[�̕`��----------//
    // ���ۂɕ`�悵�Ă���摜�T�C�Y���擾
    for (int i = 0; i < BUTTON_MAX; i++){
        _Button[i].size = Size(_Button[i].tx_size.width * _Button[i].scale,
            _Button[i].tx_size.height * _Button[i].scale);
    }

    // �`��ʒu��ύX
    for (int i = 0; i < BUTTON_MAX; i++){
        _Button[i].point = Point(_Button[i].size.width - i*_Button[i].size.width, _Button[i].size.height/15);
    }

    for (int i = 0; i < BUTTON_MAX; i++){
        button_image[i] = Sprite::create("system_image.png");
        button_image[i]->setPosition(_Button[i].point);
        button_image[i]->setTextureRect(Rect(_Button[i].tx_point.x, _Button[i].tx_point.y,
                                             _Button[i].tx_size.width, _Button[i].tx_size.height));
        button_image[i]->setAnchorPoint(Point(0, 0));
        button_image[i]->setScale(_Button[i].scale);
        this->addChild(button_image[i]);
    }

    //--------Dead--------//
    dead_image = Sprite::create("player_image.png");
    dead_image->setPosition(_Dead.point);
    dead_image->setTextureRect(Rect(_Dead.tx_point.x, _Dead.tx_point.y, _Dead.tx_size.width, _Dead.tx_size.height));
    dead_image->setScale(_Dead.scale);
    dead_image->setVisible(_Dead.visi);
    this->addChild(dead_image);

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
        if (point_to_rect(location.x, location.y, 0, 0, _Button[LEFT].size.width, winSize.height)){
            isPushRight  = false;
            isPushLeft   = true;
            _Owata.right = false;
        }
        if (point_to_rect(location.x, location.y, _Button[LEFT].size.width, 0, _Button[RIGHT].size.width, winSize.height)){
            isPushRight  = true;
            isPushLeft   = false;
            _Owata.right = true;
        }


        /* 
            ShotButton���^�b�v�����Ƃ��̏���
            �c�����ɂ����蔻���L�΂��Ă���
        */
        if (point_to_rect(location.x, location.y, winSize.width - _ShotButton.size.width, 0, _ShotButton.size.width, _ShotButton.size.height*2)){
            // ShotButton���^�b�`�����Ɣ���
            isTouchShotButton = true;
            _ShotButton.active = true;
        }
        
        iterator++;
    }
    return;
}


// �^�b�v���i�����ē������Ă���ԁj�̏���
void PlayerOwata::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        
        if (point_to_rect(location.x, location.y, 0, 0, _Button[LEFT].size.width, winSize.height)){
            isPushRight  = false;
            isPushLeft   = true;
            _Owata.right = false;
        }
        if (point_to_rect(location.x, location.y, _Button[LEFT].size.width, 0, _Button[RIGHT].size.width, winSize.height)){
            isPushRight  = true;
            isPushLeft   = false;
            _Owata.right = true;
        }
        if (point_to_rect(location.x, location.y, _Button[LEFT].size.width+_Button[RIGHT].size.width, 0,
            winSize.width - _Button[LEFT].size.width + _Button[RIGHT].size.width + _ShotButton.size.width, winSize.height)){
            isPushRight  = false;
            isPushLeft   = false;
        }

        /*
            ShotButton���^�b�v�����Ƃ��̏���
        */
        if (point_to_rect(location.x, location.y, winSize.width - _ShotButton.size.width, 0, _ShotButton.size.width, _ShotButton.size.height*2)){
            // �^�b�v�������Ă���Ԃ͒e�����˂���Ȃ��悤��false�ɂ��Ă���
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

        
        if (point_to_rect(location.x, location.y, 0, 0, _Button[LEFT].size.width + _Button[RIGHT].size.width, winSize.height)){
            isPushRight = false;
            isPushLeft  = false;
        }

        // Shot
        if (point_to_rect(location.x, location.y, winSize.width - _ShotButton.size.width, 0, _ShotButton.size.width, _ShotButton.size.height*2)){
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
    // �e�X�e�[�W�̍X�V�����̍Ō�ɒu�����Ƃ�
    // �ςȕ`����Ȃ���
    // ��F�u���b�N�ɂ̂߂荞�݂Ȃ�
    // owata_image->setPosition(_Owata.point);
}

// �I���^�̉摜�؂�ւ�
void PlayerOwata::owataSetTextureRect(){

    if (_Owata.right){
        _Owata.tx_point = Point(0, 0);
    }
    else{
        _Owata.tx_point = Point(600, 0);
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
            _Shots[i].point = Point(0, 0);
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


void PlayerOwata::owataDead(){
    if (!_Owata.active){
        // �I���^�����񂾂瑀��s�\�ɂ���
        pause = true;
        _Dead.visi = 255;
        _Dead.active = true;
    }
    
    if (_Dead.active){
        _Dead.angle++;
        if ((_Dead.angle >= 0) && (_Dead.angle <= 30)){
            deadTexture_x = 0;
        } else if ((_Dead.angle >= 31) && (_Dead.angle <= 60)){
            deadTexture_x = 200;
        } else if ((_Dead.angle >= 61) && (_Dead.angle <= 90)){
            deadTexture_x = 400;
        }
        dead_image->setTextureRect(Rect(deadTexture_x, _Dead.tx_point.y, _Dead.tx_size.width, _Dead.tx_size.height));
    }

    dead_image->setPosition(Point(_Owata.point.x + _Owata.size.width / 2, _Owata.point.y));
    dead_image->setVisible(_Dead.visi); //���ߓx
}

void PlayerOwata::visiblePlayer(){
    if (!_Owata.active){
        _Owata.visi = 0;
    }
    owata_image->setVisible(_Owata.visi); //���ߓx
}


// �����L�[���������Ƃ��{�^���̐F��ύX�����鏈��
// PS.ShotButton�̐F�ύX���ǉ�
void PlayerOwata::setButtonColor(){

    if (isPushLeft){
        _Button[LEFT].col = Color3B::BLACK;
    } else{
        _Button[LEFT].col = Color3B::WHITE;
    }

    if (isPushRight){
        _Button[RIGHT].col = Color3B::BLACK;
    } else{
        _Button[RIGHT].col = Color3B::WHITE;
    }

    //---------ShotButton--------//
    if (_ShotButton.active){
        _ShotButton.angle++;
        if (_ShotButton.angle < 10){
            _ShotButton.col = Color3B::BLACK;
        } else{
            _ShotButton.angle = 0;
            _ShotButton.active = false;
        }
    } else{
        _ShotButton.col = Color3B::WHITE;
    }

    // pause��ʒ��̐F������
    if (pause){
        for (int i = 0; i < 2; i++){
            _Button[i].col = Color3B::WHITE;
        }
        _ShotButton.col = Color3B::WHITE;
    }

    // �ύX�����F�𔽉f������
    for (int i = 0; i < BUTTON_MAX; i++){
        button_image[i]->setColor(_Button[i].col);
    }
    shot_button_image->setColor(_ShotButton.col);
}


void PlayerOwata::update(float delta){
    
    if (!pause){
        // �֐��Ăяo��
        owataMove();
        owataSetTextureRect();
        owataShot();
    }
    visiblePlayer();
    setButtonColor();
    owataDead();
}