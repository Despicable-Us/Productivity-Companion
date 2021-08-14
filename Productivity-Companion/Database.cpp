//Final Version

#include "database.h"
#include<vector>
extern udh::inputField sampletext;
extern std::vector<udh::inputField> textList;
extern std::vector<udh::inputField> completed;
extern sqlite3* DB;

int udh::createDB(const char* s)
{
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(s, &DB);
	sqlite3_close(DB);
	return exit;
}

int udh::createTaskTable()
{
	char* messageError;

	std::string sql = "CREATE TABLE IF NOT EXISTS TASKS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"Task      TEXT NOT NULL, "
		"Status INTEGER,"
		"Day INTEGER);";

		int exit = 0;
	try
	{
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in createTable function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Table created Successfully" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return exit;
}

int udh::createPlannerTable()
{
	char* messageError;
	std::string sql = "CREATE TABLE IF NOT EXISTS PLANNER("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"plan_sheet_name VARCHAR(100));";

	int exit = 0;
	try
	{
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in createPlannerTable function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Planner Table created Successfully" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return exit;
}

int udh::createPlannerListTable()
{
	char* messageError;
	std::string sql = "CREATE TABLE IF NOT EXISTS PLANNER_LIST("
		"ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
		"Task      TEXT NOT NULL, "
		"Status INTEGER,"
		"Day INTEGER,"
		"plan_sheet_name VARCHAR(40));";

	int exit = 0;
	try
	{
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in createPlannerList function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Planner ListTable created Successfully" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return exit;
}

int udh::insertTaskDB(std::string sql_data)
{
	char* messageError;
	int exit;
	exit = sqlite3_exec(DB, sql_data.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in insertData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records inserted Successfully!" << std::endl;
	return 0;
}


int udh::AddTask (udh::inputField task)
{
	char* messageError;
	std::string sql = "INSERT INTO TASKS (Task,Status,Day) VALUES('" + task.SanitizedData() + "', '" +
		std::to_string(task.getstatus()) + "','" + std::to_string(task.getDay()) + "');";

	int exit;
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in AddTask function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records Added Successfully!" << std::endl;

	return 0;
}


int udh::updateTask(std::vector<udh::inputField>::iterator itr)
{
	char* messageError;

	std::string sql = "UPDATE TASKS SET Task ='" + sampletext.SanitizedData()+ "' WHERE Task = '"+itr->SanitizedData()+"';";

	int exit;
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in updateTask function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records updated Successfully!" << std::endl;

	return 0;
}



int udh::DeleteTask(std::vector<udh::inputField>::iterator itr)
{
	char* messageError;
	std::string sql = "DELETE FROM TASKS WHERE Task = '" + itr->SanitizedData()+"';";

	int exit;
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in DeleteTask function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records Deleted Successfully!" << std::endl;

	return 0;
}

int udh::UpdateStatus(std::string sql)
{
	char* messageError;

	int exit;
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in updateTask function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records updated Successfully!" << std::endl;

	return 0;
}


int udh::delete_plan_sheet_data(const char* s, std::string plan_sheet_name)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "DELETE FROM PLANNER_LIST WHERE plan_sheet_name = '" + plan_sheet_name + "';";

	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in deleteData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records deleted Successfully!" << std::endl;

	return 0;
}

int udh::create_main_session_table()
{
	char* messageError;

	std::string sql = "CREATE TABLE IF NOT EXISTS SESSION("
		"id INTEGER NOT NULL PRIMARY KEY, "
		"session_name VARCHAR(100) );";

	int exit = 0;
	try
	{
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in SESSION TABLE creation function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "SESSION TABLE created Successfully." << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return exit;
}

int udh::create_session_list_table()
{
	char* messageError;

	std::string sql = "CREATE TABLE IF NOT EXISTS SESSION_LIST("
		"id INTEGER NOT NULL PRIMARY KEY, "
		"session_detail VARCHAR(255) NOT NULL,"
		"session_id_name VARCHAR(100) NOT NULL,"
		"total_time VARCHAR(100) NOT NULL);";

	int exit = 0;
	try
	{
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in createTable function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Table created Successfully" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return exit;
}

int udh::open_db()
{
	int exit = 0;
	const char* s = "Productivity_companion.db";
	exit = sqlite3_open(s, &DB);
	return exit;
}

int udh::close_db()
{
	const char* s = "Productivity_companion.db";
	int exit = 0;
	sqlite3_close(DB);
	return exit;
}

int udh::LoadTaskList()

{
	char* messageError;
	std::string sql = "SELECT * FROM TASKS;";
	int exit;
	exit = sqlite3_exec(DB, sql.c_str(), udh::callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;

	return exit;
}

int udh::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	sampletext.setdata(argv[1]);
	sampletext.setCreationTime();
	if (std::stoi(argv[2]) == 0)
	{
		sampletext.setstatus(false);
	}
	else
	{
		sampletext.setstatus(true);
	}
	sampletext.setday(std::stoi(argv[3]));
	if (sampletext.getstatus())
	{
		completed.push_back(sampletext);
	}
	else
	{
		textList.push_back(sampletext);
	}
	return 0;
}

int udh::select_plan_sheet_data(const char* s, std::string name)
{
	sqlite3* DB;
	char* messageError;
	std::string sql = "SELECT * FROM PLANNER_LIST WHERE plan_sheet_name = '" +  name + "';";
	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), udh::callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
	{
		std::cout << "Records selected Successfully!" << std::endl;
	}
	sqlite3_close(DB);
	return 0;
}