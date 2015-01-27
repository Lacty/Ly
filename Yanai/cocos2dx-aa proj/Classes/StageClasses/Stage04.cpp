
#include "StageSelectScene.h"
#include "Stage04.h"
#include "isHit.h"

USING_NS_CC;
using namespace collision;


Scene* Stage04::createScene()
{
    auto scene = Scene::create();
    auto layer = Stage04::create();
    scene->addChild(layer);
    return scene;
}


// コンストラクタ
Stage04::Stage04(){
    // 画面サイズを取得
    winSize = Director::getInstance()->getVisibleSize();

    // 背景色を指定
    _bg = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
    this->addChild(_bg);

    // _Playerの初期化
    _Player = { true,
        Point(0, 0), Size(400, 200),
        Point(200, 0), Size(400, 200),
        1,
        Color3B::WHITE, 255,
        true,
        0, 0, 0, 0
    };

    // _Hutonの初期化
    // activeがtrueになってから流れるようにするために
    // 始めはfalseにしておく
    for (int i = 0; i < HUTON_MAX; i++){
        _Huton[i] = { false,
            Point(winSize.width + 150, winSize.height/2), Size(0, 0),
            Point(0, 200), Size(300, 200),
            1,
            Color3B::WHITE, 255,
            true,
            0, 0, 0, 0
        };
    }

    // _Scoreの初期化
    for (int i = 0; i < NUM_MAX; i++){
        _Score[i] = { true,
            Point(winSize.width/2, winSize.height/4*3), Size(100, 200),
            Point(0, 0), Size(100, 200),
            1,
            Color3B::WHITE, 255,
            true,
            0, 0, 0, 0
        };
    }
    play_score = 0;

    // _Cloudの初期化
    for (int i = 0; i < CLOUD_MAX; i++){
        _Cloud[i] = { true,
            Point(0, 0), Size(400, 300),
            Point(0, 0), Size(400, 300),
            1,
            Color3B::WHITE, 255,
            true,
            0, 0, 0, 0
        };
    }

    // _Result_bgの初期化
    _Result_bg = { false,
        Point(0, 0), Size(winSize.width, winSize.height),
        Point(0, 0), Size(0, 0),
        1,
        Color3B::BLACK, 0,
        true,
        0, 0, 0, 0
    };

    // _ReStartの初期化
    _ReStart = { false,
        Point(winSize.width/2, winSize.height/4*3), Size(0, 0),
        Point(0, 0), Size(400, 200),
        2,
        Color3B::WHITE, 0,
        true,
        0, 0, 0, 0
    };

    // _BackToStageSelectの初期化
    _BackToStageSelect = { false,
        Point(winSize.width/2, winSize.height/4), Size(0, 0),
        Point(0, 200), Size(300, 200),
        2,
        Color3B::WHITE, 0,
        true,
        0, 0, 0, 0
    };

    isTouchBegan = false;
    isTouchMoved = false;
    isTouchEnded = false;

    timeTouchCount = 0;
    timeCount = 0;

    isInit = false;

    hutonTrigger1 = false;
    hutonTrigger2 = false;

    result_bg_Opacity = 0;
    isTouchReStart = false;
    isTouchBackToStageSelect = false;
}


