// Singletonについてあれこれしてみる.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include "Singleton.h"

int _tmain(int argc, _TCHAR* argv[])
{
    cout << "Start." << endl;

    Singleton *obj1 = &Singleton::getInstance();
    // インスタンスの生成（初回
    Singleton *obj2 = &Singleton::getInstance();
    // 二回目なので新しいインスタンスは生成されない
    if (obj1 == obj2){
        cout << "obj1とobj2は同じインスタンスです" << endl;
    }

    if (&obj1->x == &obj2->x){
        cout << "obj1とobj2のXは同じインスタンスです" << endl;
    }

	return 0;
}

