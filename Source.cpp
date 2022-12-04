#include "Query.h"
using namespace std;

int main(int argc, char* argv[])
{
	cout << "Command formats: " << endl;
	cout << "CREATE TABLE table_name [IF NOT EXISTS] ((column_1_name,type,size, default_value), (column_2_name,type,size, default_value), …)" << endl;
	cout << "DROP TABLE table_name" << endl;
	cout << "DISPLAY TABLE table_name" << endl;
	cout << "CREATE INDEX [IF NOT EXISTS] index_name ON table_name (column_name)" << endl;
	cout << "DROP INDEX index_name" << endl;
	cout << "INSERT INTO table VALUES(...)" << endl;
	cout << "DELETE FROM table_name WHERE column_name = value" << endl;
	cout << "SELECT (at_least_one_column, ...) | ALL FROM table_name [WHERE column_name = value] " << endl;
	cout << "UPDATE table_name SET column_name = value WHERE  column_name = value" << endl;
	cout << "===============================================================================================================================" << endl << endl << endl;

	while (true)
	{
		Query query;
		cin >> query;
		query.parseQuery();
	}
	return 0;
}
//