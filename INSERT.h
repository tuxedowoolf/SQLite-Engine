#pragma once
#include "Table.h"
void Insert(char** tokenArray, int noTokens)
{
	char* tableName = tokenArray[2];
	char valuesString[] = "VALUES(";
	int valueTokenStart = 3;

	if (strlen(tokenArray[3]) == 7)
	{
		for (int i = 0; i < 7; i++)
		{
			if (tokenArray[3][i] != valuesString[i])
			{
				cout << "Invalid query!" << endl;
				return;
			}
		}
	}
	else if (strlen(tokenArray[3]) == 6 && tokenArray[4][0] == '(')
	{
		for (int i = 0; i < 8; i++)
		{
			if (tokenArray[3][i] != valuesString[i])
			{
				cout << "Invalid query!" << endl;
				return;
			}
		}
		valueTokenStart = 4;
	}
	else
	{
		cout << "Invalid query!" << endl;
		return;
	}
	

	char** valuesToken = new char*[noTokens - 2];

	for (int i = valueTokenStart; i < noTokens; i++)
	{
		valuesToken[i - valueTokenStart] = strtok(tokenArray[i], " VALUES,(\"");
	}
	if (valuesToken[noTokens - 4][strlen(valuesToken[noTokens - 4]) + 1] != ')')
	{
		cout << "Invalid query!" << endl;
		return;
	}
	cout << "Inserted into table '" << tableName << "' the values: ";
	for (int j = 0; j < noTokens- 4; j++)
		cout << valuesToken[j] << ", ";
	cout << valuesToken[noTokens - 4] << "." << endl;
}