#include "Database/Database.hpp"

int main() {
	Database::registerConnector();
	Database db("sample.db");
}