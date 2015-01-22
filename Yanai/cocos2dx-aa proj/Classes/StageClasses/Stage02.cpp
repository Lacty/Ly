
#include "StageSelectScene.h"
#include "Stage02.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Stage02::createScene()
{
    auto scene = Scene::create();
    auto layer = Stage02::create();
    scene->addChild(layer);
    return scene;
}

// �R���X�g���N�^
Stage02::Stage02(){
    // ��ʃT�C�Y���擾
    winSize = Director::getInstance()->getVisibleSize();

    // �w�i�F���w��
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    // owata�̃N���G�C�g
    owata = PlayerOwata::create();

    // ���̎n�_�ƏI�_�����肷��
    for (int i = 0; i < 2; i++){
        startingPoint[i] = Point(0, winSize.height / 4 + winSize.height/8*3*i);
        endingPoint[i] = Point(winSize.width, winSize.height / 4 + winSize.height / 8 * 3 * i);
    }
    // ���̐��̑���������
    weight = 5;

    // _Block���Ƃ肠����������
    for (int i = 0; i < BLOCK_MAX; i++){
        _Block[i] = { true,
            Point(0, 0), Size(0, 0),
            Point(400, 0), Size(100, 100),
            1,
            Color3B::ORANGE, 255,
            true,
            0, 0, 0, 0
        };
    }

    // _Goal���Ƃ肠����������
    _Goal = { false,
        Point(0, 0), Size(0, 0),
        Point(0, 0), Size(300, 200),
        1,
        Color3B::WHITE, 255,
        true,
        0, 0, 0, 3
    };

    // _Pause���Ƃ肠����������
    _Pause = { false,
        Point(0, 0), Size(0, 0),
        Point(200, 500), Size(200, 200),
        1,
        Color3B::WHITE, 0,
        true,
        0, 0, 0, 0
    };

    // _WarpBlock���Ƃ肠����������
    for (int i = 0; i < WARP_MAX; i++){
        _WarpBlock[i] = { false,
            Point(0, 0), Size(0, 0),
            Point(100, 200), Size(100, 100),
            1,
            Color3B(200, 100, 200), 255,
            true,
            0, 0, 0, 0
        };
    }

    // _MovingBlock���Ƃ肠����������
    for (int i = 0; i < MOVING_BLOCK_MAX; i++){
        _MovingBlock[i] = { true,
            Point(0, 0), Size(0, 0),
            Point(100, 0), Size(100, 100),
            1,
            Color3B::BLACK, 255,
            0, 0, 0, 0
        };
    }

    // target���Ƃ肠����������
    _Target = { true,
        Point(0, 0), Size(0, 0),
        Point(100, 400), Size(100, 200),
        1,
        Color3B::ORANGE, 255,
        true,
        0, 0, 0, 0
    };
}


