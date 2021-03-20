#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include "exStack.h"
#include <fstream>   
#include <iomanip> 

#define isdigit(x) (0 <= (x) && (x) <= 9)
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

using namespace std;

//Long Multiplication Functions:

int* longMultiplicationPerDigit(int* currXArr, int currYdigit, int n, int numOfZero);
void printArray(int* numArr, int n);
int* longMultiplication(int n, int* xArr, int* yArr);
void arrInit(int* arr, int size);
void measureLongMulti(int* x, int* y, int n);
int* stringToInt(string x);

//General Karatsuba Functions:

string strSum(string a, string b);
string strSub(string str1, string str2);


//Recursive Karatsuba Functions:
string RecursionKaratsuba(string x, string y);
void measureKaratsubaRecursive(string Sx, string Sy);

//Iterative Karatsuba Functions:
string iterativeKaratsuba(string x, string y);
void measureKaratsubaIterative(string Sx, string Sy);
