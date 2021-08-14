#pragma once
#include<string>
#include "InputTodo.h"
#include <iostream>
#include <sqlite3.h>
#include <vector>
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
	int createTaskTable();

	/// <summary>
	/// function to create PLANNER table in db
	/// </summary>
	/// <returns>exit status of sql execution</returns>
	int createPlannerTable();

	/// <summary>
	/// function to create PLANNER_LIST table in db
	/// </summary>
	/// <returns>exit status of sql execution</returns>
	int createPlannerListTable();

	/// <summary>
	/// function to add task in db
	/// </summary>
	/// <param name="sql">sql query to be executed</param>
	/// <returns>exit status of sql execution</returns>
	int insertTaskDB(std::string sql);

	/// <summary>
	/// function to add task in db
	/// </summary>
	/// <param name="task">Task to be added in db</param>
	/// <returns>exit status of sql execution</returns>
	int AddTask(udh::inputField task);

	/// <summary>
	/// function to update task in db
	/// </summary>
	/// <param name="itr">itrator to the task to be updated in db</param>
	/// <returns>exit status of sql execution</returns>
	int updateTask(std::vector<udh::inputField>::iterator itr);

	/// <summary>
	/// function to delete the task from db
	/// </summary>
	/// <param name="itr">iteratoir to the task to be deleted from db</param>
	/// <returns>exit status of sql execution</returns>
	int DeleteTask(std::vector<udh::inputField>::iterator itr);

	/// <summary>
	/// function to update the status whether completed or not in db
	/// </summary>
	/// <param name="sql">sql query to be executed</param>
	/// <returns>exit status of sql execution</returns>
	int UpdateStatus(std::string sql);

	/// <summary>
	/// function to load the task list from db
	/// </summary>
	/// <returns>exit status of sql execution</returns>
	int LoadTaskList();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="NotUsed">default unused parameter</param>
	/// <param name="argc">the number of columns in the result</param>
	/// <param name="argv">an array of pointers to strings obtained from the column in table, one for each column</param>
	/// <param name="azColName">name of the column</param>
	/// <returns>0</returns>
	int callback(void* NotUsed, int argc, char** argv, char** azColName);

	int select_plan_sheet_data(const char* s, std::string);
	int delete_plan_sheet_data(const char* s, std::string);
	int create_main_session_table();
	int create_session_list_table();

	int open_db();
	int close_db();
}