bool Stage02::init(){

    if (!Layer::init())
    {
        return false;
    }

    // �}���`�^�b�`�����L���ɂ���
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(Stage02::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Stage02::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Stage02::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // Update���Ă�
    this->scheduleUpdate();

    // owata(Player)�̎���
    this->addChild(owata);

    //----------���̕`��---------//
    for (int i = 0; i < 2; i++){
        drawFloor[i] = DrawNode::create();
        drawFloor[i]->drawSegment(startingPoint[i], endingPoint[i], weight, Color4F::BLACK);
        this->addChild(drawFloor[i]);
    }

    //----------���Block---------//
    // �`��ʒu�̌���
    _Block[0].point = Point(winSize.width / 4, startingPoint[0].y + weight);     // ���̐��ɔ��Ȃ��悤��
    _Block[1].point = Point(winSize.width / 5 * 3, startingPoint[0].y + weight); // ���̑���(weight)����ɔz�u
    _Block[1].active = false;
    _Block[1].visi = 0;

    for (int i = 0; i < BLOCK_MAX; i++){
        _Block[i].size = Size(_Block[i].tx_size.width * _Block[i].scale,
            _Block[i].tx_size.height * _Block[i].scale);

        block_image[i] = Sprite::create("stage01_image.png");
        block_image[i]->setPosition(_Block[i].point);
        block_image[i]->setTextureRect(Rect(_Block[i].tx_point.x, _Block[i].tx_point.y,
            _Block[i].tx_size.width, _Block[i].tx_size.height));
        block_image[i]->setScale(_Block[i].scale);
        block_image[i]->setAnchorPoint(Point(0, 0));
        block_image[i]->setOpacity(_Block[i].visi);
        this->addChild(block_image[i]);
    }


    //-----------WarpBlock-----------//
    // ���ۂɕ`�悳��Ă���摜�̃T�C�Y���擾
    for (int i = 0; i < WARP_MAX; i++){
        _WarpBlock[i].size = Size(_WarpBlock[i].tx_size.width * _WarpBlock[i].scale,
                                  _WarpBlock[i].tx_size.height* _WarpBlock[i].scale);
    }
    // �`��ʒu�̌���
    _WarpBlock[A].point = Point(_Block[A].point.x + _Block[A].size.width*2, startingPoint[A].y + weight);
    _WarpBlock[B].point = Point(_WarpBlock[B].size.width * 2, startingPoint[1].y + weight);
    _WarpBlock[C].point = Point(winSize.width/5*4, startingPoint[1].y + weight);
    _WarpBlock[D].point = Point(winSize.width/7*4, startingPoint[0].y + weight);

    for (int i = 0; i < WARP_MAX; i++){
        warp_image[i] = Sprite::create("stage02_image.png");
        warp_image[i]->setPosition(_WarpBlock[i].point);
        warp_image[i]->setTextureRect(Rect(_WarpBlock[i].tx_point.x, _WarpBlock[i].tx_point.y,
                                           _WarpBlock[i].tx_size.width, _WarpBlock[i].tx_size.height));
        warp_image[i]->setScale(_WarpBlock[i].scale);
        warp_image[i]->setAnchorPoint(Point(0, 0));
        warp_image[i]->setColor(_WarpBlock[i].col);
        this->addChild(warp_image[i]);

        abcd_image[i] = Sprite::create("stage02_image.png");
        abcd_image[i]->setPosition(_WarpBlock[i].point);
        abcd_image[i]->setTextureRect(Rect(300+i*100, 200, 100, 100));
        abcd_image[i]->setAnchorPoint(Point(0, 0));
        abcd_image[i]->setColor(_WarpBlock[i].col);
        this->addChild(abcd_image[i]);
    }


    //-----------�㉺�u���b�N----------//
    // ���ۂɕ`�悳��Ă���摜�̃T�C�Y���擾
    for (int i = 0; i < MOVING_BLOCK_MAX; i++){
        _MovingBlock[i].size = Size(_MovingBlock[i].tx_size.width * _MovingBlock[i].scale,
                                    _MovingBlock[i].tx_size.height * _MovingBlock[i].scale);
    }
    // �ʒu�̌���
    _MovingBlock[0].point = Point(winSize.width/20*11, startingPoint[1].y + weight);
    _MovingBlock[1].point = Point(winSize.width/5*2, startingPoint[1].y + weight);

    for (int i = 0; i < MOVING_BLOCK_MAX; i++){
        moving_block_image[i] = Sprite::create("stage02_image.png");
        moving_block_image[i]->setPosition(_MovingBlock[i].point);
        moving_block_image[i]->setTextureRect(Rect(_MovingBlock[i].tx_point.x, _MovingBlock[i].tx_point.y,
                                                   _MovingBlock[i].tx_size.width, _MovingBlock[i].tx_size.height));
        moving_block_image[i]->setScale(_MovingBlock[i].scale);
        moving_block_image[i]->setAnchorPoint(Point(0, 0));
        moving_block_image[i]->setColor(_MovingBlock[i].col);
        this->addChild(moving_block_image[i]);
    }

    //----------Target-----------//
    // ���ۂɕ`�悳��Ă���摜�̃T�C�Y���擾
    _Target.size = Size(_Target.tx_size.width * _Target.scale,
                        _Target.tx_size.height * _Target.scale);
    // �`��ʒu������
    _Target.point = Point(_MovingBlock[0].point.x + _MovingBlock[0].size.width/5*7,
                          startingPoint[1].y + weight);
    target_image = Sprite::create("stage02_image.png");
    target_image->setPosition(_Target.point);
    target_image->setTextureRect(Rect(_Target.tx_point.x, _Target.tx_point.y,
                                      _Target.tx_size.width, _Target.tx_size.height));
    target_image->setScale(_Target.scale);
    target_image->setAnchorPoint(Point(0, 0));
    target_image->setColor(_Target.col);
    this->addChild(target_image);


    //---------���C�̕`��---------//
    _Goal.size = Size(_Goal.tx_size.width * _Goal.scale,
        _Goal.tx_size.height * _Goal.scale);
    _Goal.point = Point(winSize.width - _Goal.size.width - _Goal.size.width / 30,
        winSize.height / 4);

    goal_image = Sprite::create("stage01_image.png");
    goal_image->setPosition(_Goal.point);
    goal_image->setTextureRect(Rect(_Goal.tx_point.x, _Goal.tx_point.y,
        _Goal.tx_size.width, _Goal.tx_size.height));
    goal_image->setAnchorPoint(Point(0, 0));
    goal_image->setScale(_Goal.scale);
    this->addChild(goal_image);

    //------------���傗������-----------//
    // Goal��̉��o�Eowata�ɃR�����g������
    comment_image = Sprite::create("stage02_image.png");
    comment_image->setPosition(Point(0, 0));
    comment_image->setTextureRect(Rect(300, 0, 200, 100));
    comment_image->setOpacity(0);// ��\���ɂ��邽�߂ɓ��ߓx��0
    this->addChild(comment_image);

    //---------Pause--------//
    // pause��ʗp�w�i
    pause_bg = LayerColor::create(Color4B::BLACK, winSize.width, winSize.height);
    pause_bg->setOpacity(_Pause.visi);
    this->addChild(pause_bg);

    // ���ۂɕ`�悵�Ă���摜�̃T�C�Y���擾
    _Pause.size = Size(_Pause.tx_size.width * _Pause.scale,
        _Pause.tx_size.height * _Pause.scale);
    // �`��ʒu������
    _Pause.point = Point(winSize.width - _Pause.size.width - _Pause.size.width / 20,
        winSize.height - _Pause.size.height - _Pause.size.height / 20);

    pause_image = Sprite::create("system_image.png");
    pause_image->setPosition(_Pause.point);
    pause_image->setTextureRect(Rect(_Pause.tx_point.x, _Pause.tx_point.y,
        _Pause.tx_size.width, _Pause.tx_size.height));
    pause_image->setAnchorPoint(Point(0, 0));
    pause_image->setScale(_Pause.scale);
    this->addChild(pause_image);

    return true;
}

// �^�b�v�������̏���
void Stage02::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);

        // pause���
        if (!_Pause.active){
            if (point_to_rect(location.x, location.y, _Pause.point.x, _Pause.point.y, _Pause.size.width, _Pause.size.height)){
                _Pause.active = true;
            }
        }
        else{
            if (point_to_rect(location.x, location.y, _Pause.point.x, _Pause.point.y, _Pause.size.width, _Pause.size.height)){
                _Pause.active = false;
            }
        }

        iterator++;
    }
    return;
}

