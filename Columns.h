#pragma once
#include <iostream>
using namespace std;
enum ColumnType
{
	TEXT,
	INTEGER,
	FLOAT
};

class Column
{
private:
	char* name = nullptr;
	ColumnType type = TEXT;

	char* defaultText = nullptr;
	int defaultInt = 0;
	double defaultFloat = 0;

public:
	Column() {};
	Column(char* name, ColumnType type)
	{
		setName(name);
		setType(type);
	}
	Column(char* name, ColumnType type, char* defaultText) : Column(name, type) { setDefaultText(defaultText); }

	Column(char* name, ColumnType type, int defaultInt) : Column(name, type) { setDefaultInt(defaultInt); }

	Column(char* name, ColumnType type, double defaultFloat) : Column(name, type) { setDefaultFloat(defaultFloat); }

	~Column() {}

	Column(const Column& c)
	{
		setName(c.name);
		setType(c.type);
		switch (c.type)
		{
		case TEXT: setDefaultText(c.defaultText); break;
		case INTEGER: setDefaultInt(c.defaultInt); break;
		case FLOAT: setDefaultFloat(c.defaultFloat); break;
		}
	}

	char* getName()
	{
		char* nameCopy = new char[strlen(this->name) + 1];
		for (int i = 0; i < strlen(this->name) + 1; i++)
			nameCopy[i] = this->name[i];
		return nameCopy;
	}
	void setName(char* name)
	{
		if (name == nullptr) return;

		if (this->name) delete[] this->name;

		this->name = new char[strlen(name) + 1];
		for (int i = 0; i < strlen(name) + 1; i++)
			this->name[i] = name[i];
	}

	ColumnType getType() { return this->type; }
	void setType(ColumnType type) { this->type = type; }

	char* getDefaultText()
	{
		char* textCopy = new char[strlen(this->defaultText) + 1];
		for (int i = 0; i < strlen(this->defaultText) + 1; i++)
			textCopy[i] = this->defaultText[i];
		return textCopy;
	}
	void setDefaultText(char* defaultText)
	{
		if (defaultText == nullptr) return;

		if (this->defaultText) delete[] this->defaultText;

		this->defaultText = new char[strlen(defaultText) + 1];
		for (int i = 0; i < strlen(defaultText) + 1; i++)
			this->defaultText[i] = defaultText[i];
	}

	int getDefaultInt() { return this->defaultInt; }
	void setDefaultInt(int defaultInt) { this->defaultInt = defaultInt; }

	double getDefaultFloat() { return this->defaultFloat; }
	void setDefaultFloat(double defaultFloat) { this->defaultFloat = defaultFloat; }
};