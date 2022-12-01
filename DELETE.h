#pragma once
#include "Table.h"
#include <iostream>
using namespace std;
void Delete(char** tokenArray, int noTokens)
{
	char* tableName = tokenArray[2];

	if (strcmp(tokenArray[3], "WHERE") != 0)
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
		char* token = strtok(tokenArray[4], "=");
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
		
		if (tokenArray[4][strlen(tokenArray[4]) - 1] == '=')
		{
			whereTokens[0] = strtok(tokenArray[4], "=");
			whereTokens[1] = tokenArray[5];
			noWhereTokens = 2;
		}
		else if (tokenArray[5][0] == '=')
		{
			whereTokens[0] = tokenArray[4];
			whereTokens[1] = strtok(tokenArray[5], "=");
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
		if (strcmp(tokenArray[5], "=") == 0)
		{
			whereTokens[0] = tokenArray[4];
			whereTokens[1] = tokenArray[6];
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

	cout << "Deleted column from table '" << tableName << "' where " << whereTokens[0] << " = " << whereTokens[1] << "." << endl;
}