// �^�b�v���i�����ē��������Ƃ��j�̏���
void Stage02::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

// �w�𗣂����Ƃ��̏���
void Stage02::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

void Stage02::BlockTrigger(){
    // ���Block��Shot
    for (int i = 0; i < 2; i++){
        for (int s = 0; s < 2; s++){
            if (rect_to_rect(owata->_Shots[s].point.x, owata->_Shots[s].point.y, owata->_Shots[s].size.width, owata->_Shots[s].size.height,
                _Block[i].point.x, _Block[i].point.y, _Block[i].size.width, _Block[i].size.height)){
                _Block[i].active = false;
                owata->_Shots[s].active = false;
            }
        }
    }
    // �㉺�u���b�N��Shot
    for (int i = 0; i < 2; i++){
        for (int s = 0; s < 2; s++){
            if (rect_to_rect(owata->_Shots[s].point.x, owata->_Shots[s].point.y, owata->_Shots[s].size.width, owata->_Shots[s].size.height,
                _MovingBlock[i].point.x, _MovingBlock[i].point.y, _MovingBlock[i].size.width, _MovingBlock[i].size.height)){
                owata->_Shots[s].active = false;
            }
        }
    }
    // Target��Shot
    if (_Target.active){
        for (int s = 0; s < 2; s++){
            if (rect_to_rect(owata->_Shots[s].point.x, owata->_Shots[s].point.y, owata->_Shots[s].size.width, owata->_Shots[s].size.height,
                _Target.point.x, _Target.point.y, _Target.size.width, _Target.size.height)){
                owata->_Shots[s].active = false;
                _Target.active = false;
                _MovingBlock[0].active = false;
                _MovingBlock[1].active = false;
            }
        }
    }
}

