//****************************************************************************************************
//
//         File:                        RPN.cpp
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
//         This program uses the STack class to evaluate RPN expressions provided by a file.
//
//
//****************************************************************************************************

#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

//****************************************************************************************************

#include "Stack.h"

//****************************************************************************************************

void outputToken ( char token [], ofstream & resultsFile );
void processNumber ( char token [], ofstream & resultsFile, Stack <int> & expressionStack );
bool processOperator ( char opr, ofstream & resultsFile, Stack <int> & expressionStack );
void displayResult ( bool valid, ofstream & resultsFile, Stack <int> & expressionStack );
void resetFlagStack ( bool & valid, Stack <int> & expressionStack);

//****************************************************************************************************

int main ()
{
	ifstream expFile ("expressions.txt");
	ofstream resFile ("results.txt");
	Stack <int> expStack;
	char token [5];
	bool isValid = true;

	while ( expFile >> token )
	{
		outputToken ( token, resFile );

		if ( token [0] == ';' )
		{
			displayResult ( isValid, resFile, expStack );
			resetFlagStack ( isValid, expStack );
		}
		else if ( (isValid) && ( isdigit ( token [0] ) ) )
		{
			processNumber ( token, resFile, expStack );
		}
		else if (isValid)
		{
			isValid = processOperator ( token [0], resFile, expStack );
		}

	}

	expFile.close ();
	resFile.close ();

	return 0;
}

//****************************************************************************************************

void outputToken ( char token [], ofstream & resultsFile )
{
	resultsFile << endl << "( Token:  " << token << " ) \t\t"; 

	if ( token [0] != ';' )
		cout << token << " ";
}

//****************************************************************************************************

void processNumber ( char token [], ofstream & resultsFile, Stack <int> & expressionStack )
{
	int iVal;
	iVal = atoi (token);
	expressionStack.push (iVal);
	resultsFile << "Push " << iVal;
}

//****************************************************************************************************

bool processOperator ( char opr, ofstream & resultsFile, Stack <int> & expressionStack )
{
	bool valid = false;
	int op1,
		op2,
		result;

	if ( expressionStack.getNumValues () >= 2 )
	{
		expressionStack.pop (op2);
		expressionStack.pop (op1);

		switch (opr)
		{
			case '+' :
				result = op1 + op2;
				break;
			case '-' :
				result = op1 - op2;
				break;
			case '*' :
				result = op1 * op2;
				break;
			case '/' :
				result = op1 / op2;
				break;
			case '%' :
				result = op1 % op2;
		}

		expressionStack.push (result);
		resultsFile << "Pop " << op2 << "\t\t" << "Pop " << op1 << "\t\t" << "Push " << result;
		valid = true;
	}

	return valid;
}

//****************************************************************************************************

void displayResult ( bool valid, ofstream & resultsFile, Stack <int> & expressionStack )
{
	int result;

	if (expressionStack.getNumValues() > 1)
	{
		cout << "\tinvalid\n\n";
		resultsFile << "\n\t\tInvalid RPN expression -- too many operands\n\n\n";
	}
	else if (!valid)
	{
		cout << "\tinvalid\n\n";
		resultsFile << "\n\t\tInvalid RPN expression -- not enough operands\n\n\n";
	}
	else
	{
		expressionStack.pop (result);
		cout << "= " << result << endl << endl;
		resultsFile << "Pop " << result << endl << "\t\tValid: result = " << result << "\n\n\n";
	}
}

//****************************************************************************************************

void resetFlagStack ( bool & valid, Stack <int> & expressionStack )
{
	int value;
	while ( expressionStack.pop (value) );

	valid = true;
}

//****************************************************************************************************

/*
2 4 * 5 + = 13

13 5 % 5 + = 8

15 1 + 2 / 1 - = 7

15 + 1 + 2 / 1 -        invalid

3 4 + 15 10 - * = 35

3 4 + 6 15 10 - *       invalid

2 13 + 14 6 - - 5 * 4 + = 39

35 6 4 2 2 / + * - = 5

3 4 + 1 2 - * 4 2 / 3 - + = -8

3 14 1 2 4 2 3 + % * + - + = 8
*/