
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


// コンストラクタ
Stage01::Stage01(){
    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を指定
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    // クリエイト
    owata = PlayerOwata::create();

    // 床の始点と終点を決定する
    startingPoint = Point(0, winSize.height/4);
    endingPoint   = Point(winSize.width, winSize.height/4);
    // 床の線の太さを決定
    weight = 5;


    // _Blockをとりあえず初期化
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

    // _Goalをとりあえず初期化
    _Goal = { false,
        Point(0, 0), Size(0, 0),
        Point(0, 0), Size(300, 200),
        1,
        Color3B::WHITE, 255,
        true,
        0, 0, 0, 3
    };

    // _Tutorialをとりあえず初期化
    _Tutorial = { true,
        Point(winSize.width/2, winSize.height/4*3), Size(0, 0),
        Point(0, 200), Size(300, 200),
        2,
        Color3B::WHITE, 255,
        true,
        0, 0, 0, 0
    };

    // _Pauseをとりあえず初期化
    _Pause = { false,
        Point(0, 0), Size(0, 0),
        Point(0, 500), Size(200, 200),
        1,
        Color3B::WHITE, 0,
        true,
        0, 0, 0, 0
    };


    /////////////////////////////////////////////////////
    // デバッグ用にプレイヤーの位置を変更できるようにする
    owata->_Owata.point = Point(0, winSize.height/4);
}


bool Stage01::init(){

    if ( !Layer::init() )
    {
        return false;
    }
    
    // マルチタッチ操作を有効にする
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(Stage01::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Stage01::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Stage01::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // Updateを呼ぶ
    this->scheduleUpdate();

    // owata(Player)の実装
    this->addChild(owata);

    //----------床の描画---------//
    drawFloor = DrawNode::create();
    drawFloor->drawSegment(startingPoint, endingPoint, weight, Color4F::BLACK);
    this->addChild(drawFloor);


    //----------矢印Block---------//
    // 描画位置の決定
    _Block[0].point = Point(winSize.width/3, winSize.height/4+weight);   // 床の線に被らないように
    _Block[1].point = Point(winSize.width/5*3, winSize.height/4+weight); // 線の太さ(weight)分上に配置

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


    //---------樹海の描画---------//
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

    //------------終わらせてよー-----------//
    // Goal後の演出・owataにコメントをつける
    comment_image = Sprite::create("stage01_image.png");
    comment_image->setPosition(Point(0, 0));
    comment_image->setTextureRect(Rect(300, 200, 200, 100));
    comment_image->setOpacity(0);// 非表示にするために透過度を0
    this->addChild(comment_image);
    

    //---------チュートリアル(画像)の描画----------//
    tutorial_image = Sprite::create("stage01_image.png");
    tutorial_image->setPosition(_Tutorial.point);
    tutorial_image->setTextureRect(Rect(_Tutorial.tx_point.x, _Tutorial.tx_point.y,
                                        _Tutorial.tx_size.width, _Tutorial.tx_size.height));
    tutorial_image->setScale(_Tutorial.scale);
    this->addChild(tutorial_image);

    //---------Pause--------//
    // pause画面用背景
    pause_bg = LayerColor::create(Color4B::BLACK, winSize.width, winSize.height);
    pause_bg->setOpacity(_Pause.visi);
    this->addChild(pause_bg);

    // 実際に描画している画像のサイズを取得
    _Pause.size = Size(_Pause.tx_size.width * _Pause.scale,
                       _Pause.tx_size.height * _Pause.scale);
    // 描画位置を決定
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

// タップした時の処理
void Stage01::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);

        // ゴールに着いていない間ポーズ画面を有効にする
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

// タップ中（押して動かしたとき）の処理
void Stage01::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch  = (Touch*)(*iterator);
        auto location = touch->getLocation();

        iterator++;
    }
    return;
}

// 指を離したときの処理
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

        // 変更したステータスを反映させる
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

        // 変更したステータスを反映させる
        block_image[i]->setColor(_Block[i].col);
    }
}

// プレイヤーとブロックのあたり判定
// プレイヤーのすり抜け防止
void Stage01::BlockToPlayer(){
    for (int i = 0; i < 2; i++){
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
}

void Stage01::GoalScene(){
    // オワタとGaolのあたり判定
    if (rect_to_rect(owata->_Owata.point.x, owata->_Owata.point.y, owata->_Owata.size.width, owata->_Owata.size.height,
                     _Goal.point.x, _Goal.point.y, _Goal.size.width, _Goal.size.height)){

        // 樹海(Goal)をアクティブにする
        _Goal.active = true;
    }

    // 樹海の演出
    if (_Goal.active){
        // Goalがアクティブ中オワタの移動を制限する
        owata->pause = true;

        _Goal.tx_point = Point(0, 400);  // 画像の切り取り位置を変更
        _Goal.point.x += _Goal.speed;    // Goal画像の移動


        if (_Goal.point.x >= winSize.width){
            owata->_Owata.point.x += owata->_Owata.speed;
            comment_image->setOpacity(255);
            comment_image->setPosition(Point(owata->_Owata.point.x, owata->_Owata.point.y+owata->_Owata.size.height));
        }

        //----------ここでシーン移動させる------------//
        // とりあえずStageSelectSceneに移動させる
        if (owata->_Owata.point.x >= winSize.width){
            Director::getInstance()->replaceScene(StageSelect::createScene());
        }
    }

    // 変更したステータスの反映
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
    // 変更したステータスを反映させる
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