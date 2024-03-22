// test_sqlite.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "Poco/SharedPtr.h"
#include "Poco/DateTime.h"

#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/RecordSet.h"

// #pragma comment (lib , "PocoFoundationd.lib")
// #pragma comment (lib , "PocoDatad.lib")
// #pragma comment (lib , "PocoDataSQLited.lib")

 
using namespace Poco::Data::Keywords;
using Poco::DateTime;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Data::RecordSet;
using Poco::Data::SQLite::Connector;

int main(int argc, char* argv[])
{
	Connector::registerConnector();

#if 1
	// create a session
	Session session("SQLite", "sample.db");

	// drop sample table, if it exists
	session << "DROP TABLE IF EXISTS Person", now;

	// (re)create table
	session << "CREATE TABLE Person (Name VARCHAR(30), Address VARCHAR, Age INTEGER(3), Birthday DATE)", now;

	// insert some rows
	DateTime bd(1980, 4, 1);
	DateTime ld(1982, 5, 9);
	session << "INSERT INTO Person VALUES('bob', 'beijing', 12, ?)", use(bd), now;
	session << "INSERT INTO Person VALUES('sam', 'shanghai', 10, ?)", use(ld), now;

	// a simple query
	Statement select(session);
	select << "SELECT * FROM Person";
#else
	// create a session
	Session session("SQLite", "test.db");
	Statement select(session);
	select << "SELECT * FROM user";
#endif // 0
	try
	{
		select.execute();
	}
	catch (const std::exception& e)
	{
		const char * buf = e.what();
		std::cout <<buf << std::endl;
	}

	// create a RecordSet 
	RecordSet rs(select);
	std::size_t cols = rs.columnCount();
	// print all column names
	for (std::size_t col = 0; col < cols; ++col)
	{
		std::cout << rs.columnName(col) << "\t";// << std::endl;
	}
	std::cout << std::endl;
	// iterate over all rows and columns
	bool more = rs.moveFirst();
	while (more)
	{
		for (std::size_t col = 0; col < cols; ++col)
		{
			std::cout << rs[col].convert<std::string>() << "\t";
		}
		std::cout << std::endl;
		more = rs.moveNext();
	}

	return 0;
}