bool Stage04::init(){

    if ( !Layer::init() )
    {
        return false;
    }

    // タッチ機能の追加
    auto listener = EventListenerTouchOneByOne::create();
    listener->setEnabled(true);
    listener->onTouchBegan = CC_CALLBACK_2(Stage04::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Stage04::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Stage04::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // updateを呼ぶ
    this->scheduleUpdate();

    //--------(:3=---------//
    _Player.point = Point(_Player.size.width/2, winSize.height/2);
    player_image = Sprite::create("stage04_image.png");
    player_image->setPosition(_Player.point);
    player_image->setTextureRect(Rect(_Player.tx_point.x, _Player.tx_point.y,
                                      _Player.tx_size.width, _Player.tx_size.height));
    player_image->setColor(_Player.col);
    this->addChild(player_image);

    //---------布団---------//
    for (int i = 0; i < HUTON_MAX; i++){
        _Huton[0].point = Point(winSize.width/4*3, winSize.height/2);

        huton_image[i] = Sprite::create("stage04_image.png");
        huton_image[i]->setPosition(_Huton[i].point);
        huton_image[i]->setTextureRect(Rect(_Huton[i].tx_point.x, _Huton[i].tx_point.y,
                                            _Huton[i].tx_size.width, _Huton[i].tx_size.height));
        huton_image[i]->setColor(_Huton[i].col);
        this->addChild(huton_image[i]);
    }


    // SCOREの描画
    // 描画位置の決定
    _Score[0].point = Point(winSize.width/2 - _Score[0].size.width, winSize.height/4*3);
    _Score[2].point = Point(winSize.width/2 + _Score[0].size.width, winSize.height/4*3);
    for (int i = 0; i < NUM_MAX; i++){
        score_image[i] = Sprite::create("number_image.png");
        score_image[i]->setPosition(_Score[i].point);
        score_image[i]->setTextureRect(Rect(_Score[i].tx_point.x, _Score[i].tx_point.y,
                                            _Score[i].tx_size.width, _Score[i].tx_size.height));
        score_image[i]->setScale(_Score[i].scale);
        score_image[i]->setColor(_Score[i].col);
        this->addChild(score_image[i]);
    }

    // Cloudの描画
    // 画像の切り取りを指定
    _Cloud[0].tx_point = Point(0, 400);
    _Cloud[1].tx_point = Point(400, 400);
    _Cloud[2].tx_point = Point(0, 700);
    _Cloud[3].tx_point = Point(400, 700);
    // 位置の決定
    _Cloud[0].point = Point(winSize.width/5, winSize.height/4);
    _Cloud[1].point = Point(winSize.width/5*2, winSize.height/3);
    _Cloud[2].point = Point(winSize.width/4*3, winSize.height/4*3);
    _Cloud[3].point = Point(winSize.width, winSize.height/2);
    for (int i = 0; i < CLOUD_MAX; i++){
        cloud_image[i] = Sprite::create("stage04_image.png");
        cloud_image[i]->setPosition(_Cloud[i].point);
        cloud_image[i]->setTextureRect(Rect(_Cloud[i].tx_point.x, _Cloud[i].tx_point.y,
                                            _Cloud[i].tx_size.width, _Cloud[i].tx_size.height));
        cloud_image[i]->setColor(_Cloud[i].col);
        cloud_image[i]->setScale(_Cloud[i].scale);
        this->addChild(cloud_image[i]);
    }

    
    // Result時に被せる背景
    // 背景色を指定
    result_bg = LayerColor::create(Color4B::BLACK, _Result_bg.size.width, _Result_bg.size.height);
    result_bg->setOpacity(0);             //--透明度--//
    result_bg->setVisible(_Result_bg.visi); //--非表示--//
    this->addChild(result_bg);
    
    // ReStartの描画
    // 実際に描画している画像サイズを取得
    _ReStart.size = Size(_ReStart.tx_size.width * _ReStart.scale,
                         _ReStart.tx_size.height * _ReStart.scale);
    restart_image = Sprite::create("result_image.png");
    restart_image->setPosition(_ReStart.point);
    restart_image->setTextureRect(Rect(_ReStart.tx_point.x, _ReStart.tx_point.y,
                                       _ReStart.tx_size.width, _ReStart.tx_size.height));
    restart_image->setScale(_ReStart.scale);
    restart_image->setVisible(_ReStart.visi);
    this->addChild(restart_image);

    // BackToStageSelectの描画
    // 実際に描画している画像のサイズを取得
    _BackToStageSelect.size = Size(_BackToStageSelect.tx_size.width * _BackToStageSelect.scale,
                                   _BackToStageSelect.tx_size.height * _BackToStageSelect.scale);
    backtoSS_image = Sprite::create("result_image.png");
    backtoSS_image->setPosition(_BackToStageSelect.point);
    backtoSS_image->setTextureRect(Rect(_BackToStageSelect.tx_point.x, _BackToStageSelect.tx_point.y,
                                        _BackToStageSelect.tx_size.width, _BackToStageSelect.tx_size.height));
    backtoSS_image->setScale(_BackToStageSelect.scale);
    backtoSS_image->setVisible(_BackToStageSelect.visi);
    this->addChild(backtoSS_image);

    return true;
}

bool Stage04::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    auto location = touch->getLocation();
    log("location.x = %f, location.y = %f", location.x, location.y);

    if (_Player.active){
        // 画面左半分内のみの移動制限
        if (location.x < winSize.width/2){
            _Player.point.x = location.x;
            firstTouchPoint = location;
        }

        isTouchBegan = true;
    }

    // リザルト画面でどのボタンをタッチしているかの判定
    if (point_to_rect(location.x, location.y,
                      _ReStart.point.x - _ReStart.size.width/2,
                      _ReStart.point.y - _ReStart.size.height/2,
                      _ReStart.size.width, _ReStart.size.height)){
        isTouchReStart = true;
    } else{
        isTouchReStart = false;
    }
    if (point_to_rect(location.x, location.y,
                      _BackToStageSelect.point.x - _BackToStageSelect.size.width/2,
                      _BackToStageSelect.point.y - _BackToStageSelect.size.height/2,
                      _BackToStageSelect.size.width, _BackToStageSelect.size.height)){
        isTouchBackToStageSelect = true;
    } else{
        isTouchBackToStageSelect = false;
    }

    return true;
}

