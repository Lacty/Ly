
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


// コンストラクタ
PlayerOwata::PlayerOwata(){

    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // _Owataをとりあえず初期化
    _Owata = { true,
        Point(0, winSize.height/4), Size(0, 0),
        Point(0, 0), Size(200, 100),
        1,
        Color3B::WHITE, 1,
        true,
        0, 0, 0, 3
    };

    // _Shotsをとりあえず初期化
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

    // _ShotButtonをとりあえず初期化
    _ShotButton = { false,
        Point(0, 0), Size(0, 0),
        Point(700, 300), Size(200, 100),
        1.8,
        Color3B::WHITE,
        true,
        0, 0, 0, 0
    };

    // _Buttonをとりあえず初期化
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

    // _Deadの初期化
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
    このクラスを他で生成しないようにする処理
*/
PlayerOwata &PlayerOwata::getInstance(){
    // 初回のみインスタンスを生成
    static PlayerOwata singleton;
    return singleton;
}


bool PlayerOwata::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }

    // マルチタッチ操作を有効にする
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true); // 理解不能とりあえずtrue
    listener->onTouchesBegan = CC_CALLBACK_2(PlayerOwata::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(PlayerOwata::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(PlayerOwata::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    // Updateを呼ぶ
    this->scheduleUpdate();


    //--------オワタの描画--------//
    owata_image = Sprite::create("player_image.png");
    // ステータスの初期化
    owata_image->setPosition(_Owata.point);
    owata_image->setTextureRect(Rect(_Owata.tx_point.x, _Owata.tx_point.y,
                                     _Owata.tx_size.width, _Owata.tx_size.height));
    owata_image->setScale(_Owata.scale);
    owata_image->setAnchorPoint(Point(0, 0));
    this->addChild(owata_image);

    // 実際に描画されている画像のサイズを取得
    _Owata.size = Size(_Owata.tx_size.width  * _Owata.scale,
                       _Owata.tx_size.height * _Owata.scale);


    //----------弾の描画----------//
    for (int i = 0; i < SHOT_MAX; i++){
        gun_image[i] = Sprite::create("player_image.png");
        gun_image[i]->setPosition(_Shots[i].point);
        gun_image[i]->setTextureRect(Rect(_Shots[i].tx_point.x, _Shots[i].tx_point.y,
                                          _Shots[i].tx_size.width, _Shots[i].tx_size.height));
        gun_image[i]->setAnchorPoint(Point(0, 0));
        gun_image[i]->setScale(_Shots[i].scale);
        this->addChild(gun_image[i]);
    }

    // 実際に描画している画像サイズを取得
    for (int i = 0; i < SHOT_MAX; i++){
        _Shots[i].size = Size(_Shots[i].tx_size.width * _Shots[i].scale,
                              _Shots[i].tx_size.height * _Shots[i].scale);
    }

    //----------ShotButtonの描画----------//
    // 実際に描画している画像のサイズを取得
    _ShotButton.size = Size(_ShotButton.tx_size.width * _ShotButton.scale,
                            _ShotButton.tx_size.height * _ShotButton.scale);

    // 描画位置の変更
    _ShotButton.point = Point(winSize.width - (_ShotButton.size.width/20 * 21), _ShotButton.size.height/15);

    shot_button_image = Sprite::create("system_image.png");
    shot_button_image->setPosition(_ShotButton.point);
    shot_button_image->setTextureRect(Rect(_ShotButton.tx_point.x, _ShotButton.tx_point.y,
                                           _ShotButton.tx_size.width, _ShotButton.tx_size.height));
    shot_button_image->setAnchorPoint(Point(0, 0));
    shot_button_image->setScale(_ShotButton.scale);
    this->addChild(shot_button_image);


    //---------方向キーの描画----------//
    // 実際に描画している画像サイズを取得
    for (int i = 0; i < BUTTON_MAX; i++){
        _Button[i].size = Size(_Button[i].tx_size.width * _Button[i].scale,
            _Button[i].tx_size.height * _Button[i].scale);
    }

    // 描画位置を変更
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


// タップした時の処理
void PlayerOwata::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

        log("location.x=%f, location.y=%f", location.x, location.y);
        
        /*
            移動の処理をそのまま書くと"タップした間"の関数がないので
            処理が思うようにいかなかった
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
            ShotButtonをタップしたときの処理
            縦方向にあたり判定を伸ばしておく
        */
        if (point_to_rect(location.x, location.y, winSize.width - _ShotButton.size.width, 0, _ShotButton.size.width, _ShotButton.size.height*2)){
            // ShotButtonをタッチしたと判定
            isTouchShotButton = true;
            _ShotButton.active = true;
        }
        
        iterator++;
    }
    return;
}


// タップ中（押して動かしている間）の処理
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
            ShotButtonをタップしたときの処理
        */
        if (point_to_rect(location.x, location.y, winSize.width - _ShotButton.size.width, 0, _ShotButton.size.width, _ShotButton.size.height*2)){
            // タップし続けている間は弾が発射されないようにfalseにしておく
            isTouchShotButton = false;
        }

        iterator++;
    }
    return;
}


