#pragma once
#include <iostream>
#include <Windows.h>

class F1 {
private:
    Vector* result;
    int N;
    HANDLE mutex;
public:
    F1(int N, HANDLE mutex);
    Vector* getResult();
    static DWORD WINAPI startThread(void* param);
    DWORD run();
};
