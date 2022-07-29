/*
 * Функціональне програмування
 * Лабораторна робота №3 "ПОТОКИ В WinApi"
 * 1.9 MC = MIN(A) * (MA * MD)
 * 2.24 MG = SORT(MF - MH * MK)
 * 3.7 O = (P + R) * (MS * MT)
 *
 * Сайко Сабріна Анатоліївна
 * ІВ-91
 * 02.11.2021
 * */

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <windows.h>
#include  "omp.h";
#include "Header.h"







int main()
{
    cout << "Main thread started...\n";
    omp_set_num_threads(3);

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {

                F1();
            }
            #pragma omp section
            {
                F2();
            }
            #pragma omp section
            {
                F3();
            }
        }
    }

    cout << "T1, T2 & T3 are finished\n";

    // Thread handle must be closed when no longer needed

    Sleep(1000);

    cout << "Main thread finished...\n";

    return 0;
}


void F1()
{
    cout << "T1 started\n";
    int n;

    #pragma omp critical(console) 
    {
        cout << "T1 : Please enter matrix dimension(N) : \n";
        cin >> n;
        if (n <= 0) {
            cout << "negative dimension :(\n";
        }
    }
    vector<vector<int>> MA(n, vector<int>(n));
    vector<vector<int>> MD(n, vector<int>(n));
    vector<int> A(n);

    if (n > 5) {
        MA = getRandomMatrix(n);
        MD = getRandomMatrix(n);
        A = getRandomVector(n);

    }
    else {
        #pragma omp critical(console) 
        {
            fillingMatrix(MA, "MA(T1)");
            fillingMatrix(MD, "MD(T1)");
            fillingVector(A, "A(T1)");
        }
    }

    vector<vector<int>> MAMD = multiplyMatrices(MA, MD);
    int min = minVectorElement(A);
    vector<vector<int>> MC = multiplyNumberMatrix(MAMD, min);


#pragma omp critical(console) 
    {
        cout << "T1 : \n";
        printMatrix(MAMD);
    }

    cout << "T1 finished\n";
    return;
}

void F2()
{
    cout << "T2 started\n";
    int n;

    #pragma omp critical(console)
    {
        cout << "T2 : Please enter matrix dimension(N) : \n";
        cin >> n;
        if (n <= 0) {
            cout << "negative dimension :(\n";
        }
    }
    vector<vector<int>> MF(n, vector<int>(n));
    vector<vector<int>> MG(n, vector<int>(n));
    vector<vector<int>> MH(n, vector<int>(n));
    vector<vector<int>> MK(n, vector<int>(n));
    if (n > 5) {
        MF = getRandomMatrix(n);
        MH = getRandomMatrix(n);
        MK = getRandomMatrix(n);
    }
    else
    {
        #pragma omp critical(console) 
        {
            fillingMatrix(MF, "MF(T2)");
            fillingMatrix(MH, "MH(T2)");
            fillingMatrix(MK, "MK(T2)");
        }
    }

    vector<vector<int>> MHMK = multiplyMatrices(MH, MK);
    MG = devideMatrices(MF, MHMK);
    for (int i = 0; i < n; i++)
    {
        sortVector(MG[i]);
    }

#pragma omp critical(console) 
    {
        cout << "T2 : \n";
        printMatrix(MG);
    }
    // cout << ML.size() << " " << ML[0].size() << "\n";
    cout << "T2 finished\n";


    return;
}


void F3()
{
    cout << "T3 started\n";
    int n;

    #pragma omp critical(console)
    {

        cout << "T3 : Please enter matrix dimension(N) : \n";
        cin >> n;
        if (n <= 0) {
            cout << "negative dimension :(\n"; //O = (P + R) * (MS * MT)
        }
    }
    vector<int> P(n);
    vector<int> R(n);
    vector<int> O(n);
    vector<vector<int>> MS(n, vector<int>(n));
    vector<vector<int>> MT(n, vector<int>(n));
    if (n > 5) {
        MS = getRandomMatrix(n);
        MT = getRandomMatrix(n);
        R = getRandomVector(n);
        P = getRandomVector(n);

    }
    else {
        #pragma omp critical(console)
        {
            fillingMatrix(MS, "MS(T3)");
            fillingMatrix(MT, "MT(T3)");
            fillingVector(P, "P(T3)");
            fillingVector(R, "R(T3)");
        }
    }

    vector<vector<int>> MSMT = multiplyMatrices(MS, MT);
    vector<int> PR = addVectors(P, R);
    O = multiplyVectorMatrix(MSMT, PR);
#pragma omp critical(console) 
    {
        cout << "T3 : ";
        printVector(O);
    }
    cout << "T3 finished\n";

    return;
}


void printMatrix(const vector<vector<int>>& matrix) {
    #pragma omp parallel
    {
        #pragma omp for

        for (ptrdiff_t  i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
}

vector<vector<int>> multiplyNumberMatrix(vector<vector<int>>& matrix, int number) {
    int n = matrix.size();
    #pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] *= number;
            }
        }
    }
    return matrix;
}

int maxMatrixElement(const vector<vector<int>>& matrix) {
    int result = matrix[0][0];
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                if (matrix[i][j] > result) {
                    result = matrix[i][j];
                }
            }
        }
    }
    return result;
}

vector<vector<int>> getRandomMatrix(int n) {
    vector<vector<int>> result(n, vector<int>(n));
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = rand() % 100; // 0 to 99
    }
    return result;
}

vector<int> getRandomVector(int n) {
    vector<int> result(n);
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < n; ++i) {
            result[i] = rand() % 100;
        }
    }
    return result;
}

int minVectorElement(const vector<int>& vector) {
    int result = vector[0];
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < vector.size(); ++i) {

            if (vector[i] < result) {
                result = vector[i];
            }
        }
    }
    return result;
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) {
    int n = matrixA.size();
    vector<vector<int>> result(n, vector<int>(n));
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = 0;
                for (int k = 0; k < n; ++k) {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
    }
    return result;
}

void fillingMatrix(vector<vector<int>>& matrix, string matrixName) {
    cout << "Please enter elements in " << matrixName << " matrix: \n";
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                cin >> matrix[i][j];
            }
        }
    }
}

vector<int> addVectors(const vector<int>& vecA, const vector<int>& vecB) {
    vector<int> result(vecA.size());
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < vecA.size(); ++i) {
            result[i] = vecA[i] + vecB[i];
        }
    }
    return result;
}

void fillingVector(vector<int>& vec, string vecName) {
    cout << "Please enter elements in " << vecName << " vector: \n";
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < vec.size(); i++) {
            cin >> vec[i];
        }
    }
}

vector<vector<int>> devideMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) {
    int m = matrixA.size();
    int n = matrixA[0].size();
    vector<vector<int>> result(m, vector<int>(n));
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = matrixA[i][j] - matrixB[i][j];
    }
    return result;
}

vector<int> multiplyVectorMatrix(const vector<vector<int>>& matrix, const vector<int>& vec) {
    vector<int> result(matrix.size());
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                result[i] += matrix[i][j] * vec[j];
            }
        }
    }
    return result;
}

void sortVector(vector<int>& vec) {
    sort(vec.begin(), vec.end());
}

void fillMatrixWithValue(vector<vector<int>>& matrix, int number) {
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); j++) {
                matrix[i][j] = number;
            }
        }
    }
}

void printVector(const vector<int>& vec) {
#pragma omp parallel
    {
#pragma omp for
        for (ptrdiff_t i = 0; i < vec.size(); ++i) {
            cout << vec[i] << ", ";
        }
    }
    cout << "\n";
}
