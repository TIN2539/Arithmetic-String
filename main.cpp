#include <iostream>
#include "Stack.h"
#include "Arifmetic string.h"
using namespace std;

void AllinOne(char userstr[])
{
	do
	{
		cout << "Enter the expression: ";

		cin.getline(userstr, 200);

		Arifmetic string(userstr);

		if (!string.CheckforCorrect())
		{
			cout << "Error!" << endl;
			continue;
		}

		if (!string.WorkwithStack())
		{
			cout << "Error!" << endl;
			continue;
		}

		string.Result();
	} while (1);
}
int main()
{
	char userstr[200] = {};
	AllinOne(userstr);
}