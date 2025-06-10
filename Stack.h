//****************************************************************************************************
//
//         File:                        Stack.h
//
//         Student:                     Allison Coil
//
//         Assignment:                  Program  # 6
//
//         Course Name:                 Data Structures   I
//
//         Course Number:               COSC 3050 - 01
//
//         Due:                         Mar 6, 2021
//
//
//         This class defines a stack data structure using an array.
//
//
//****************************************************************************************************

#ifndef STACK_H
#define STACK_H

//****************************************************************************************************

template <typename TYPE>
class Stack
{
private:
	TYPE* stack;
	int top;
	int capacity;

public:
	Stack(int cap = 40);
	~Stack();
	bool push(const TYPE& dataIn);
	bool pop(TYPE& dataOut);
	bool peek(TYPE& dataOut) const;
	int getNumValues() const;
	bool isEmpty() const;
	bool isFull() const;
};

//****************************************************************************************************

template <typename TYPE>
Stack <TYPE> ::Stack(int cap)
{
	capacity = cap;
	top = -1;
	stack = new TYPE[capacity];
}

//****************************************************************************************************

template <typename TYPE>
Stack <TYPE> :: ~Stack()
{
	delete[] stack;
	top = -1;
	capacity = 0;
	stack = nullptr;
}

//****************************************************************************************************

template <typename TYPE>
bool Stack <TYPE> ::push(const TYPE& dataIn)
{
	bool success = false;

	if ((top + 1) < capacity)
	{
		top++;
		stack[top] = dataIn;
		success = true;
	}

	return success;
}

//****************************************************************************************************

template <typename TYPE>
bool Stack <TYPE> ::pop(TYPE& dataOut)
{
	bool success = false;

	if (top > -1)
	{
		dataOut = stack[top];
		top--;
		success = true;
	}

	return success;
}

//****************************************************************************************************

template <typename TYPE>
bool Stack <TYPE> ::peek(TYPE& dataOut) const
{
	bool success = false;

	if (top > -1)
	{
		dataOut = stack[top];
		success = true;
	}

	return success;
}

//****************************************************************************************************

template <typename TYPE>
int Stack <TYPE> ::getNumValues() const
{
	return (top + 1);
}

//****************************************************************************************************

template <typename TYPE>
bool Stack <TYPE> ::isEmpty() const
{
	return (top < 0);
}

//****************************************************************************************************

template <typename TYPE>
bool Stack <TYPE> ::isFull() const
{
	return ((top + 1) == capacity);
}

//****************************************************************************************************

#endif 