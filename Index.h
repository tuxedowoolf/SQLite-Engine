#pragma once
#include <iostream>
using namespace std;
class Index 
{
private:
	char* name = nullptr;
	char* tableName = nullptr;
	char* columnName = nullptr;
public:
	Index() {}

	Index(char* name, char* tableName, char* columnName)
	{
		setName(name);
		setTableName(tableName);
		setColumnName(columnName);
	}

	~Index() {}

	Index(const Index& i)
	{
		setName(i.name);
		setTableName(i.tableName);
		setColumnName(i.columnName);
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

	char* getTableName()
	{
		int nameSize = (int)strlen(this->tableName) + 1;
		char* nameCopy = new char[nameSize];
		for (int i = 0; i < nameSize; i++)
			nameCopy[i] = this->tableName[i];
		return nameCopy;
	}

	void setTableName(char* tableName)
	{
		if (tableName == nullptr) return;

		if (this->tableName)
			delete[] this->tableName;

		int nameSize = (int)strlen(tableName) + 1;
		this->tableName = new char[nameSize];
		for (int i = 0; i < nameSize; i++)
			this->tableName[i] = tableName[i];
	}

	char* getColumnName()
	{
		int nameSize = (int)strlen(this->columnName) + 1;
		char* nameCopy = new char[nameSize];
		for (int i = 0; i < nameSize; i++)
			nameCopy[i] = this->columnName[i];
		return nameCopy;
	}

	void setColumnName(char* columnName)
	{
		if (columnName == nullptr) return;

		if (this->columnName)
			delete[] this->columnName;

		int nameSize = (int)strlen(columnName) + 1;
		this->columnName = new char[nameSize];
		for (int i = 0; i < nameSize; i++)
			this->columnName[i] = columnName[i];
	}

	friend ostream& operator<<(ostream& console, const Index& i);
};
ostream& operator<<(ostream& console, const Index& i)
{
	cout << "Index " << i.name << " on column " << i.columnName << " of table " << i.tableName << "." << endl;
	return console;
}
//