// 指を離したときの処理
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
            // ShotButtonから指を離した時
            isTouchShotButton = false;
        }

        iterator++;
    }
    return;
}


// オワタの移動制御
void PlayerOwata::owataMove(){
    // 画面外に出ないように移動制御
    if (_Owata.point.x < 0){
        isPushLeft = false;
    }
    if ((_Owata.point.x + _Owata.size.width) > winSize.width){
        isPushRight = false;
    }

    // 押されている方向に移動させる
    if (isPushRight){
        _Owata.point.x += _Owata.speed;
    }
    if (isPushLeft){
        _Owata.point.x -= _Owata.speed;
    }

    // オワタの位置を反映させる
    // 各ステージの更新処理の最後に置くことで
    // 変な描画をなくす
    // 例：ブロックにのめり込みなど
    // owata_image->setPosition(_Owata.point);
}

// オワタの画像切り替え
void PlayerOwata::owataSetTextureRect(){

    if (_Owata.right){
        _Owata.tx_point = Point(0, 0);
    }
    else{
        _Owata.tx_point = Point(600, 0);
    }

    // 切り替えた画像の切り出し位置を反映させる
    owata_image->setTextureRect(Rect(_Owata.tx_point.x, _Owata.tx_point.y,
                                     _Owata.tx_size.width, _Owata.tx_size.height));
}


// 弾を発射させる関数
void PlayerOwata::owataShot(){
    // ShotButtonをタップされたら
    if (isTouchShotButton){
        for (int i = 0; i < SHOT_MAX; i++){
            // 生成されてない弾を探す
            if (!_Shots[i].active){

                // 検索された中から弾を一つ生成する
                _Shots[i].active = true;

                // 生成する弾が左右どちらを向いているか保存
                if (_Owata.right){
                    _Shots[i].right = true;
                } else{
                    _Shots[i].right = false;
                }

                // 生成する弾の位置をキャラクターに合わせる
                // 射出する弾の方向にあわせて位置を変更
                if (_Shots[i].right){
                    _Shots[i].point = Point(_Owata.point.x, _Owata.point.y);
                } else{
                    _Shots[i].point = Point(_Owata.point.x, _Owata.point.y);
                }

                // 他の弾を生成しないようにブレイク
                isTouchShotButton = false;
                break;
            }
        }
    }

    // 弾の移動制御
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].active){
            if (_Shots[i].right){
                _Shots[i].point.x += _Shots[i].speed;
            } else{
                _Shots[i].point.x -= _Shots[i].speed;
            }
        }
    }

    // 画面外にでたら弾を消す
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].point.x < 0){
            _Shots[i].active = false;
        }
        // 画面横幅サイズ - 弾の画像横幅
        if (_Shots[i].point.x > winSize.width - _Shots[i].size.width){
            _Shots[i].active = false;
        }
    }

    // 弾の"表示""非表示"を弾の生死によって変更
    // "visi"はint型なのでtrue,falseではなく数字で判定させる
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].active){
            _Shots[i].visi = 1; /* true */
        } else{
            _Shots[i].visi = 0; /* false */
            _Shots[i].point = Point(0, 0);
        }
    }

    // 弾の画像切り取り位置を変更
    for (int i = 0; i < SHOT_MAX; i++){
        if (_Shots[i].right){
            _Shots[i].tx_point = Point(400, 100);
        } else{
            _Shots[i].tx_point = Point(500, 100);
        }
    }

    // 変更したステータスを反映させる
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
        // オワタが死んだら操作不能にする
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
    dead_image->setVisible(_Dead.visi); //透過度
}

void PlayerOwata::visiblePlayer(){
    if (!_Owata.active){
        _Owata.visi = 0;
    }
    owata_image->setVisible(_Owata.visi); //透過度
}


// 方向キーを押したときボタンの色を変更させる処理
// PS.ShotButtonの色変更も追加
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

    // pause画面中の色を決定
    if (pause){
        for (int i = 0; i < 2; i++){
            _Button[i].col = Color3B::WHITE;
        }
        _ShotButton.col = Color3B::WHITE;
    }

    // 変更した色を反映させる
    for (int i = 0; i < BUTTON_MAX; i++){
        button_image[i]->setColor(_Button[i].col);
    }
    shot_button_image->setColor(_ShotButton.col);
}


void PlayerOwata::update(float delta){
    
    if (!pause){
        // 関数呼び出し
        owataMove();
        owataSetTextureRect();
        owataShot();
    }
    visiblePlayer();
    setButtonColor();
    owataDead();
}