#pragma once
#include "Table.h"
void Update(char** tokenArray, int noTokens)
{
	char* tableName = tokenArray[1];
	if (strcmp(tokenArray[2], "SET") != 0)
	{
		cout << "Invalid query!" << endl;
		return;
	}
	char** setTokens = new char* [2];
	int noSetTokens = 0;
	int wherePos = 0;
	for (int i = 0; i < noTokens; i++)
	{
		if (strcmp(tokenArray[i], "WHERE") == 0)
		{
			wherePos = i;
			break;
		}
	}
	if (wherePos < 4 || wherePos > 6)
	{
		cout << "Invalid query!" << endl;
		return;
	}

	switch (wherePos)
	{
	case 4:
	{
		char* token = strtok(tokenArray[3], "=");
		int i = 0;
		while (token != NULL)
		{
			setTokens[i] = token;
			i++;
			noSetTokens++;
			token = strtok(NULL, "=");
		}
		break;
	}
	case 5:
	{

		if (tokenArray[3][strlen(tokenArray[3]) - 1] == '=')
		{
			setTokens[0] = strtok(tokenArray[3], "=");
			setTokens[1] = tokenArray[4];
			noSetTokens = 2;
		}
		else if (tokenArray[4][0] == '=')
		{
			setTokens[0] = tokenArray[3];
			setTokens[1] = strtok(tokenArray[4], "=");
			noSetTokens = 2;
		}
		else
		{
			cout << "Invalid query!" << endl;
			return;
		}
		break;
	}
	case 6:
	{
		if (strcmp(tokenArray[4], "=") == 0)
		{
			setTokens[0] = tokenArray[3];
			setTokens[1] = tokenArray[5];
			noSetTokens = 2;
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
	if (noSetTokens != 2)
	{
		cout << "Invalid query!" << endl;
		return;
	}

	char** whereTokens = new char* [2];
	int noWhereTokens = 0;
	switch (noTokens - wherePos)
	{
	case 2:
	{
		char* token = strtok(tokenArray[wherePos + 1], "=");
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
	case 3:
	{

		if (tokenArray[wherePos + 1][strlen(tokenArray[wherePos + 1]) - 1] == '=')
		{
			whereTokens[0] = strtok(tokenArray[wherePos + 1], "=");
			whereTokens[1] = tokenArray[wherePos + 2];
			noWhereTokens = 2;
		}
		else if (tokenArray[wherePos + 2][0] == '=')
		{
			whereTokens[0] = tokenArray[wherePos + 1];
			whereTokens[1] = strtok(tokenArray[wherePos + 2], "=");
			noWhereTokens = 2;
		}
		else
		{
			cout << "Invalid query!" << endl;
			return;
		}
		break;
	}
	case 4:
	{
		if (strcmp(tokenArray[wherePos + 2], "=") == 0)
		{
			whereTokens[0] = tokenArray[wherePos + 1];
			whereTokens[1] = tokenArray[wherePos + 3];
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
	

	cout << "Changed value of column '" << setTokens[0] << "' with '" << setTokens[1];
	cout << "' where " << whereTokens[0] << " = " << whereTokens[1];
	cout << " from table '" << tableName << "'." << endl;
}
//