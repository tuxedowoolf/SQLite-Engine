#pragma once
#include "Table.h"
#include <iostream>
using namespace std;
void Select(char** tokenArray, int noTokens)
{
	bool skipCol = false;
	if (strcmp(tokenArray[1], "ALL") == 0)
		skipCol = true;
	int fromPos = 0;
	for (int i = 0; i < noTokens; i++)
	{
		if (strcmp(tokenArray[i], "FROM") == 0)
		{
			fromPos = i;
			break;
		}
	}
	if (fromPos < 2)
	{
		cout << "Invalid query!" << endl;
		return;
	}
	char** columns = nullptr;
	if (!skipCol)
	{
		if (tokenArray[1][0] != '(' || tokenArray[fromPos-1][strlen(tokenArray[fromPos-1]) - 1] != ')')
		{
			cout << "Invalid query!" << endl;
			return;
		}
		columns = new char* [fromPos - 1];
		for (int i = 1; i < fromPos; i++)
		{
			char* column = strtok(tokenArray[i], " ,()");
			columns[i - 1] = column;
		}
		
	}
	char* tableName = tokenArray[fromPos + 1];

	if (noTokens > fromPos + 1)
	{
		if (strcmp(tokenArray[fromPos + 2], "WHERE") != 0)
		{
			cout << "Invalid query!" << endl;
			return;
		}
		char** whereTokens = new char* [2];
		int noWhereTokens = 0;
		switch (noTokens)
		{
		case 5:
		{
			char* token = strtok(tokenArray[fromPos + 3], "=");
			int i = 0;
			while (token != NULL)
			{
				whereTokens[i] = token;
				i++;
				noWhereTokens++;
				token = strtok(NULL, "=");
			}
			break;
		}
		case 6:
		{

			if (tokenArray[fromPos + 3][strlen(tokenArray[fromPos + 3]) - 1] == '=')
			{
				whereTokens[0] = strtok(tokenArray[fromPos + 3], "=");
				whereTokens[1] = tokenArray[fromPos + 4];
				noWhereTokens = 2;
			}
			else if (tokenArray[fromPos + 4][0] == '=')
			{
				whereTokens[0] = tokenArray[fromPos + 3];
				whereTokens[1] = strtok(tokenArray[fromPos + 4], "=");
				noWhereTokens = 2;
			}
			else
			{
				cout << "Invalid query!" << endl;
				return;
			}
			break;
		}
		case 7:
		{
			if (strcmp(tokenArray[fromPos + 4], "=") == 0)
			{
				whereTokens[0] = tokenArray[fromPos + 3];
				whereTokens[1] = tokenArray[fromPos + 5];
				noWhereTokens = 2;
			}
			else
			{
				cout << "Invalid query!" << endl;
				return;
			}
			break;
		}
		default:
		{
			cout << "Invalid query!" << endl;
			break;
		}

		}
		if (noWhereTokens != 2)
		{
			cout << "Invalid query!" << endl;
			return;
		}

		if (skipCol)
			cout << "Selected everything from '" << tableName << "' where " << whereTokens[0] << " = " << whereTokens[1] << "." << endl;
		else
		{
			cout << "Selected columns: ";
			for (int i = 0; i < fromPos - 1; i++)
				cout << columns[i] << ", ";
			cout << "from table '" << tableName << "' where " << whereTokens[0] << " = " << whereTokens[1] << "." << endl;
		}
		return;
	}
	if (skipCol)
		cout << "Selected everything from '" << tableName << "'." << endl;
	else
	{
		cout << "Selected columns: ";
		for (int i = 0; i < fromPos - 1; i++)
			cout << columns[i] << ", ";
		cout << "from table '" << tableName << "'." << endl;
	}
	
}
//