void Stage04::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
    auto location = touch->getLocation();

    if (_Player.active){
        // 画面左半分内のみの移動制限
        if (location.x < winSize.width / 2){
            _Player.point.x = location.x;
        }

        isTouchMoved = true;
    }

    // リザルト画面でどのボタンをタッチしているかの判定
    if (point_to_rect(location.x, location.y,
        _ReStart.point.x - _ReStart.size.width / 2,
        _ReStart.point.y - _ReStart.size.height / 2,
        _ReStart.size.width, _ReStart.size.height)){
        isTouchReStart = true;
    }
    else{
        isTouchReStart = false;
    }
    if (point_to_rect(location.x, location.y,
        _BackToStageSelect.point.x - _BackToStageSelect.size.width / 2,
        _BackToStageSelect.point.y - _BackToStageSelect.size.height / 2,
        _BackToStageSelect.size.width, _BackToStageSelect.size.height)){
        isTouchBackToStageSelect = true;
    }
    else{
        isTouchBackToStageSelect = false;
    }
}

void Stage04::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
    auto location = touch->getLocation();

    if (_Player.active){
        if (location.x >= winSize.width / 2){
            lastTouchPoint = location;
            isTouchEnded = true;
            _Player.active = false;
        } else {
            timeTouchCount = 0;
            isTouchMoved = false;
        }
    }

    isTouchBackToStageSelect = false;
    isTouchReStart = false;


    // "もう一度"をタップしていたらリスタート
    if (point_to_rect(location.x, location.y,
        _ReStart.point.x - _ReStart.size.width / 2,
        _ReStart.point.y - _ReStart.size.height / 2,
        _ReStart.size.width, _ReStart.size.height)){
        
        //////////////////////////////////////////////////////////////////////////////////
        // シーン移動
        Director::getInstance()->replaceScene(Stage04::createScene());
    }

    // "もどる"をタップしていたらステージ選択へ移動
    if (point_to_rect(location.x, location.y,
        _BackToStageSelect.point.x - _BackToStageSelect.size.width / 2,
        _BackToStageSelect.point.y - _BackToStageSelect.size.height / 2,
        _BackToStageSelect.size.width, _BackToStageSelect.size.height)){
        
        //////////////////////////////////////////////////////////////////////////////////
        // シーン移動
        Director::getInstance()->replaceScene(StageSelect::createScene());
    }

}