void Stage02::BlockMove(){
    for (int i = 0; i < 2; i++){
        if (!_Block[i].active){
            _Block[i].point.y = (winSize.height / 4 + weight) + _Block[i].size.height;
        }

        // �ύX�����X�e�[�^�X�𔽉f������
        block_image[i]->setPosition(_Block[i].point);
    }

    // �㉺����u���b�N
    for (int i = 0; i < MOVING_BLOCK_MAX; i++){
        if (_MovingBlock[i].active){
            _MovingBlock[i].point.y = sin(_MovingBlock[i].angle+=0.1) * 10 + _MovingBlock[i].point.y;
        } else{
            _MovingBlock[i].point.y = _WarpBlock[B].point.y + weight + _MovingBlock[i].size.height;
        }

        // �ύX�����X�e�[�^�X�𔽉f������
        moving_block_image[i]->setPosition(_MovingBlock[i].point);
    }
}

void Stage02::BlockColor(){
    for (int i = 0; i < 2; i++){
        //------���u���b�N-----//
        if (_Block[i].active){
            _Block[i].col = Color3B::ORANGE;
        }
        else{
            _Block[i].col = Color3B::WHITE;
        }

        // �ύX�����X�e�[�^�X�𔽉f������
        block_image[i]->setColor(_Block[i].col);


        //-----�㉺�u���b�N-----//
        if (!_MovingBlock[i].active){
            _MovingBlock[i].col = Color3B::WHITE;
        }
        // �ύX�����X�e�[�^�X�𔽉f������
        moving_block_image[i]->setColor(_MovingBlock[i].col);
    }


    //-----Target�F�̕ύX-----//
    if (!_Target.active){
        _Target.col = Color3B::WHITE;
    }
    // �ύX�����X�e�[�^�X�𔽉f������
    target_image->setColor(_Target.col);
}

// �v���C���[�ƃu���b�N�̂����蔻��
// �v���C���[�̂��蔲���h�~
void Stage02::BlockToPlayer(){
    // ���u���b�N�̂����蔻��
    for (int i = 0; i < 2; i++){
        // Block�ɍ����瓖���������̏���
        if ((owata->_Owata.point.x + owata->_Owata.size.width) > _Block[i].point.x){
            if ((owata->_Owata.point.x + owata->_Owata.size.width) < _Block[i].point.x + 10){ // ���蔲���h�~��+10
                if ((owata->_Owata.point.y + owata->_Owata.size.height) > _Block[i].point.y){
                    if (owata->_Owata.point.y < _Block[i].point.y + _Block[i].size.height){
                        owata->_Owata.point.x = _Block[i].point.x - owata->_Owata.size.width;
                    }
                }
            }
        }

        // Block�ɉE���瓖���������̏���
        if (owata->_Owata.point.x < (_Block[i].point.x + _Block[i].size.width)){
            if (owata->_Owata.point.x > _Block[i].point.x - 10){ // ���蔲���h�~��-10
                if ((owata->_Owata.point.y + owata->_Owata.size.height) > _Block[i].point.y){
                    if (owata->_Owata.point.y < _Block[i].point.y + _Block[i].size.height){
                        owata->_Owata.point.x = _Block[i].point.x + _Block[i].size.width;
                    }
                }
            }
        }
    }

    // �㉺����u���b�N�Ƃ̂����蔻��
    if (_MovingBlock[1].active){
        if (owata->_Owata.point.x + owata->_Owata.size.width >= _MovingBlock[1].point.x){
            owata->_Owata.point.x = _MovingBlock[1].point.x - owata->_Owata.size.width;
        }
    }
}

