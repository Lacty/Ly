
#pragma once


class Singleton{
private:
    Singleton();

public:
    static Singleton& getInstance();

    int x;

};