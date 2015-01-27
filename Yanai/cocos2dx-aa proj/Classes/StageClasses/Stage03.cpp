
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


// コンストラクタ
Stage03::Stage03(){
    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を指定
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    // owataのクリエイト
    owata = PlayerOwata::create();

    // 床の始点と終点を決定する
    for (int i = 0; i < 2; i++){
        floorStartingPoint[i] = Point(0, winSize.height / 4 + winSize.height / 8 * 3 * i);
        floorEndingPoint[i] = Point(winSize.width, winSize.height / 4 + winSize.height / 8 * 3 * i);
    }
    // 床の線の太さを決定
    floorWeight = 5;

    // _Pauseをとりあえず初期化
    _Pause = { false,
        Point(0, 0), Size(0, 0),
        Point(200, 500), Size(200, 200),
        1,
        Color3B::WHITE, 0,
        true,
        0, 0, 0, 0
    };

    // _Buttonをとりあえず初期化
    _Button = { false,
        Point(0, 0), Size(0, 0),
        Point(0, 0), Size(100, 100),
        1,
        Color3B::ORANGE, 255,
        true,
        0, 0, 0, 0
    };

    // WallBlockをとりあえず初期化
    _WallBlock = { true,
        Point(0, 0), Size(100, 100),
        Point(100, 0), Size(100, 100),
        1,
        Color3B::BLACK, 255,
        true,
        0, 0, 0, 0
    };

    // _WarpBlockをとりあえず初期化
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

    // _Blockをとりあえず初期化
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

    // _SignBoardをとりあえず初期化
    _SignBoard = { false,
        Point(0, 0), Size(0, 0),
        Point(0, 600), Size(300, 200),
        1,
        Color3B::BLACK, 255,
        true,
        0, 0, 0, 2.5
    };
}