void Stage02::WarpTrigger(){
    if (rect_to_rect(owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height,
                     _WarpBlock[A].point.x, _WarpBlock[A].point.y, _WarpBlock[A].size.width, _WarpBlock[A].size.height)){
        owata->_Owata.point = Point(_WarpBlock[B].point.x + _WarpBlock[B].size.width/2*3,
                                    _WarpBlock[B].point.y);
    }
    if (rect_to_rect(owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height,
                     _WarpBlock[C].point.x, _WarpBlock[C].point.y, _WarpBlock[C].size.width, _WarpBlock[C].size.height)){
        owata->_Owata.point = Point(_WarpBlock[D].point.x + _WarpBlock[D].size.width / 2 * 3,
                                    _WarpBlock[D].point.y);
    }
}

void Stage02::GoalScene(){
    // �I���^��Gaol�̂����蔻��
    if (rect_to_rect(owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height,
        _Goal.point.x, _Goal.point.y, _Goal.size.width, _Goal.size.height)){

        // ���C(Goal)���A�N�e�B�u�ɂ���
        _Goal.active = true;
        // �����Ă���e�����ł�����
        for (int i = 0; i < 2; i++){
            owata->gun_image[i]->setOpacity(0);
        }
    }

    // ���C�̉��o
    if (_Goal.active){
        // Goal���A�N�e�B�u���I���^�̈ړ��𐧌�����
        owata->pause = true;

        _Goal.tx_point = Point(0, 400);  // �摜�̐؂���ʒu��ύX
        _Goal.point.x += _Goal.speed;    // Goal�摜�̈ړ�

        if (_Goal.point.x >= winSize.width){
            owata->_Owata.point.x += owata->_Owata.speed;
            comment_image->setOpacity(255);
            comment_image->setPosition(Point(owata->_Owata.point.x, owata->_Owata.point.y + owata->_Owata.size.height));
        }

        //----------�����ŃV�[���ړ�������------------//
        // �Ƃ肠����StageSelectScene�Ɉړ�������
        if (owata->_Owata.point.x >= winSize.width){
            Director::getInstance()->replaceScene(StageSelect::createScene());
        }
    }

    // �ύX�����X�e�[�^�X�̔��f
    goal_image->setTextureRect(Rect(_Goal.tx_point.x, _Goal.tx_point.y,
        _Goal.tx_size.width, _Goal.tx_size.height));
    goal_image->setPosition(_Goal.point);

    owata->owata_image->setPosition(owata->_Owata.point);
}

void Stage02::PlayerUpdate(){
    owata->owata_image->setPosition(owata->_Owata.point);
}

void Stage02::Pause(){
    if (_Pause.active){
        owata->pause = true;
        _Pause.visi = 130;
    }
    else{
        owata->pause = false;
        _Pause.visi = 0;
    }
    // �ύX�����X�e�[�^�X�𔽉f������
    pause_bg->setOpacity(_Pause.visi);
}

void Stage02::update(float delta){

    BlockTrigger();
    if (!_Pause.active){
        // ����������pause�ł͂Ȃ����̂ݍs��
        BlockMove();
    }
    BlockColor();
    BlockToPlayer();

    WarpTrigger();

    PlayerUpdate();
    // Goal���o����pause��ʂɂȂ�Ȃ��悤�ɂ���
    if (!_Goal.active){
        Pause();
    }

    GoalScene();
}