#include "Arifmetic string.h"
#include <iostream>
#include "Stack.h"
using namespace std;

Arifmetic::Arifmetic() :
	str(0), length(0)
{
}

Arifmetic::Arifmetic(char* user_str)
{
	length = strlen(user_str);
	str = new char[length];
	memcpy(str, user_str, sizeof(char)*length);
	DeleteSpace();
}

Arifmetic::~Arifmetic()
{
	length = 0;
}

int Arifmetic::GetLength()
{
	return length;
}

void Arifmetic::DeleteSpace()
{
	for (int i = 0; i < length; i++)
	{
		if (str[i] == ' ')
		{
			memmove(&str[i], &str[i + 1], sizeof(char) * (length - i));
			length--;
		}
	}
	str[length] = '\0';
}

bool Arifmetic::CheckforCorrect()
{
	//проверка первого символа строки
	if (str[0] == '/' || str[0] == '*' || str[0] == '^' || str[0] == ')')
	{
		return false;
	}
	for (int i = 0; i < length; ++i)
	{
		if (str[i] < '(' || str[i] > '9' && str[i] != '^')
		{
			return false;
		}
		if (str[i] == ',')
		{
			str[i] = '.';
		}
	}
	return true;
}

void Arifmetic::NegativeNumber(int i, Stack<char>& operators, Stack<double>& operands)
{
		operands.Push(0);
		operators.Push(str[i]);
}

int Arifmetic::GetPriority(const char& oper)
{
	switch (oper)
	{
	case '^':
		return 4;
	case '*':
		return 3;
	case '/':
		return 3;
	case '-':
		return 2;
	case '+':
		return 2;
	case '(':
		return 1;
	case ')':
		return 0;
	default:
		return 10;
	}
}

void Arifmetic::Calculate(Stack<char>& operators, Stack<double>& operands)
{
	double one = operands.Pop();
	double two = operands.Pop();
	double result;
	switch (operators.Pop())
	{
	case '+':
		result = two + one;
		break;
	case '-':
		result = two - one;
		break;
	case '*':
		result = two * one;
		break;
	case '/':
		result = two / one;
		break;
	case '^':
		result = 1;
		if (one != 0)
		{
			for (int j = 0; j < one; j++)
				result *= two;
		}
		break;
	}
	operands.Push(result);
}


bool Arifmetic::NumberforExponentiation(int& i, Stack<char>& operators, Stack<double>& operands)
{
	double value = atof(&str[i]);
	while (str[i + 1] != '\0' && str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != '/' && str[i + 1] != '*' && str[i + 1] != ')')
	{
		i++;
		if (str[i] == '.' || str[i] == ',')
		{
			return false;
		}
	}
	operands.Push(value);
	return true;
}

bool Arifmetic::Divisionby0(Stack<char>& operators, Stack<double>& operands)
{
	if (operands.Peek() == 0 && operators.Peek() == '/')
	{
		return false;
	}
	if (operators.Peek() != '(')
	{
		Calculate(operators, operands);
		return true;
	}
	return false;
}

void Arifmetic::DeterminationNumber(int& i, Stack<char>& operators, Stack<double>& operands)
{
	double value = atof(&str[i]);
	while (str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != '/' && str[i + 1] != '*' && str[i + 1] && str[i + 1] != '^' && str[i + 1] != ')' && str[i + 1] != '\0')
	{
		i++;
		if (str[i] == '.')
		{
			do
			{
				i++;
			} while (str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != '/' && str[i + 1] != '*' && str[i + 1] != '^' && str[i + 1] != ')' && str[i + 1] != '\0');
		}
	}
	operands.Push(value);
}

char& Arifmetic::operator[](const int index)
{
	return str[index];
}

bool Arifmetic::Whiledontmeet(Stack<char>& operators, Stack<double>& operands)
{
	while (operators.Peek() != '(' && operators.GetSize() != 0)
	{
		Divisionby0(operators, operands);
	}
	//если '(' нету в стеке
	if (operators.GetSize() == 0)
	{
		return false;
	}
	else
	{
		operators.Pop();
	}
	return true;
}

bool Arifmetic::WorkwithStack()
{
	for (int i = 0; i < length; i++)
	{
		if (str[i] == '-' && i == 0 || str[i] == '-' && str[i - 1] == '(')
		{
			NegativeNumber(i, operators, operands);
			continue;
		}
		if (str[i] == '^')
		{
			operators.Push(str[i]);
			i++;
			if (!NumberforExponentiation(i, operators, operands))
			{
				return false;
			}
			Calculate(operators, operands);
		}

		else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' && str[i] != '\0')
		{
			if (operands.GetSize() > 1 && GetPriority(operators.Peek()) >= GetPriority(str[i]))
			{
				if (!Divisionby0(operators, operands))
				{
					return false;
				}
				else
				{
					i--;
					continue;
				}
			}
			operators.Push(str[i]);
			continue;
		}

		else if (str[i] == '(')
		{
			operators.Push(str[i]);
			continue;
		}

		else if (str[i] != '\0' && str[i] != '+' && str[i] != '-' && str[i] != '/' && str[i] != '*' && str[i] != '^' && str[i] != ')' && str[i] != '(')
		{
			DeterminationNumber(i, operators, operands);
		}

		//вытаскиваем значения пока не встретим '('
		while (str[i + 1] == ')')
		{
			if (!Whiledontmeet(operators, operands))
			{
				return false;
			}
			i++;
		}
	}
	if (!CheckLastOperation())
	{
		return false;
	}
	return true;
}

void Arifmetic::Result()
{
	if (operators.GetSize() > 0)
	{
		cout << "Error!" << endl;
	}
	else if (operators.GetSize() == 0 && operands.GetSize() == 1)
	{
		cout << "Result = " << operands.Pop() << endl;
	}
}

bool Arifmetic::CheckLastOperation()
{
	while (operands.GetSize() > 1)
	{
		if (!Divisionby0(operators, operands))
		{
			return false;
		}
	}
	return true;
}