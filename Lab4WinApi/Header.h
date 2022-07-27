#pragma once
using namespace std;
#include <vector>
#include <string>
#include <windows.h>

int multiplyVectors(vector<int> vecA, vector<int> vecB);
vector<int> addVectors(const vector<int>& vecA, const vector<int>& vecB);
vector<vector<int>> devideMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB);
void printMatrix(const vector<vector<int>>& matrix);
vector<vector<int>> multiplyNumberMatrix(vector<vector<int>>& matrix, int number);
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB);
int Min(const vector<int>& vector);
vector<vector<int>> inputMatrix(int n);
vector<int> inputVector(int n);
void fillingMatrix(vector<vector<int>>& matrix, string matrixName);
void fillingVector(vector<int>& vec, string vecName);
vector<int> multiplyVectorMatrix(const vector<vector<int>>& matrix, const vector<int>& vec);
void sortVector(vector<int>& vec);
void printVector(const vector<int>& vec);

DWORD WINAPI F1(LPVOID lpParameter);
DWORD WINAPI F2(LPVOID lpParameter);
DWORD WINAPI F3(LPVOID lpParameter);

