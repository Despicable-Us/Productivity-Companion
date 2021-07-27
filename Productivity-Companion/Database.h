#pragma once
#include<string>
#include "InputField.h"
#include <iostream>
#include <sqlite3.h>
namespace udh
{

	int createDB(const char* s);
	int createTaskTable(const char* s);
	int deleteData(const char* s);
	int insertTaskData(const char* s, udh::inputField data);
	//int insertData(const char* s,std::string taskname);
	int updateData(const char* s);
	int LoadTaskList(const char* s);
	int callback(void* NotUsed, int argc, char** argv, char** azColName);
	void setGlobalListPtr(std::vector<udh::inputField>* Ptr);
}