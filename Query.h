#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ValidTokens.h"
#include "CREATE INDEX.h"
#include "CREATE TABLE.h"
#include "DELETE.h"
#include "DISPLAY TABLE.h"
#include "DROP INDEX.h"
#include "DROP TABLE.h"
#include "INSERT.h"
#include "SELECT.h"
#include "UPDATE.h"
#include "Table.h"
#include "Index.h"
#include "Columns.h"
using namespace std;

class Query
{
private:
	char* query = nullptr;
	char** tokens = new char* [50];
	int noTokens = 0;
	static int queryNumber;

public:
	Query() {};

	Query(const char* query)
	{
		setQuery(query);
		setTokens();
	}

	~Query() {}

	Query(const Query& q)
	{
		setQuery(q.query);
		setTokens();
	}

	char* getQuery() 
	{ 
		int querySize = (int)strlen(this->query) + 1;
		char* queryCopy = new char[querySize];
		for (int i = 0; i < querySize; i++)
			queryCopy[i] = this->query[i];
		return queryCopy; 
	}
	
	void setQuery(const char* query)
	{
		if (query == nullptr) return;

		if (this->query)
			delete[] this->query;

		int querySize = (int) strlen(query) + 1;
		this->query = new char[querySize];
		for (int i = 0; i < querySize; i++)
			this->query[i] = query[i];
	}

	char** getTokens() 
	{ 
		char** tokensCopy = new char* [50];
		char* queryCopy = getQuery();

		char* token = strtok(queryCopy, " ;");
		int i = 0;
		while (token != NULL)
		{
			tokensCopy[i] = token;
			i++;
			token = strtok(NULL, " ;");
		}

		return tokensCopy; 
	}

	void setTokens()
	{
		char* queryCopy = getQuery();

		char* token = strtok(queryCopy, " ;");
		int i = 0;
		while (token != NULL)
		{
			this->tokens[i] = token;
			i++;
			token = strtok(NULL, " ;");
		}
		setNoTokens(i);
	}

	int getNoTokens() { return this->noTokens; }

	void setNoTokens(int noTokens) { this->noTokens = noTokens; }

	void parseQuery()
	{
		char* op = this->tokens[0];
		Operation operation = NULLOP;
		Target target = NULLTG;
		if (strcmp(op, "CREATE") == 0) operation = CREATE;
		if (strcmp(op, "DROP") == 0) operation = DROP;
		if (strcmp(op, "DISPLAY") == 0) operation = DISPLAY;
		if (strcmp(op, "INSERT") == 0) operation = INSERT;
		if (strcmp(op, "DELETE") == 0) operation = DELETE;
		if (strcmp(op, "SELECT") == 0) operation = SELECT;
		if (strcmp(op, "UPDATE") == 0) operation = UPDATE;

		switch (operation)
		{
		case CREATE:
		{
			char* tg = this->tokens[1];
			if (strcmp(tg, "TABLE") == 0) target = TABLE;
			if (strcmp(tg, "INDEX") == 0) target = INDEX;

			switch (target)
			{
			case TABLE:
			{
				CreateTable(getTokens(), getNoTokens());
				break;
			}
			case INDEX:
			{
				CreateIndex(getTokens(), getNoTokens());
				break;
			}
			default: cout << endl << "Not a valid query!" << endl;
			}
			break;
		}
		case DROP:
		{
			if (noTokens > 3)
			{
				cout << "Invalid query!" << endl;
				return;
			}
			char* tg = this->tokens[1];
			if (strcmp(tg, "TABLE") == 0) target = TABLE;
			if (strcmp(tg, "INDEX") == 0) target = INDEX;

			switch (target)
			{
			case TABLE:
			{
				char* tableName = this->tokens[2];
				DropTable(tableName);
				break;
			}
			case INDEX:
			{
				char* indexName = this->tokens[2];
				DropIndex(indexName);
				break;
			}
			default: cout << endl << "Not a valid query!" << endl;
			}
			break;
		}
		case DISPLAY:
		{
			if (this->noTokens > 3)
			{
				cout << "Invalid query!" << endl;
				return;
			}
			char* tg = this->tokens[1];
			if (strcmp(tg, "TABLE") == 0) target = TABLE;
			else 
			{
				cout << "Invalid query!" << endl;
				return;
			}
			char* tableName = this->tokens[2];
			DisplayTable(tableName);
			break;
		}
		case INSERT:
		{
			if (strcmp(this->tokens[1], "INTO") != 0)
			{
				cout << "Invalid query!" << endl;
				return;
			}
			Insert(getTokens(), getNoTokens());

			break;
		}
		case DELETE:
		{
			if (strcmp(this->tokens[1], "FROM") != 0)
			{
				cout << "Invalid query!" << endl;
				return;
			}
			Delete(getTokens(), getNoTokens());
			break;
		}
		case SELECT:
		{
			Select(getTokens(), getNoTokens());
			break;
		}
		case UPDATE:
		{
			Update(getTokens(), getNoTokens());
			break;
		}
		default: cout << endl << "Not a valid query!" << endl;
		}
	}

	void readQuery(istream& input);
	friend istream& operator>>(istream& input, Query& q);
	friend ostream& operator<<(ostream& console, const Query& q);
};

int Query::queryNumber;

void Query::readQuery(istream& input)
{
	cout << "Please input your query:" << endl;
	char* queryInput;
	queryInput = new char[257];
	input.getline(queryInput, 256);
	if (strlen(queryInput) < 3) return;
	setQuery(queryInput);
	setTokens();
}

istream& operator>>(istream& input, Query& q)
{
	q.readQuery(input);
	return input;
}

ostream& operator<<(ostream& console, const Query& q)
{
	cout << endl << "Command entered: " << endl << q.query << endl;
	for (int i = 0; i < q.noTokens; i++)
		cout << q.tokens[i] << endl;
	return console;
}