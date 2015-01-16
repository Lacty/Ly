
#include "StageSelectScene.h"
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

    // �N���G�C�g
    owata = PlayerOwata::create();

    // ���̎n�_�ƏI�_�����肷��
    startingPoint = Point(0, winSize.height/4);
    endingPoint   = Point(winSize.width, winSize.height/4);
    // ���̐��̑���������
    weight = 5;


    // _Block���Ƃ肠����������
    for (int i = 0; i < 2; i++){
        _Block[i] = { true,
            Point(0, 0), Size(0, 0),
            Point(400/* + i*200*/, 0), Size(100, 100),
            1,
            Color3B::ORANGE,
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

    // _Tutorial���Ƃ肠����������
    _Tutorial = { true,
        Point(winSize.width/2, winSize.height/4*3), Size(0, 0),
        Point(0, 200), Size(300, 200),
        2,
        Color3B::WHITE, 255,
        true,
        0, 0, 0, 0
    };

    // _Pause���Ƃ肠����������
    _Pause = { false,
        Point(0, 0), Size(0, 0),
        Point(0, 500), Size(200, 200),
        1,
        Color3B::WHITE, 0,
        true,
        0, 0, 0, 0
    };


    /////////////////////////////////////////////////////
    // �f�o�b�O�p�Ƀv���C���[�̈ʒu��ύX�ł���悤�ɂ���
    owata->_Owata.point = Point(0, winSize.height/4);
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

    // owata(Player)�̎���
    this->addChild(owata);

    //----------���̕`��---------//
    drawFloor = DrawNode::create();
    drawFloor->drawSegment(startingPoint, endingPoint, weight, Color4F::BLACK);
    this->addChild(drawFloor);


    //----------���Block---------//
    // �`��ʒu�̌���
    _Block[0].point = Point(winSize.width/3, winSize.height/4+weight);   // ���̐��ɔ��Ȃ��悤��
    _Block[1].point = Point(winSize.width/5*3, winSize.height/4+weight); // ���̑���(weight)����ɔz�u

    for (int i = 0; i < 2; i++){
        _Block[i].size = Size(_Block[i].tx_size.width * _Block[i].scale,
                              _Block[i].tx_size.height * _Block[i].scale);

        block_image[i] = Sprite::create("stage01_image.png");
        block_image[i]->setPosition(_Block[i].point);
        block_image[i]->setTextureRect(Rect(_Block[i].tx_point.x, _Block[i].tx_point.y,
                                            _Block[i].tx_size.width, _Block[i].tx_size.height));
        block_image[i]->setScale(_Block[i].scale);
        block_image[i]->setAnchorPoint(Point(0, 0));
        this->addChild(block_image[i]);
    }


    //---------���C�̕`��---------//
    _Goal.size = Size(_Goal.tx_size.width * _Goal.scale,
                      _Goal.tx_size.height * _Goal.scale);
    _Goal.point = Point(winSize.width - _Goal.size.width - _Goal.size.width/30,
                        winSize.height/4);

    goal_image = Sprite::create("stage01_image.png");
    goal_image->setPosition(_Goal.point);
    goal_image->setTextureRect(Rect(_Goal.tx_point.x, _Goal.tx_point.y,
                                    _Goal.tx_size.width, _Goal.tx_size.height));
    goal_image->setAnchorPoint(Point(0, 0));
    goal_image->setScale(_Goal.scale);
    this->addChild(goal_image);

    //------------�I��点�Ă�[-----------//
    // Goal��̉��o�Eowata�ɃR�����g������
    comment_image = Sprite::create("stage01_image.png");
    comment_image->setPosition(Point(0, 0));
    comment_image->setTextureRect(Rect(300, 200, 200, 100));
    comment_image->setOpacity(0);// ��\���ɂ��邽�߂ɓ��ߓx��0
    this->addChild(comment_image);
    

    //---------�`���[�g���A��(�摜)�̕`��----------//
    tutorial_image = Sprite::create("stage01_image.png");
    tutorial_image->setPosition(_Tutorial.point);
    tutorial_image->setTextureRect(Rect(_Tutorial.tx_point.x, _Tutorial.tx_point.y,
                                        _Tutorial.tx_size.width, _Tutorial.tx_size.height));
    tutorial_image->setScale(_Tutorial.scale);
    this->addChild(tutorial_image);

    //---------Pause--------//
    // pause��ʗp�w�i
    pause_bg = LayerColor::create(Color4B::BLACK, winSize.width, winSize.height);
    pause_bg->setOpacity(_Pause.visi);
    this->addChild(pause_bg);

    // ���ۂɕ`�悵�Ă���摜�̃T�C�Y���擾
    _Pause.size = Size(_Pause.tx_size.width * _Pause.scale,
                       _Pause.tx_size.height * _Pause.scale);
    // �`��ʒu������
    _Pause.point = Point(winSize.width - _Pause.size.width - _Pause.size.width/20,
                         winSize.height - _Pause.size.height - _Pause.size.height/20);

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
void Stage01::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);

        // �S�[���ɒ����Ă��Ȃ��ԃ|�[�Y��ʂ�L���ɂ���
        if (!_Goal.active){
            if (!_Pause.active){
                if (point_to_rect(location.x, location.y, _Pause.point.x, _Pause.point.y, _Pause.size.width, _Pause.size.height)){
                    _Pause.active = true;
                }
            } else{
                if (point_to_rect(location.x, location.y, _Pause.point.x, _Pause.point.y, _Pause.size.width, _Pause.size.height)){
                    _Pause.active = false;
                }
            }
        }

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

        iterator++;
    }
    return;
}


