#include "stdafx.h"
#include "Singleton.h"

#include <iostream>
using namespace std;


Singleton::Singleton(){
    cout << "�C���X�^���X����������܂���" << endl;
    x = 0;
}

Singleton &Singleton::getInstance(){
    // ����Ăяo���̂݃C���X�^���X�̐���
    static Singleton singleton;
    return singleton;
}