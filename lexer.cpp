#include "lexer.hpp"

int main() {
	string filename, outputFileName;
	cout << "Please enter text file name: ";
	cin >> filename;

	cout << "Please enter output file name: ";
	cin >> outputFileName;

	
	fin.open(filename);
	outputFile.open(outputFileName);

	cout << "Tokens               Lexemes\n"; // prints headers 
	cout << "----------------------------\n";
	outputFile << "Tokens               Lexemes\n";
	outputFile << "----------------------------\n";

	while (!fin.eof()) 
	{
		ch = fin.get();
		lexer();
	}

	fin.close();
	outputFile.close();

	system("pause");
	return 0;
}