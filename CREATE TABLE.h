#pragma once
#include "Table.h"

void CreateTable(char** tokenArray, int noTokens)
{
	char* tableName = tokenArray[2];
	bool existCheck = false;

	int columnStart = 3;

	if (strcmp(tokenArray[3], "IF") == 0)
	{
		
		if (strcmp(tokenArray[4], "NOT") == 0 && strcmp(tokenArray[5], "EXISTS") == 0)
		{
			existCheck = true;
			columnStart = 6;
		}
		else {
			cout << "Invalid query!" << endl;
			return;
		}
	}

	if (tokenArray[columnStart][0] != '(')
	{
		cout << "Invalid query!" << endl;
		return;
	}

	int noColumns = noTokens - columnStart;

	Column* columns = new Column[noColumns];

	for (int x = columnStart; x < noTokens; x++)
	{
		char** colTokens = new char* [noTokens - x];
		char* colToken = strtok(tokenArray[x], " ,()");

		int i = 0;
		while (colToken != NULL && i < 4)
		{
			colTokens[i] = colToken;
			i++;
			colToken = strtok(NULL, ",)");
		}
		

		char* columnName = colTokens[0];
		ColumnType columnType = TEXT;
		char* defaultText = (char*)"hello";
		int defaultInt = 0;
		double defaultFloat = 0;

		int size = 0;

		try { size = (int)colTokens[2]; }
		catch (int size){ throw "Invalid size!"; }

		if (strcmp(colTokens[1], "TEXT") == 0)
		{
			if (colTokens[3][0] == '\"')
			{
				if (colTokens[3][1] == '\"')
				{
					defaultText = new char[1];
					defaultText[0] = ""[0];
				}
				else {
					char** textTokens = new char* [noTokens - x];
					textTokens[0] = colTokens[3];
					int noText = 1;
					int y = x;
					int t = 1;
					cout << colTokens[3];
					int textSize = strlen(colTokens[3]);
					for (y = x + 1; y < noTokens; y++)
					{
						char* textToken = strtok(tokenArray[y], " ,()");

						while (textToken != NULL)
						{
							textTokens[t] = textToken;
							t++;
							noText++;
							textSize += strlen(textToken) + 2;
							textToken = strtok(NULL, ",)");
						}
					}
					x = y;
					defaultText = new char[textSize];
					int p = 0;
					if (textTokens[0][0] != '\"' && textTokens[noText][strlen(textTokens[noText]) + 1] != '\n')
					{
						cout << "Invalid query!" << endl;
						return;
					}
					for (int q = 0; q < noText; q++)
					{
						for (int r = 0; r < strlen(textTokens[q]) + 1; r++)
						{
							if (textTokens[q][r] != '\"')
							{
								defaultText[p] = textTokens[q][r];
								p++;
							}
						}
						if (q != noText - 1)
						{
							defaultText[p] = ' ';
							p++;
						}
						else defaultText[p] = '\0';

					}
					noColumns = noColumns - noText + 1;
					Column column(columnName, columnType, size, defaultText);
					columns[x - noText - columnStart] = column;
				}
				
			}
			else
			{
				cout << "Invalid query!";
				return;
			}
		}
		else if (strcmp(colTokens[1], "INTEGER") == 0)
		{
			columnType = INTEGER;
			defaultInt = atoi(colTokens[3]);
			Column column(columnName, columnType, size, defaultInt);
			columns[x - columnStart] = column;
		}
		else if (strcmp(colTokens[1], "FLOAT") == 0)
		{
			columnType = FLOAT;
			defaultFloat = atof(colTokens[3]);
			Column column(columnName, columnType, size, defaultFloat);
			columns[x - columnStart] = column;
		}
		else
		{
			cout << "Invalid query!" << endl;
			return;
		}
	}
	Column* updatedColumns = new Column[noColumns];
	updatedColumns = columns;

	Table table(tableName, columns, noColumns);
	cout << "You just created a table:" << endl << table;
}
//