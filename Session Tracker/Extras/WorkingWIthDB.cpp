#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#define SQLITE_OK 0

static int createDB(const char* s);
static int createTable(const char* s);
static int insertData(const char* s);
static int updateData(const char* s);
static int deleteData(const char* s);
static int selectData(const char* s);
static int callback(void*, int, char**, char**);

int main()
{
	const char* dir = "C:\\Users\\Progosta\\Desktop\\SQLITE\\Data\\STUDENTS.db";
	//createDB(dir);
	//createTable(dir);
	//insertData(dir);
	//updateData(dir);
	//deleteData(dir);
	selectData(dir);
	return 0;
}

static int createDB(const char* s)
{
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(s, &DB);
	sqlite3_close(DB);
	return 0;
}

static int createTable(const char* s)
{
	sqlite3* DB;
	char* messageError;
	std::string sql = "CREATE TABLE GRADES("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME		TEXT NOT NULL, "
		"LNAME		TEXT NOT NULL, "
		"AGE		INT NOT NULL, "
		"ADDRESS	CHAR(50), "
		"GRADE		CHAR(1) );";

	try
	{
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cout << messageError << std::endl;
			std::cerr << "Error in createTable function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Table created Successfully" << std::endl;
		sqlite3_close(DB);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

	return 0;
}


static int insertData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	//std::string sql("INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Alice', 'Chapa', 35, 'Tampa', 'A');"
	//	"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Bob', 'Lee', 20, 'Dallas', 'B');"
	//	"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Fred', 'Cooper', 24, 'New York', 'C');");
	std::string sql("INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Santosh', 'Pandey', 22, 'Kapilvastu', 'A');");

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in insertData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records inserted Successfully!" << std::endl;

	return 0;
}

static int updateData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql("UPDATE GRADES SET LNAME = 'Pandaya' WHERE LNAME = 'Pandey'");

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in updateData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records updated Successfully!" << std::endl;

	return 0;
}


static int deleteData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "DELETE FROM GRADES WHERE LNAME = 'Pandaya';";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in deleteData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records deleted Successfully!" << std::endl;

	return 0;
}

static int selectData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "SELECT * FROM GRADES;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;

	return 0;
}


// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	//std::cout << argc << std::endl;
	//for (int i = 0; i < argc; i++) {
	//	// column name and value
	//	std::cout << azColName[i] << ": " << argv[i] << std::endl;
	//}
	std::cout << azColName[0] << " : " << argv[0] << std::endl;

	std::cout << std::endl;

	return 0;
}