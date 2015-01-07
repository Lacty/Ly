
#pragma once

//
//  �\���̂̒u��
//

#include "cocos2d.h"

struct _Object{
    bool active;             // �����Ă��邩�ǂ���

    cocos2d::Point point;    // �ʒu
    cocos2d::Size  size;     // �T�C�Y
    cocos2d::Point tx_point; // �摜�؂���ʒu
    cocos2d::Size  tx_size;  // �摜�؂���T�C�Y

    float scale;             // �g��䗦

    cocos2d::Color3B col;
    int   visi;              // ���ߓx(0~255)"0"�œ���

    bool  right;             // �E�������Ă��邩�ǂ���
    
    float g, vy;             // �d�́A�����x

    float angle;             // ���[�V�����Ȃ�

    float speed;
};
