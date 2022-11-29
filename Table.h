#pragma once
#include <iostream>
#include "Columns.h"
using namespace std;
class Table
{
private:
	char* name = nullptr;
	Column* columns = nullptr;
	int noColumns = 0;
	static int noTables;

public:
	Table() {}

	Table(char* name, Column* columns, int noColumns)
	{
		setName(name);
		setColumns(columns, noColumns);
	}

	~Table() {}

	Table(const Table& t)
	{
		setName(t.name);
		setColumns(t.columns, t.noColumns);
	}

	char* getName()
	{
		int nameSize = (int)strlen(this->name) + 1;
		char* nameCopy = new char[nameSize];
		for (int i = 0; i < nameSize; i++)
			nameCopy[i] = this->name[i];
		return nameCopy;
	}

	void setName(char* name)
	{
		if (name == nullptr) return;

		if (this->name)
			delete[] this->name;

		int nameSize = (int)strlen(name) + 1;
		this->name = new char[nameSize];
		for (int i = 0; i < nameSize; i++)
			this->name[i] = name[i];
	}

	Column* getColumns()
	{
		Column* columnsCopy = new Column[this->noColumns];

		for (int i = 0; i < noColumns; i++)
			columnsCopy[i] = this->columns[i];

		return columnsCopy;
	}

	void setColumns(Column* columns, int noColumns)
	{
		if (columns == nullptr) return;

		if (this->columns)
			delete[] this->columns;

		this->columns = new Column[noColumns];

		for (int i = 0; i < noColumns; i++)
			this->columns[i] = columns[i];
		this->noColumns = noColumns;
	}

	int getNoColumns()
	{
		return this->noColumns;
	}

	void setNoColumns(int noColumns)
	{
		this->noColumns = noColumns;
	}

	friend ostream& operator<<(ostream& console, const Table& t);
	friend bool operator==(const Table& t1, const Table& t2);
	friend bool operator<(const Table& t1, const Table& t2);
	static void numberOfTables() { cout << noTables; }

	Table operator=(const Table& t)
	{
		if (this != &t)
		{
			setName(t.name);
			setColumns(t.columns, t.noColumns);
		}
		return *this;
	}
};

int Table::noTables;

ostream& operator<<(ostream& console, const Table& t)
{
	cout << "Table: " << t.name << endl;
	cout << "Number of columns: " << t.noColumns << endl;
	cout << "Columns:" << endl;
	for (int i = 0; i < t.noColumns; i++)
	{
		cout << "Column " << i + 1 << ": " << t.columns[i].getName() << ", Type: " << t.columns[i].getType() << ", Default: ";
		switch (t.columns[i].getType())
		{
		case TEXT: cout << t.columns[i].getDefaultText(); break;
		case INTEGER: cout << t.columns[i].getDefaultInt(); break;
		case FLOAT: cout << t.columns[i].getDefaultFloat(); break;
		}
		cout << endl;
	}
	cout << endl;
	return console;
}

bool operator==(const Table& t1, const Table& t2)
{
	if (strcmp(t1.name, t2.name) == 0) return true;
	return false;
}

bool operator<(const Table& t1, const Table& t2)
{
	if (t1.noColumns < t2.noColumns) return true;
	return false;
}