void Stage04::TouchingTimeCount(){
    if (!isTouchEnded){
        if (isTouchMoved){
            timeTouchCount += 0.2;
            log("timeTouchCount = %f", timeTouchCount);
        }
    }
}

void Stage04::DistTouchBeganToEnded(){
    if (isTouchEnded && !isInit){
        distTouchBeganToEnded = (lastTouchPoint.x - firstTouchPoint.x) > 800 ?
            800 : lastTouchPoint.x - firstTouchPoint.x;
        log("distTouchBeganToEnded = %f", distTouchBeganToEnded);
    }
}

void Stage04::HutonScene(){
    // 指を離したときに初めの布団をactiveにする
    if (isTouchEnded && !isInit){
        _Huton[0].active = true;
        isInit = true;
    }


    // Hutonのスピード
    for (int i = 0; i < HUTON_MAX; i++){
        _Huton[i].speed = (distTouchBeganToEnded/3 - timeTouchCount*40) > 0 ?
            distTouchBeganToEnded/3 - timeTouchCount * 40 : 0;
    }
    if (distTouchBeganToEnded > 0){
        distTouchBeganToEnded-=0.6;
    }
    //timeCount++;
    log("distTouchBeganToEnded = %f", distTouchBeganToEnded);

    for (int i = 0; i < HUTON_MAX; i++){
        if (_Huton[i].active){
            _Huton[i].point.x -= _Huton[i].speed;
            
            if (_Huton[i].point.x <= _Player.point.x){
                _Huton[i].point.x = _Player.point.x;

                _Huton[i].tx_size = Size(500, 200); // 切り取り位置の変更
                _Huton[i].point.y += 6;             // 画像の移動
                _Huton[i].visi -= 6;                // 透過度の変更

                // 布団が消える処理
                if (_Huton[i].visi <= 0){
                    _Huton[i].point = Point(winSize.width + 150, winSize.height/2);
                    _Huton[i].tx_size = Point(300, 200);
                    _Huton[i].visi = 255;
                    _Huton[i].active = false;
                }
                ///////////////////////////////////////////
                // よろしくない処理をしているので
                // 時間ができたらリファクタリングすること
                if (_Huton[i].visi == 249){
                    // スコアを加算
                    play_score += 1;
                }
            }
        }
    }
}

// 布団を流すトリガー
void Stage04::HutonTrigger(){
    for (int i = 0; i < HUTON_MAX; i++){
        if (_Huton[i].active){
            if (_Huton[i].point.x < winSize.width / 4 * 3){
                hutonTrigger1 = true;
            }
            else{
                hutonTrigger1 = false;
            }
        }
        if (_Huton[i].point.x > winSize.width / 4 * 3){
            if (!_Huton[i].active){
                hutonTrigger2 = true;
            }
            else{
                hutonTrigger2 = false;
            }
        }
        if (hutonTrigger1 && hutonTrigger2){
            if (!_Huton[i].active){
                _Huton[i].active = true;
                hutonTrigger1 = false;
                hutonTrigger2 = false;
                break;
            }
        }
    }
}

void Stage04::PlayerScene(){
    if (!_Player.active){
        _Player.tx_point = Point(0, 0);
        _Player.tx_size = Size(600, 200);
    }
}

void Stage04::HutonUpdate(){
    for (int i = 0; i < HUTON_MAX; i++){
        huton_image[i]->setPosition(_Huton[i].point);
        huton_image[i]->setTextureRect(Rect(_Huton[i].tx_point.x, _Huton[i].tx_point.y,
                                            _Huton[i].tx_size.width, _Huton[i].tx_size.height));
        huton_image[i]->setOpacity(_Huton[i].visi); // 透過度
        huton_image[i]->setColor(_Huton[i].col);
    }
}

