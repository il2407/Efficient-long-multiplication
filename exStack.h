
#include <iostream>
#include <cstdlib>
using namespace std;


#define SIZE 10
#define START 1
#define AFTER_FIRST 2
#define AFTER_SECOND 3
#define AFTER_THIRD 4

struct Item 
{ 
	int n;
	string x;
	string y;
	int len;
	int line;
	string a, b, c, d, ac, bd;
	string ex01, ex02;
	string result;
};


namespace exStack {
		
		class stack
		{
				Item *arr;
				int top;
				int capacity;

			public:
				stack(int size = SIZE);     
				~stack();                  

				void push(Item);
				Item pop();
				Item peek();

				int size();
				bool isEmpty();
				bool isFull();
		};
}
