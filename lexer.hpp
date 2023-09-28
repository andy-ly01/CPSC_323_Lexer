#include<iostream>
#include<fstream>
#include <iomanip>
#include <string>
#include <string.h>

using namespace std;

ifstream fin;
ofstream outputFile;

char operators[] = "*+-=/><%";
char delimiter[] = "(){}[],:;";
char keywords[4][10] = { "while", "int", "char", "return"};
bool hasDelim = false;	//verifies if ch is a delimiter
bool hasOp = false;		//verifies if ch is an operator
bool hasChar = false;	//verifies if ch is a char
bool inString = false;
int currentIndex = 0;	// index for check isInt() and isFloat()

// bool statement that will print token and lexeme if true
bool endOperator = false;
bool endDelimiter = false;
bool endChar = false;
bool endInt = false;
bool endFloat = false;
bool endIdentifier = false;

char ch;			//reads input txt file char by char
char buffer[31];	//stores instance for input if string or literal number
int j = 0;			// index for buffer[]

bool isKeyword(char buffer[]) 
{
	for (int i = 0; i < 4; ++i)
		if (strcmp(keywords[i], buffer) == 0)
			return true;
	return false;
}

bool isOperator(char ch) 
{
	for (int i = 0; i < 10; ++i)	 //check if ch matches any elements in array operators
	{
		if (ch == operators[i])
			return true;
	}
	return false;	
}

bool isDelimiter(char ch) 
{
	for (int i = 0; i < 10; ++i) 	//check if ch matches any elements in array delimiter
	{
		if (ch == delimiter[i])
			return true;
	}
	return false;
}

bool isFloat(char buffer[]) 
{ 
	string str(buffer);
	string substr(".");

	size_t found = str.find(substr);

	if (found != string::npos) 
	{
		for (int i = 0; i < found; i++) 
		{
			if (!isdigit(buffer[i]))
				return false;
		}
		for (int i = found + 1; i < currentIndex; i++) 
		{
			if (!isdigit(buffer[i]))
				return false;
		}
		return true;
	}
	else
		return false;
}


bool isChar(char buffer[])
{
	string str(buffer);
	string substr("'");

	size_t found = str.find(substr);

	if (found != string::npos) {
		for (int i = 0; i < found; i++) 
		{
			if (!isalpha(buffer[i]))
				return false;
		}
		for (int i = found + 1; i < currentIndex; i++) 
		{
			if (!isalpha(buffer[i]))
				return false;
		}
		return true;
	}
	else
		return false;
}



bool isInt(char buffer[]) 
{
	for (int i = 0; i <= (currentIndex - 1); i++) 
	{
		if (!isdigit(buffer[i]))
			return false;
	}
	return true;
}

void print() 
{

	if (endIdentifier) 
	{
		cout << "identifier           " << buffer << endl;
		outputFile << "identifier           " << buffer << endl;
		endIdentifier = false;
	}

	if (endInt) 
	{
		cout << "number               " << buffer << endl;
		outputFile << "number               " << buffer << endl;
		endInt = false;
	}

	if (endFloat) 
	{
		cout << "literal              " << buffer << endl;
		outputFile << "literal              " << buffer << endl;
		endFloat = false;
	}

	if (endDelimiter) 
	{
		cout << "delimiter            " << ch << endl;
		outputFile << "delimiter            " << ch << endl;
		endDelimiter = false;
		hasDelim = false;
	}

	if (endChar) 
	{
		cout << "char literal         " << buffer << endl;
		outputFile << "char literal         " << buffer << endl;
		endChar = false;
		hasChar = false;
	}
	

	if (endOperator) 
	{
		cout << "operator             " << ch << endl;
		outputFile << "operator             " << ch << endl;
		endOperator = false;
		hasOp = false;
	}
}

void lexer() 
{
		if (isDelimiter(ch)) 
		{
			hasDelim = true;
			endDelimiter = true;
		}

		if (isOperator(ch)) {
			hasOp = true;
			endOperator = true;
		}

		if ((isalnum(ch) || ch == '.') && !inString)
		{
			buffer[j++] = ch;
			currentIndex++;
		}

		if(ch == '\'' ) //checks if ch is a char
		{
			buffer[j++] = ch;
			currentIndex++;
		}

		//if(ch == '\"' ) //checks if ch is a string
		//{
		//	buffer[j++] = ch;
		//	currentIndex++;
		//}
		if (ch == '\"' ) //checks if ch is a string
    	{
        	inString = !inString; // toggle the string flag
        	if(!inString) // if the flag is off, it means we've found the end of a string
        {
			buffer[j++] = ch;
            buffer[j] = '\0'; // terminate the string
            cout << "String              " << buffer << endl;
            outputFile << "String              " << buffer << endl;
            j = 0; // reset the buffer index
            return; // exit the function early
        }
    }

    if(inString) // if we're in a string, just add the character to the buffer and continue
    {
        buffer[j++] = ch;
        return;
    }
		
		

		else if ((ch == '\'' || ch == ' ' || ch == '\n' || hasDelim || hasOp || fin.eof()) && (j != 0)) 
		{
			buffer[j] = '\0';	// sets last element to null 
			j = 0;
			if (isChar(buffer))	//recognizes char but prints ' as a char needs to be fixed
			{
				endChar = true;
			}
			//else if(ch == '\"')	//needs to be fixed doesnt recognize string
			//{
			//	cout << "String              " << buffer << endl;
			//	outputFile << "String              " << buffer << endl;

			//}
			else if (isKeyword(buffer)) 
			{	
				cout << "keyword              " << buffer << endl;
				outputFile << "keyword              " << buffer << endl;
			}
			else if (isFloat(buffer))
				endFloat = true;
			else if (isInt(buffer))
				endInt = true;
			else {
				if (!isdigit(buffer[0]))
					endIdentifier = true;
			}

			currentIndex = 0;
		}
		print();
}
