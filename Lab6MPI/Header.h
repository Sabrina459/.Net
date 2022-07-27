#ifndef DATA_H
#define DATA_H

#include <stdarg.h>
#include <iostream>

typedef float* data;
namespace Header
{
    void cpy(data Dest, data Src, size_t size) {
        for (size_t i = 0; i < size; i++) {
            *(Dest + i) = *(Src + i);
        }
    }

    void printVec(int N, data V, const char* name) {
        if (*name)
            std::cout << name << ":\n";
        std::cout << "[ ";
        for (int i = 0; i < N; i++)
        {
            std::cout << V[i] << " ";
        }
        std::cout << "]" << std::endl;
    }

    void printMat(int N, int H, data M, const char* name) {
        std::cout << "\n" << name << ":\n";
        for (int i = 0; i < H; i++)
        {
            printVec(N, &M[N * i], "");
        }
        std::cout << std::endl;
    }

    void inputMats(int N, int l, ...)
    {
        va_list arr;
        va_start(arr, l);

        for (int i = 0; i < l; i++)
        {
            data M = va_arg(arr, data);
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    std::cin >> *(M + j * N + k);
                }
            }
        }
    }

    void inputVecs(int N, int l, ...)
    {
        va_list arr;
        va_start(arr, l);

        for (int i = 0; i < l; i++)
        {
            data M = va_arg(arr, data);
            for (int j = 0; j < N; j++)
            {
                std::cin >> *(M + j);
            }
        }
    }

    void fillMats(int N, float num, int l, ...)
    {
        va_list arr;
        va_start(arr, l);

        for (int i = 0; i < l; i++)
        {
            data M = va_arg(arr, data);
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    *(M + j * N + k) = num;

                }
            }
        }
    }

    void fillVecs(int N, float num, int l, ...)
    {
        va_list arr;
        va_start(arr, l);

        for (int i = 0; i < l; i++)
        {
            data M = va_arg(arr, data);
            for (int j = 0; j < N; j++)
            {
                *(M + j) = num;

            }
        }
    }

    data numDotVec(int N, float a, data B)
    {
        data C = new float[N];

        for (int i = 0; i < N; i++)
        {
            *(C + i) = a * *(B + i);
        }

        return C;
    }

    data vecDotMat(int N, data A, data MB)
    {
        data C = new float[N];

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (j == 0) *(C + i) = 0;
                *(C + i) += *(A + i) * *(MB + j * N + i);
            }
        }

        return C;
    }

    float minVec(int N, data V) {
        float a = *V;
        for (int i = 1; i < N; i++) {
            if (a > *(V + i))
                a = *(V + i);
        }

        return a;
    }

    float vecDotVec(int N, data A, data B) {
        float a = 0;
        for (int i = 0; i < N; i++) {
            a += *(A + i) * *(B + i);
        }

        return a;
    }

    data MHDotM(int N, int H, data MA, data MB) {
        data MC = new float[N * H];
        for (int i = 0; i < H; i++)
        {
            data V = vecDotMat(N, &MA[N * i], MB);
            cpy(&MC[N * i], V, N);
            delete[] V;
        }
        return MC;
    }

    data numDotMatH(int N, int H, float num, data MH) {
        data MA = new float[N * H];
        for (int i = 0; i < H; i++) {
            data V = numDotVec(N, num, &MH[N * i]);
            cpy(&MA[N * i], V, N);
            delete[] V;
        }
        return MA;
    }

    data sumMatH(int N, int H, data MH1, data MH2) {
        data MT = new float[N * H];
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < N; j++) {
                *(MT + i * N + j) = *(MH1 + i * N + j) + *(MH2 + i * N + j);
            }
        }
        return MT;
    }

    data partRes(int N, int H, float a, float d, data MOH, data MZH, data MR) {
        data M1 = Header::MHDotM(N, H, MOH, MR);
        data M2 = Header::numDotMatH(N, H, a, M1);

        data M3 = Header::numDotMatH(N, H, d, MZH);
        data MTH = Header::sumMatH(N, H, M2, M3);

        delete[] M1, M2, M3;

        return MTH;
    }
}
#endif
