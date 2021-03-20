#include "exStack.h"

namespace exStack{

stack::stack(int size)
{
	arr = new Item[size];
	capacity = size;
	top = -1;
}


stack::~stack()
{
	delete[] arr;
}


void stack::push(Item x)
{
	if (isFull())
	{
		cout << "OverFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	
	arr[++top] = x;
}


Item stack::pop()
{

	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	

	
	return arr[top--];
}


Item stack::peek()
{
	if (!isEmpty())
		return arr[top];
	else
		exit(EXIT_FAILURE);
}


int stack::size()
{
	return top + 1;
}


bool stack::isEmpty()
{
	return top == -1;  
}


bool stack::isFull()
{
	return top == capacity - 1;    
}
}
