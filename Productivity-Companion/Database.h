#pragma once
#include<string>
#include "InputTodo.h"
#include <iostream>
#include <sqlite3.h>
namespace udh
{

	/// <summary>
	/// Creates a database file if it doesn't already exist.
	/// </summary>
	/// <param name="s">relative path to the db</param>
	/// <returns>exit status for sqlite3_open</returns>
	int createDB(const char* s);

	/// <summary>
	/// Creates a table TASKS in the database.
	/// </summary>
	/// <param name="s">The database to create table in.</param>
	/// <returns>Exit status of sqlite3_exec for table creation</returns>
	int createTaskTable(const char* s);
	int deleteData(const char* s);
	//int insertTaskData(const char* s, udh::inputField data);
	int insertTaskDB(const char* s, std::string);
	//int insertData(const char* s,std::string taskname);
	int updateData(const char* s);
	int LoadTaskList(const char* s);
	int callback(void* NotUsed, int argc, char** argv, char** azColName);
	//void setGlobalListPtr(std::vector<udh::inputField>* Ptr);

	int select_plan_sheet_data(const char* s, std::string);
	int delete_plan_sheet_data(const char* s, std::string);
}