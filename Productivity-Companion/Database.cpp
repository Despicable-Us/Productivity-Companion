
//Final Version

#include "database.h"
#include<vector>
extern udh::inputField sampletext;
extern std::vector<udh::inputField> textList;
int udh::createDB(const char* s)
{
	sqlite3* DB;

	int exit = 0;
	exit = sqlite3_open(s, &DB);
	sqlite3_close(DB);

	return exit;
}

int udh::createTaskTable(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "CREATE TABLE IF NOT EXISTS TASKS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"Task      TEXT NOT NULL, "
		"Status INTEGER,"
		"Day INTEGER);";

		int exit = 0;
	try
	{
		exit = sqlite3_open(s, &DB);
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
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
	return exit;
}
//insert OK!!
//int udh::insertTaskData(const char* s, std::string sql_data)
//{
//	
//
//	return 0;
//}

int udh::insertTaskDB(const char* s, std::string sql_data)
{
	sqlite3* DB;
	char* messageError;

	//std::string task = data.getdata();
	//task.replace(task.find("'"), 2, "''");
	//std::string sql = "INSERT INTO TASKS (Task,Status,Day) VALUES('" + task + "', '" +
						//std::to_string(data.getstatus()) +"','"+std::to_string(data.getDay())+ "');";

	int exit = sqlite3_open(s, &DB);
	std::cout << sql_data << std::endl;
	exit = sqlite3_exec(DB, sql_data.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in insertData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records inserted Successfully!" << std::endl;
	return 0;
}


//Working inloading
int udh::updateData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'");

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

int udh::deleteData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "DROP TABLE TASKS;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in deleteData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records deleted Successfully!" << std::endl;

	return 0;
}



int udh::LoadTaskList(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "SELECT * FROM TASKS;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), udh::callback, NULL, &messageError);

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
int udh::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	sampletext.setdata(argv[1]);
	sampletext.setCreationTime();
	if (std::stoi(argv[2]) == 0)
	{
		sampletext.setstatus(false);
	}
	else
		sampletext.setstatus(true);
	sampletext.setday(std::stoi(argv[3]));
	textList.push_back(sampletext);
	return 0;
}