void Stage01::BlockTrigger(){
    for (int i = 0; i < 2; i++){
        for (int s = 0; s < 2; s++){
            if (rect_to_rect(owata->_Shots[s].point.x, owata->_Shots[s].point.y, owata->_Shots[s].size.width, owata->_Shots[s].size.height,
                            _Block[i].point.x, _Block[i].point.y, _Block[i].size.width, _Block[i].size.height)){
                _Block[i].active = false;
                owata->_Shots[s].active = false;
            }
        }
    }
}

void Stage01::BlockMove(){
    for (int i = 0; i < 2; i++){
        if (!_Block[i].active){
            _Block[i].point.y = (winSize.height / 4 + weight) + _Block[i].size.height;
        }

        // �ύX�����X�e�[�^�X�𔽉f������
        block_image[i]->setPosition(_Block[i].point);
    }
}

void Stage01::BlockColor(){
    for (int i = 0; i < 2; i++){
        if (_Block[i].active){
            _Block[i].col = Color3B::ORANGE;
        } else{
            _Block[i].col = Color3B::WHITE;
        }

        // �ύX�����X�e�[�^�X�𔽉f������
        block_image[i]->setColor(_Block[i].col);
    }
}

// �v���C���[�ƃu���b�N�̂����蔻��
// �v���C���[�̂��蔲���h�~
void Stage01::BlockToPlayer(){
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
}

void Stage01::GoalScene(){
    // �I���^��Gaol�̂����蔻��
    if (rect_to_rect(owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height,
                     _Goal.point.x, _Goal.point.y, _Goal.size.width, _Goal.size.height)){

        // ���C(Goal)���A�N�e�B�u�ɂ���
        _Goal.active = true;
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
            comment_image->setPosition(Point(owata->_Owata.point.x, owata->_Owata.point.y+owata->_Owata.size.height));
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

void Stage01::PlayerUpdate(){
    owata->owata_image->setPosition(owata->_Owata.point);
}

void Stage01::Pause(){
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

void Stage01::update(float delta){

    BlockTrigger();
    BlockMove();
    BlockColor();
    BlockToPlayer();

    PlayerUpdate();
    Pause();

    GoalScene();
}