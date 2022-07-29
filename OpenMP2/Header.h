#pragma once
using namespace std;
#include <vector>
#include <string>
#include <windows.h>
vector<int> addVectors(const vector<int>& vecA, const vector<int>& vecB);
vector<vector<int>> devideMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB);
void printMatrix(const vector<vector<int>>& matrix);
vector<vector<int>> multiplyNumberMatrix(vector<vector<int>>& matrix, int number);
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB);
int minVectorElement(const vector<int>& vector);
vector<vector<int>> getRandomMatrix(int n);
vector<int> getRandomVector(int n);
void fillingMatrix(vector<vector<int>>& matrix, string matrixName);
void fillingVector(vector<int>& vec, string vecName);
vector<int> multiplyVectorMatrix(const vector<vector<int>>& matrix, const vector<int>& vec);
void sortVector(vector<int>& vec);
void fillMatrixWithValue(vector<vector<int>>& matrix, int number);
void printVector(const vector<int>& vec);

void F1();
void F2();
void F3();