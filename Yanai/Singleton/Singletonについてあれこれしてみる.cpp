// Singleton�ɂ��Ă��ꂱ�ꂵ�Ă݂�.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include "Singleton.h"

int _tmain(int argc, _TCHAR* argv[])
{
    cout << "Start." << endl;

    Singleton *obj1 = &Singleton::getInstance();
    // �C���X�^���X�̐����i����
    Singleton *obj2 = &Singleton::getInstance();
    // ���ڂȂ̂ŐV�����C���X�^���X�͐�������Ȃ�
    if (obj1 == obj2){
        cout << "obj1��obj2�͓����C���X�^���X�ł�" << endl;
    }

    if (&obj1->x == &obj2->x){
        cout << "obj1��obj2��X�͓����C���X�^���X�ł�" << endl;
    }

	return 0;
}

