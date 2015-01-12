#include "stdafx.h"
#include "Singleton.h"

#include <iostream>
using namespace std;


Singleton::Singleton(){
    cout << "インスタンスが生成されました" << endl;
    x = 0;
}

Singleton &Singleton::getInstance(){
    // 初回呼び出しのみインスタンスの生成
    static Singleton singleton;
    return singleton;
}