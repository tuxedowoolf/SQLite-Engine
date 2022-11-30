#pragma once
#include "Table.h"
#include "Index.h"
void DropIndex(char* indexName)
{
	cout << "You deleted the index: '" << indexName << "'." << endl;
}