bool Stage03::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }

    // マルチタッチ操作を有効にする
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(Stage03::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Stage03::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Stage03::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // Updateを呼ぶ
    this->scheduleUpdate();

    // owata(Player)の実装
    this->addChild(owata);

    //----------床の描画---------//
    for (int i = 0; i < 2; i++){
        drawFloor[i] = DrawNode::create();
        drawFloor[i]->drawSegment(floorStartingPoint[i], floorEndingPoint[i], floorWeight, Color4F::BLACK);
        this->addChild(drawFloor[i]);
    }

    //---------Button--------//
    // 実際に描画されている画像サイズを取得
    _Button.size = Size(_Button.tx_size.width * _Button.scale, _Button.tx_size.height * _Button.scale);

    // 描画する位置を決定
    _Button.point = Point(owata->_Owata.point.x + owata->_Owata.size.width/5*8,
                          floorStartingPoint[0].y + floorWeight);
    button_image = Sprite::create("stage03_image.png");
    button_image->setPosition(_Button.point);
    button_image->setTextureRect(Rect(_Button.tx_point.x, _Button.tx_point.y,
                                      _Button.tx_size.width, _Button.tx_size.height));
    button_image->setScale(_Button.scale);
    button_image->setAnchorPoint(Point(0, 0));
    button_image->setColor(_Button.col);
    this->addChild(button_image);

    //----------WallBlockの描画---------//
    _WallBlock.point = Point(_Button.point.x + _Button.size.width * 3.5, floorStartingPoint[0].y);
    wall_image = Sprite::create("stage02_image.png");
    wall_image->setPosition(_WallBlock.point);
    wall_image->setTextureRect(Rect(100, 0, 100, 100));
    wall_image->setAnchorPoint(Point(0, 0));
    wall_image->setColor(_WallBlock.col);
    this->addChild(wall_image);

    //-----------WarpBlock-----------//
    // 実際に描画されている画像のサイズを取得
    for (int i = 0; i < WARP_MAX; i++){
        _WarpBlock[i].size = Size(_WarpBlock[i].tx_size.width * _WarpBlock[i].scale,
            _WarpBlock[i].tx_size.height* _WarpBlock[i].scale);
    }
    // 描画位置の決定
    _WarpBlock[A].point = Point(_Button.point.x + _Button.size.width * 2, floorStartingPoint[A].y + floorWeight);
    _WarpBlock[B].point = Point(0, floorStartingPoint[1].y + floorWeight);
    _WarpBlock[C].point = Point(winSize.width / 5 * 4, floorStartingPoint[1].y + floorWeight);
    _WarpBlock[D].point = Point(winSize.width / 7 * 3, floorStartingPoint[0].y + floorWeight);

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
        abcd_image[i]->setTextureRect(Rect(300 + i * 100, 200, 100, 100));
        abcd_image[i]->setAnchorPoint(Point(0, 0));
        abcd_image[i]->setColor(_WarpBlock[i].col);
        this->addChild(abcd_image[i]);
    }

    //---------矢印Block---------//
    // 実際に描画されている画像サイズを取得
    for (int i = 0; i < BLOCK_MAX; i++){
        _Block[i].size = Size(_Block[i].tx_size.width * _Block[i].scale,
                              _Block[i].tx_size.height * _Block[i].scale);
    }
    // 描画位置を決定
    _Block[0].point = Point(winSize.width/5, floorStartingPoint[1].y + floorWeight);
    _Block[1].point = Point(winSize.width/5*2, floorStartingPoint[1].y + floorWeight);
    _Block[2].point = Point(winSize.width/2, floorStartingPoint[1].y + floorWeight + _Block[2].size.height);
    _Block[3].point = Point(winSize.width/10*7, floorStartingPoint[1].y + floorWeight);

    _Block[0].col = Color3B::YELLOW;
    _Block[2].col = Color3B::YELLOW;
    _Block[2].tx_point = Point(600, 0);
    _Block[2].active = false;

    for (int i = 0; i < BLOCK_MAX; i++){
        block_image[i] = Sprite::create("stage01_image.png");
        block_image[i]->setPosition(_Block[i].point);
        block_image[i]->setTextureRect(Rect(_Block[i].tx_point.x, _Block[i].tx_point.y,
                                            _Block[i].tx_size.width, _Block[i].tx_size.height));
        block_image[i]->setAnchorPoint(Point(0, 0));
        block_image[i]->setScale(_Block[i].scale);
        block_image[i]->setColor(_Block[i].col);
        this->addChild(block_image[i]);
    }


    //----------看板SignBoard----------//
    _SignBoard.size = Size(_SignBoard.tx_size.width * _SignBoard.scale,
                           _SignBoard.tx_size.height * _SignBoard.scale);
    // 描画位置を決定
    _SignBoard.point = Point(-_SignBoard.size.width/3*4, floorStartingPoint[0].y);

    signboard_image = Sprite::create("stage01_image.png");
    signboard_image->setPosition(_SignBoard.point);
    signboard_image->setTextureRect(Rect(_SignBoard.tx_point.x, _SignBoard.tx_point.y,
                                         _SignBoard.tx_size.width, _SignBoard.tx_size.height));
    signboard_image->setAnchorPoint(Point(0, 0));
    signboard_image->setColor(_SignBoard.col);
    this->addChild(signboard_image);

    //-------現実からは逃げられない-------//
    real_image = Sprite::create("stage03_image.png");
    real_image->setTextureRect(Rect(100, 0, 300, 200));
    real_image->setPosition(Point(winSize.width/2, winSize.height/2));
    real_image->setVisible(0); //--非表示--//
    real_image->setScale(1.5); //--1.5拡大--//
    this->addChild(real_image);


    //---------Pause--------//
    // pause画面用背景
    pause_bg = LayerColor::create(Color4B::BLACK, winSize.width, winSize.height);
    pause_bg->setOpacity(_Pause.visi);
    this->addChild(pause_bg);

    // 実際に描画している画像のサイズを取得
    _Pause.size = Size(_Pause.tx_size.width * _Pause.scale,
        _Pause.tx_size.height * _Pause.scale);
    // 描画位置を決定
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

// タップした時の処理
void Stage03::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);

        // pause画面
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

// タップ中（押して動かしたとき）の処理
void Stage03::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

// 指を離したときの処理
void Stage03::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

