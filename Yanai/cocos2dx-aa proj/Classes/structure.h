
#pragma once

//
//  構造体の置場
//

#include "cocos2d.h"

struct _Object{
    bool active;             // 生きているかどうか

    cocos2d::Point point;    // 位置
    cocos2d::Size  size;     // サイズ
    cocos2d::Point tx_point; // 画像切り取り位置
    cocos2d::Size  tx_size;  // 画像切り取りサイズ

    float scale;             // 拡大比率

    cocos2d::Color3B col;
    int   visi;              // 透過度(0~255)"0"で透明

    bool  right;             // 右を向いているかどうか
    
    float g, vy;             // 重力、加速度

    float angle;             // モーションなど

    float speed;
};
