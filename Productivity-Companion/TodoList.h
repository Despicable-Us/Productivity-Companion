#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "InputTodo.h"
#include<iostream>
#include<vector>
#include "button.h"
#include "Database.h"
#include "Btn.h"
#include <functional>

extern std::vector<udh::inputField> textList;//vector to store all the incomplete tasks as list
extern std::vector<udh::inputField> completed;//vector to store all the completed task as list
extern udh::inputField sampletext;//<udh::inputField> to be used as temp variable to add, edit and load the task into list
extern int viewPos;//int tp set the view position of the tasks while scrolling

#define TEXTAREA_HEIGHT 125.f

class TodoList
{
	sf::RectangleShape scrollBar;//scrollbar to show the current position in the list
	sf::CircleShape c1;// left circle of the textarea to give round finish
	sf::CircleShape c2;//right circle of the textarea to give round finish
	sf::Font fonts, roboto_font;
	std::vector<udh::inputField>::iterator editTaskItr;//iterator to track the current task being edited
	sf::Texture cover;//texture of cover image of the todolist window
	sf::Sprite TodoImage;//sprite of cover image of the todolist window
	udh::Button textarea;//textarea to input the task
	std::string a;//temp string to store the data of task before adding into task
public:

	bool run_todoList;//bool to check if checkaction is to be run on incomplete tasks list
	bool run_completedList;//bool to check if chechaction is to be run on completed tasks list
	Btn* home_back_btn;//button to go back to homepage
	std::function<void()> home_back_btn_func;//functtion to be called of homebackbutton is clicked
	bool home_back_btn_clicked;//bnoolean to check if home back button was clicked.
	sf::Text background_text;//text o display in the background
	std::string plan_sheet_name;//name of the plan sheet if it is a plansheet
	bool is_planner_sheet;//boolean to check if this is a plansheet

	/// <summary>
	/// default constructor
	/// </summary>
	TodoList();

	/// <summary>
	/// parameterized constructor in case of plansheet
	/// </summary>
	/// <param name="plan_name">name of the plansheet</param>
	TodoList(std::string);

	/// <summary>
	/// function the switch the planner sheet
	/// </summary>
	/// <param name="str">name of the plansheet to switch into</param>
	void Reset_Functions(std::string);

	/// <summary>
	/// function to load plansheet from db
	/// </summary>
	void LoadDB();

	/// <summary>
	/// function to load todolist from db
	/// </summary>
	void LoadTodoList();

	/// <summary>
	/// main function to run the todolist app
	/// </summary>
	/// <param name="window">sf::Renderwindow: the window to run the todolist app on</param>
	/// <param name="event">sf::Event: The event from the main app</param>
	/// <param name="taskView">view to draw thwe todolist on</param>
	/// <param name="run_main_window">bool to check if main window(homnepage) is to be shown</param>
	/// <param name="run_app">bool to check if Todo-List app is to be run</param>
	void RunTodo(sf::RenderWindow& window, sf::Event event, sf::View& TaskView, bool& run_main_window, bool& run_app);

	/// <summary>
	/// methods to draw the necessary things in the mainwindow
	/// </summary>
	/// <param name="window">window to draw</param>
	void DrawTodoMainWindow(sf::RenderWindow& window);

	/// <summary>
	/// function to draw elements into View
	/// </summary>
	/// <param name="window">window to draw the elements</param>
	void DrawTodoView(sf::RenderWindow& window);

	/// <summary>
	/// method to update the plansheet data into DB.
	/// </summary>
	void Update_DB();

};