void Stage03::BlockTrigger(){
    // ボタンとowataのあたり判定
    if (rect_to_rect(owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height,
                     _Button.point.x, _Button.point.y, _Button.size.width, _Button.size.height)){
        _Button.active = true;
    }
    // 矢印BlockとShot
    for (int i = 0; i < 2; i++){
        if (rect_to_rect(owata->_Shots[i].point.x, owata->_Shots[i].point.y, owata->_Shots[i].size.width, owata->_Shots[i].size.height,
            _Block[0].point.x, _Block[0].point.y, _Block[0].size.width, _Block[0].size.height)){
            owata->_Shots[i].active = false;
            _Block[0].active = false;
            _Block[2].active = true;
        }
    }
    for (int i = 0; i < 2; i++){
        if (rect_to_rect(owata->_Shots[i].point.x, owata->_Shots[i].point.y, owata->_Shots[i].size.width, owata->_Shots[i].size.height,
            _Block[1].point.x, _Block[1].point.y, _Block[1].size.width, _Block[1].size.height)){
            owata->_Shots[i].active = false;
            _Block[1].active = false;
        }
    }
    for (int i = 0; i < 2; i++){
        if (rect_to_rect(owata->_Shots[i].point.x, owata->_Shots[i].point.y, owata->_Shots[i].size.width, owata->_Shots[i].size.height,
            _Block[2].point.x, _Block[2].point.y, _Block[2].size.width, _Block[2].size.height)){
            owata->_Shots[i].active = false;
            _Block[2].active = false;
            _Block[0].active = true;
        }
    }
    for (int i = 0; i < 2; i++){
        if (rect_to_rect(owata->_Shots[i].point.x, owata->_Shots[i].point.y, owata->_Shots[i].size.width, owata->_Shots[i].size.height,
            _Block[3].point.x, _Block[3].point.y, _Block[3].size.width, _Block[3].size.height)){
            owata->_Shots[i].active = false;
            _Block[3].active = false;
        }
    }
}

void Stage03::BlockMove(){
    for (int i = 0; i < BLOCK_MAX; i++){
        if (_Block[i].active){
            _Block[i].point.y = floorStartingPoint[1].y + floorWeight;
        } else{
            _Block[i].point.y = floorStartingPoint[1].y + floorWeight + _Block[i].size.height;
        }
        // 変更したステータスを反映させる
        block_image[i]->setPosition(_Block[i].point);
    }
}

void Stage03::BlockColor(){
    if (_Button.active){
        _Button.col = Color3B::WHITE;
    }
    // 変更したステータスを反映させる
    button_image->setColor(_Button.col);

    for (int i = 0; i < BLOCK_MAX; i++){
        if (!_Block[i].active){
            _Block[i].col = Color3B::WHITE;
        } else{
            _Block[i].col = Color3B::ORANGE;
        }
        block_image[i]->setColor(_Block[i].col);
    }
}

