#pragma once
#include "Stack.h"

class Arifmetic
{
private:
	Stack<char> operators;
	Stack<double> operands;
	char* str;
	int length;
public:
	Arifmetic();
	Arifmetic(char*);
	~Arifmetic();
	int GetLength();
	int GetPriority(const char&);
	void DeleteSpace();
	bool CheckforCorrect();
	void NegativeNumber(int, Stack<char>&, Stack<double>&);
	char& operator[](const int index);
	void Calculate(Stack<char>&, Stack<double>&);
	bool NumberforExponentiation(int&, Stack<char>&, Stack<double>&);
	bool Divisionby0(Stack<char>&, Stack<double>&);
	void DeterminationNumber(int&, Stack<char>&, Stack<double>&);
	bool Whiledontmeet(Stack<char>&, Stack<double>&);
	bool WorkwithStack();
	void Result();
	bool CheckLastOperation();
};