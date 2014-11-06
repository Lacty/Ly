#pragma once

#include "lib/defines.hpp"
// ������͕K���ŏ���include����

//�v���C���[�T�C�Y
const int player_size_x = 50, player_size_y = 50;
//�W�����v��
const int jump_power = 20;
//�L�����̈ړ����x(�h�b�g/1�t���[��)
const int player_move_power = 5;
//�W�����v����p
static int jump = 0;
//�W�����v�����p
static float gravity = 0, jump_vy = jump_power;
//���̈ʒu
static int floor_y = 0;
//�ǔ���p
bool wall_left = 0, wall_right = 0;
//�J�����ʒu�ړ��p
static double camera_x = 0;
static double camera_y = 0;
//�L�����ʒu
const double player_x = 0;
static double player_y = 0;

//�R���X�g��`

const int MAX_MAP_Y = 12;//�z��p

const int MAX_MAP_X = 80;//�z��p

const int size_x = 50;//X�ɑ΂��Ă̑傫��

const int size_y = 50; //Y�ɑ΂��Ă̑傫��

int object_x, object_y;//�I�u�W�F�N�g�\���ʒu