void Stage03::BlockToPlayer(){
    // ワープポイントとプレイヤーのあたり判定
    if (rect_to_rect(_WarpBlock[A].point.x, _WarpBlock[A].point.y, _WarpBlock[A].size.width, _WarpBlock[A].size.height,
        owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height)){
        owata->_Owata.point = Point(_WarpBlock[B].point.x + _WarpBlock[B].size.width,
                                    _WarpBlock[B].point.y);
    }
    if (rect_to_rect(_WarpBlock[C].point.x, _WarpBlock[C].point.y, _WarpBlock[C].size.width, _WarpBlock[C].size.height,
        owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height)){
        owata->_Owata.point = Point(_WarpBlock[D].point.x + _WarpBlock[D].size.width,
            _WarpBlock[D].point.y);
    }

    for (int i = 0; i < BLOCK_MAX; i++){
        // Blockに左から当たった時の処理
        if ((owata->_Owata.point.x + owata->_Owata.size.width) > _Block[i].point.x){
            if ((owata->_Owata.point.x + owata->_Owata.size.width) < _Block[i].point.x + 10){ // すり抜け防止に+10
                if ((owata->_Owata.point.y + owata->_Owata.size.height) > _Block[i].point.y){
                    if (owata->_Owata.point.y < _Block[i].point.y + _Block[i].size.height){
                        owata->_Owata.point.x = _Block[i].point.x - owata->_Owata.size.width;
                    }
                }
            }
        }
        // Blockに右から当たった時の処理
        if (owata->_Owata.point.x < (_Block[i].point.x + _Block[i].size.width)){
            if (owata->_Owata.point.x > _Block[i].point.x - 10){ // すり抜け防止に-10
                if ((owata->_Owata.point.y + owata->_Owata.size.height) > _Block[i].point.y){
                    if (owata->_Owata.point.y < _Block[i].point.y + _Block[i].size.height){
                        owata->_Owata.point.x = _Block[i].point.x + _Block[i].size.width;
                    }
                }
            }
        }
    }

    // WallBlockに左から当たった時の処理
    if ((owata->_Owata.point.x + owata->_Owata.size.width) > _WallBlock.point.x){
        if ((owata->_Owata.point.x + owata->_Owata.size.width) < _WallBlock.point.x + 10){ // すり抜け防止に+10
            if ((owata->_Owata.point.y + owata->_Owata.size.height) > _WallBlock.point.y){
                if (owata->_Owata.point.y < _WallBlock.point.y + _WallBlock.size.height){
                    owata->_Owata.point.x = _WallBlock.point.x - owata->_Owata.size.width;
                }
            }
        }
    }
    // WallBlockに右から当たった時の処理
    if (owata->_Owata.point.x < (_WallBlock.point.x + _WallBlock.size.width)){
        if (owata->_Owata.point.x > _WallBlock.point.x - 10){ // すり抜け防止に-10
            if ((owata->_Owata.point.y + owata->_Owata.size.height) > _WallBlock.point.y){
                if (owata->_Owata.point.y < _WallBlock.point.y + _WallBlock.size.height){
                    owata->_Owata.point.x = _WallBlock.point.x + _WallBlock.size.width;
                }
            }
        }
    }
}

void Stage03::SignBoard(){
    if (_Button.active){
        // ボタンを踏んだらactiveにする
        _SignBoard.active = true;
    }
    if (!_Pause.active){
        if (_SignBoard.active){
            // 看板の移動
            _SignBoard.point.x += _SignBoard.speed;
        }
    }

    // ワープポイントとプレイヤーのあたり判定
    if (rect_to_rect(_WarpBlock[A].point.x, _WarpBlock[A].point.y, _WarpBlock[A].size.width, _WarpBlock[A].size.height,
        _SignBoard.point.x, _SignBoard.point.y, _SignBoard.size.width, _SignBoard.size.height)){
        _SignBoard.point = Point(_WarpBlock[B].point.x + _WarpBlock[B].size.width,
            _WarpBlock[B].point.y);
    }
    if (rect_to_rect(_WarpBlock[C].point.x, _WarpBlock[C].point.y, _WarpBlock[C].size.width, _WarpBlock[C].size.height,
        _SignBoard.point.x, _SignBoard.point.y, _SignBoard.size.width, _SignBoard.size.height)){
        _SignBoard.point = Point(_WarpBlock[D].point.x + _WarpBlock[D].size.width,
            _WarpBlock[D].point.y);
    }

    // プレイヤーと看板とのあたり判定
    if (rect_to_rect(owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height,
        _SignBoard.point.x, _SignBoard.point.y, _SignBoard.size.width, _SignBoard.size.height)){
        owata->_Owata.active = false;
    }

    if (owata->_Dead.active){
        real_image->setVisible(255); //--表示--//
    }

    //////////////////////////////////////////////////////////////
    // シーン移動
    if (owata->_Dead.angle > 180){
        Director::getInstance()->replaceScene(StageSelect::createScene());
    }

    // 変更したステータスを反映させる
    signboard_image->setPosition(_SignBoard.point);
}

void Stage03::PlayerUpdate(){
    owata->owata_image->setPosition(owata->_Owata.point);
}

void Stage03::Pause(){
    if (_Pause.active){
        owata->pause = true;
        _Pause.visi = 130;
    }
    else{
        owata->pause = false;
        _Pause.visi = 0;
    }
    // 変更したステータスを反映させる
    pause_bg->setOpacity(_Pause.visi);
}

void Stage03::update(float delta){
    
    BlockTrigger();
    if (!_Pause.active){
        BlockMove();
    }
    BlockToPlayer();
    BlockColor();

    if (!owata->_Dead.active){
        Pause();
    }
    PlayerUpdate();

    SignBoard();
}