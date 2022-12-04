#include "Table.h"
#include "Index.h"
#include <iostream>
using namespace std;
#pragma once
void CreateIndex(char** tokenArray, int noTokens)
{
	
	bool existCheck = false;

	int nameStart = 2;

	int noValidTokens = 6;

	if (strcmp(tokenArray[2], "IF") == 0)
	{

		if (strcmp(tokenArray[3], "NOT") == 0 && strcmp(tokenArray[4], "EXISTS") == 0)
		{
			existCheck = true;
			nameStart = 5;
			noValidTokens = 9;
		}
		else {
			cout << "Invalid query!" << endl;
			return;
		}
	}

	if (noTokens > noValidTokens)
	{
		cout << "Invalid query!" << endl;
		return;
	}

	char* indexName = tokenArray[nameStart];

	if (strcmp(tokenArray[nameStart + 1], "ON") != 0)
	{
		cout << "Invalid query!" << endl;
		return;
	}

	char* tableName = tokenArray[nameStart + 2];
	int columnNameSize = strlen(tokenArray[nameStart + 3]);
	if (tokenArray[nameStart + 3][0] != '(' || tokenArray[nameStart + 3][columnNameSize - 1] != ')')
	{
		cout << "Invalid query!" << endl;
		return;
	}
	
	char* columnName = strtok(tokenArray[nameStart + 3], "()");

	Index index(indexName, tableName, columnName);
	cout << "Created the following index: " << endl << index << endl;
}
//