void Stage04::ScoreSetTextureRect(){
    _Score[0].tx_point = Point(play_score/100 * 100, 0);
    _Score[1].tx_point = Point(play_score/10%10 * 100, 0);
    _Score[2].tx_point = Point(play_score%10 * 100, 0);
    log("play_score = %f", play_score);
    // 変更したステータスを反映させる
    for (int i = 0; i < NUM_MAX; i++){
        score_image[i]->setTextureRect(Rect(_Score[i].tx_point.x, _Score[i].tx_point.y,
                                            _Score[i].tx_size.width, _Score[i].tx_size.height));
    }
}

void Stage04::CloudMove(){
    
    for (int i = 0; i < CLOUD_MAX; i++){
        _Cloud[i].speed = (distTouchBeganToEnded / 6 - timeTouchCount*20) > 0 ?
            distTouchBeganToEnded / 6 - timeTouchCount*20 : 0;
        _Cloud[i].point.x -= _Cloud[i].speed;

        if (_Cloud[i].point.x <= 0 - _Cloud[i].size.width/2){
            _Cloud[i].point.x = winSize.width + _Cloud[i].size.width/2;
        }
    }

    // 変更したステータスを反映させる
    for (int i = 0; i < CLOUD_MAX; i++){
        cloud_image[i]->setPosition(_Cloud[i].point);
    }
}

void Stage04::ResultTrigger(){
    if ((!_Player.active) && (_Cloud[0].speed == 0)){
        // 半透明のレイヤーをかける
        _Result_bg.active = true;

        // 背景の透過度を130になるまで回す
        if (result_bg_Opacity <= 130){
            result_bg_Opacity++;
            result_bg->setOpacity(result_bg_Opacity);
        }

        // 背景の透過度が130になったらそれぞれをtrue
        if (result_bg_Opacity == 130){
            _ReStart.active = true;
            _BackToStageSelect.active = true;
        }
    }
}

void Stage04::ResultSetVisible(){
    if (_Result_bg.active){
        _Result_bg.visi = 1; //表示・true
    }
    // 変更したステータスを反映させる
    result_bg->setVisible(_Result_bg.visi);
}

void Stage04::ReStartSetVisible(){
    if (_ReStart.active){
        _ReStart.visi = 1; //表示・true
    }
    // 変更したステータスを反映させる
    restart_image->setVisible(_ReStart.visi);
}

void Stage04::ReStartSetColor(){
    if (isTouchReStart){
        _ReStart.col = Color3B::BLUE;
    } else{
        _ReStart.col = Color3B::WHITE;
    }
    // 変更したステータスを反映させる
    restart_image->setColor(_ReStart.col);
}

void Stage04::BackToStageSelectSetVisible(){
    if (_BackToStageSelect.active){
        _BackToStageSelect.visi = 1; //表示・true
    }
    // 変更したステータスを反映させる
    backtoSS_image->setVisible(_BackToStageSelect.visi);
}

void Stage04::BackToStageSelectSetColor(){
    if (isTouchBackToStageSelect){
        _BackToStageSelect.col = Color3B::BLUE;
    } else{
        _BackToStageSelect.col = Color3B::WHITE;
    }
    // 変更したステータスを反映させる
    backtoSS_image->setColor(_BackToStageSelect.col);
}

void Stage04::PlayerUpdate(){
    player_image->setPosition(_Player.point);
    player_image->setTextureRect(Rect(_Player.tx_point.x, _Player.tx_point.y,
                                      _Player.tx_size.width, _Player.tx_size.height));
}

void Stage04::update(float delta){
    TouchingTimeCount();
    DistTouchBeganToEnded();

    PlayerScene();
    PlayerUpdate();

    HutonScene();
    HutonTrigger();
    HutonUpdate();

    ScoreSetTextureRect();
    CloudMove();

    ResultTrigger();
    ResultSetVisible();
    ReStartSetVisible();
    BackToStageSelectSetVisible();

    ReStartSetColor();
    BackToStageSelectSetColor();
}