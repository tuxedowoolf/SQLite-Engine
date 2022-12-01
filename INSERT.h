#pragma once
#include "Table.h"
void Insert(char** tokenArray, int noTokens)
{
	char* tableName = tokenArray[2];
	char valuesString[] = "VALUES(";

	for (int i = 0; i < 7; i++)
	{
		if (tokenArray[3][i] != valuesString[i])
		{
			cout << "Invalid query!" << endl;
			return;
		}
	}

	char** valuesToken = new char*[noTokens - 2];

	for (int i = 3; i < noTokens; i++)
	{
		valuesToken[i - 3] = strtok(tokenArray[i], " VALUES,(\"");
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