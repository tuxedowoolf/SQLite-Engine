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
	int size = 0;

	char* defaultText = nullptr;
	int defaultInt = 0;
	double defaultFloat = 0;

public:
	Column() {};
	Column(char* name, ColumnType type, int size)
	{
		setName(name);
		setType(type);
		setSize(size);
	}
	Column(char* name, ColumnType type, int size, char* defaultText) : Column(name, type, size) { setDefaultText(defaultText); }

	Column(char* name, ColumnType type, int size, int defaultInt) : Column(name, type, size) { setDefaultInt(defaultInt); }

	Column(char* name, ColumnType type, int size, double defaultFloat) : Column(name, type, size) { setDefaultFloat(defaultFloat); }

	~Column() {}

	Column(const Column& c)
	{
		setName(c.name);
		setType(c.type);
		setSize(c.size);
		switch (c.type)
		{
		case TEXT: setDefaultText(c.defaultText); break;
		case INTEGER: setDefaultInt(c.defaultInt); break;
		case FLOAT: setDefaultFloat(c.defaultFloat); break;
		}
	}

	char* getName()
	{
		if (strlen(this->name) < 2)
		{
			char* copy = new char[1];
			copy[0] = ""[0];
		}
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

	int getSize() { return this->size; }
	void setSize(int size) { this->size = size; }

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
//