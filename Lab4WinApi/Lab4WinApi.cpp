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
#include <iterator>
#include <algorithm>
#include <windows.h>
#include "Header.h"


HANDLE semaphore;



int main()
{
    cout << "Main thread started...\n";
    semaphore = CreateSemaphore(
        NULL,           // default security attributes
        1,              // initial count
        1,              // maximum count
        NULL);          // unnamed semaphore

    HANDLE T1 = CreateThread(NULL, 0, F1, NULL, 0, NULL);
    HANDLE T2 = CreateThread(NULL, 0, F2, NULL, CREATE_SUSPENDED, NULL);
    HANDLE T3 = CreateThread(NULL, 0, F3, NULL, 0, NULL);

    ResumeThread(T2);

    // Wait for thread to finish execution
    WaitForSingleObject(T1, INFINITE);
    WaitForSingleObject(T2, INFINITE);
    WaitForSingleObject(T3, INFINITE);

    cout << "T1, T2 & T3 are finished\n";

    // Thread handle must be closed when no longer needed
    CloseHandle(T1);
    CloseHandle(T2);
    CloseHandle(T3);

    Sleep(1000);


    return 0;
}


DWORD WINAPI F1(LPVOID lpParameter)
{
    cout << "T1 started\n";

    WaitForSingleObject(semaphore, INFINITE);

    cout << "T1 : Please enter matrix dimension(N) : \n";
    int n;
    cin >> n;
    if (n <= 0) {
        cout << "negative dimension :(\n";
        return 1;
    }
    vector<vector<int>> MA(n, vector<int>(n));
    vector<vector<int>> MD(n, vector<int>(n));
    vector<int> A(n);
    if (n > 5) {
        MA = inputMatrix(n);
        MD = inputMatrix(n);
        A = inputVector(n);
        
    }
    else {
        fillingMatrix(MA, "MA(T1)");
        fillingMatrix(MD, "MD(T1)");
        fillingVector(A, "A(T1)");
    }

    ReleaseSemaphore(semaphore, 1, NULL);

    vector<vector<int>> MAMD = multiplyMatrices(MA, MD);
    int min = Min(A);
    vector<vector<int>> MC = multiplyNumberMatrix(MAMD, min);
    

    WaitForSingleObject(semaphore, INFINITE);

    cout << "T1 : \n";
    printMatrix(MAMD);

    cout << "T1 finished\n";

    ReleaseSemaphore(semaphore, 1, NULL);
    return 0;
}

DWORD WINAPI F2(LPVOID lpParameter)
{
    cout << "T2 started\n";

    WaitForSingleObject(semaphore, INFINITE);

    cout << "T2 : Please enter matrix dimension(N) : \n";
    int n;
    cin >> n;
    if (n <= 0) {
        cout << "negative dimension :(\n";
        return 1;
    }

    vector<vector<int>> MF(n, vector<int>(n));
    vector<vector<int>> MG(n, vector<int>(n));
    vector<vector<int>> MH(n, vector<int>(n));
    vector<vector<int>> MK(n, vector<int>(n));
    if (n > 5) {
        MF = inputMatrix(n);
        MH = inputMatrix(n);
        MK = inputMatrix(n);
    }
    else {
        fillingMatrix(MF, "MF(T2)");
        fillingMatrix(MH, "MH(T2)");
        fillingMatrix(MK, "MK(T2)");
    }

    ReleaseSemaphore(semaphore, 1, NULL);

    vector<vector<int>> MHMK = multiplyMatrices(MH, MK);
    MG = devideMatrices(MF, MHMK);
    for (int i = 0; i < n; i++)
    {
        sortVector(MG[i]);
    }

    WaitForSingleObject(semaphore, INFINITE);

    cout << "T2 : \n";
    printMatrix(MG);
    // cout << ML.size() << " " << ML[0].size() << "\n";
    cout << "T2 finished\n";

    ReleaseSemaphore(semaphore, 1, NULL);

    return 0;
}


DWORD WINAPI F3(LPVOID lpParameter)
{
    cout << "T3 started\n";

    WaitForSingleObject(semaphore, INFINITE);


    cout << "T3 : Please enter matrix dimension(N) : \n";
    int n;
    cin >> n;
    if (n <= 0) {
        cout << "negative dimension :(\n"; 
        return 1;
    }
    vector<int> P(n);
    vector<int> R(n);
    vector<int> O(n);
    vector<vector<int>> MS(n, vector<int>(n));
    vector<vector<int>> MT(n, vector<int>(n));
    if (n > 5) {
        MS = inputMatrix(n);
        MT = inputMatrix(n);
        R = inputVector(n);
        P = inputVector(n);

    }
    else {
        fillingMatrix(MS, "MS(T3)");
        fillingMatrix(MT, "MT(T3)");
        fillingVector(P, "P(T3)");
        fillingVector(R, "R(T3)");
    }

    ReleaseSemaphore(semaphore, 1, NULL);

    vector<vector<int>> MSMT = multiplyMatrices(MS, MT);
    vector<int> PR = addVectors(P, R);
    O = multiplyVectorMatrix(MSMT, PR);

    WaitForSingleObject(semaphore, INFINITE);

    cout << "T3 : ";
    printVector(O);
    cout << "T3 finished\n";

    ReleaseSemaphore(semaphore, 1, NULL);

    return 0;
}


int multiplyVectors(vector<int> vecA, vector<int> vecB) {
    int sum = 0;
    for (size_t i = 0; i < vecA.size(); i++)
        sum += vecA[i] * vecB[i];
    return sum;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

vector<vector<int>> multiplyNumberMatrix(vector<vector<int>>& matrix, int number) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] *= number;
        }
    }
    return matrix;
}

vector<vector<int>> inputMatrix(int n) {
    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = rand() % 100; // 0 to 99
    return result;
}

vector<int> inputVector(int n) {
    vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = rand() % 100;
    }
    return result;
}

int Min(const vector<int>& vector) {
    int result = vector[0];
    for (int i = 0; i < vector.size(); ++i) {
        
        if (vector[i] < result) {
            result = vector[i];
        }
        
    }
    return result;
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) {
    int n = matrixA.size();
    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return result;
}

void fillingMatrix(vector<vector<int>>& matrix, string matrixName) {
    cout << "Please enter elements in " << matrixName << " matrix: \n";
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            cin >> matrix[i][j];
        }
    }
}

vector<int> addVectors(const vector<int>& vecA, const vector<int>& vecB) {
    vector<int> result(vecA.size());
    for (int i = 0; i < vecA.size(); ++i) {
        result[i] = vecA[i] + vecB[i];
    }
    return result;
}

void fillingVector(vector<int>& vec, string vecName) {
    cout << "Please enter elements in " << vecName << " vector: \n";
    for (int i = 0; i < vec.size(); i++) {
        cin >> vec[i];
    }
}

vector<vector<int>> devideMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) {
    int m = matrixA.size();
    int n = matrixA[0].size();
    vector<vector<int>> result(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = matrixA[i][j] - matrixB[i][j];
    return result;
}

vector<int> multiplyVectorMatrix(const vector<vector<int>>& matrix, const vector<int>& vec) {
    vector<int> result(matrix.size());
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

void sortVector(vector<int>& vec) {
    sort(vec.begin(), vec.end());
}


void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ", ";
    }
    cout << "\n";
}
