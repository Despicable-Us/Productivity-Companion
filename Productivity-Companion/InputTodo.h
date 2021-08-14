#pragma once
#ifndef INPUT_FIELD
#define INPUT_FIELD

#include<iostream>
#include"SFML/Graphics.hpp"
#include<string.h>
#include"button.h"
#include <Windows.h>
#include <time.h>
#include "Icon.h"


#define COMPLETED_C 41, 41, 41


namespace udh
{
	class inputField
	{
		std::string text; //<string> to store task name and detail
		
		sf::Font font;//<sf::Font> font for the task to be printed
		int creationDay;// <int> to store the creation date
	public:
		sf::RectangleShape crossline;//<sf::Rectangle> to strikethrough the completed task
		bool completed = false;//<bool> to set the task as completed or incomplete
		udh::Button done;// done button for the task
		udh::Button del;//delete button for the task
		udh::Button edit;//edit button for the task
		sf::Texture del_tex, edit_tex;
		Icon del_icon;//icon of delete button for the task
		Icon edit_icon;//icon of edit button for the task
		sf::Text textdata; //<sf::Text> text of the task to display

		/// <summary>
		/// default constructor
		/// </summary>
		inputField();

		/// <summary>
		/// method to load texture for edit and delete button icon
		/// </summary>
		void loadIconTexture();

		/// <summary>
		/// Member function for setting string to text data member
		/// </summary>
		/// <param name="str">A string to set as stringdata in text member</param>
		void setdata(std::string str);
		
		/// <summary>
		/// Member function to draw the text in window
		/// </summary>
		/// <param name="window">refrence to sf::renderwindow to draw text into</param>
		void drawtext(sf::RenderWindow* window);

		/// <summary>
		/// member function
		/// </summary>
		/// <returns>
		/// string data available in text data member>
		/// </returns>
		std::string getdata();

		/// <summary>
		/// Member Function 
		/// </summary>
		/// <returns>string set in textdata member</returns>
		sf::Text gettext();

		/// <summary>
		/// Set drawing position for textdata menber
		/// </summary>
		/// <param name="position">A Vector2f to give coordinates of starting position</param>
		void setposition(sf::Vector2f position);

		/// <summary>
		/// Member function
		/// </summary>
		/// <returns>Font used in the textdata data member</returns>
		sf::Font getfont();

		/// <summary>
		/// sets completed to true
		/// </summary>
		void setdone();

		/// <summary>
		/// sets the completed status to the given parameter value
		/// </summary>
		/// <param name="a">bool value to set in "completed" data member</param>
		void setstatus(bool a)
		{
			this->completed = a;
		}

		/// <summary>
		/// sets timecreated to the integer for the present day
		/// </summary>
		void setCreationTime();

		/// <summary>
		/// method to get the value set to "completed"
		/// </summary>
		/// <returns>true if task is completed and false if it's not completed</returns>
		bool getstatus();

		/// <summary>
		/// method to get creationday
		/// </summary>
		/// <returns>int value for date of creation of task</returns>
		int getDay();

		/// <summary>
		/// method to set the creation date
		/// </summary>
		/// <param name="a">int to set as creationDay</param>
		void setday(int a);

		/// <summary>
		/// metthod to clean the text string of task to set into sql query
		/// </summary>
		/// <returns>string as cleaned data to add to sql query</returns>
		std::string SanitizedData();

		friend void drawlist(std::vector<udh::inputField>& textlist, std::vector<udh::inputField>&, sf::RenderWindow* window);
	};

	/// <summary>
	/// draw all the tasklist
	/// </summary>
	/// <param name="textlist">A vector containing inputfield objects to draw</param>
	/// <param name="window">A refrence of type Renderwindow to draw the list into</param>
	void drawlist(std::vector<udh::inputField>& textlist, std::vector<udh::inputField>&, sf::RenderWindow* window);

	/// <summary>
	/// checks the action user performs on the task
	/// </summary>
	/// <param name="event">Event type to check the action of user</param>
	/// <param name="textlist">Vector of inputfield objects to check the action was performed on which task</param>
	/// <param name="window">Refrence to RenderWindow to check which button was clicked wrt to position of cursor</param>
	/// <param name="itredit">Iterator to Vector of inputField which stores which task to edit if edit was pressed</param>
	/// <param name="sample">inputField type to store the string data already available in the task that was selected to edit</param>
	/// <param name="textarea">Refrence to the input area where text is entered</param>
	void checkAction(sf::Event event, std::vector<udh::inputField>& textlist, sf::RenderWindow* window,
		std::vector<udh::inputField>::iterator& itredit, udh::inputField& sample, udh::Button& textarea, bool&);

	/// <summary>
	/// Edits the task if edit button for that task is pressed
	/// </summary>
	/// <param name="sampletext">A inputfield type to store buffer of task info before saving into actual task</param>
	/// <param name="a">A string to use as buffer to store user input data</param>
	/// <param name="event">Event to check the user action</param>
	/// <param name="edititr">iterator to the task which is to be edited</param>
	/// <param name="textarea">Refrence to the input area to edit the task</param>
	void editTask(udh::inputField& sampletext, std::string& a, sf::Event event, std::vector<udh::inputField>::iterator& edititr,
		udh::Button& textarea);

	/// <summary>
	/// Adds task to the tasklist
	/// </summary>
	/// <param name="sampletext">A inputfield type to store buffer of task info before saving into actual task</param>
	/// <param name="a">A string to use as buffer to store user input data</param>
	/// <param name="event">Event to check the user action</param>
	/// <param name="textlist">A vector to store all the task as a list of task</param>
	/// <param name="textarea">Refrence to the input area to type the task to add</param>
	void addTask(udh::inputField& sampletext, std::string& a, sf::Event event, std::vector<udh::inputField>& textlist, udh::Button textarea, bool is_planner_list);
};
#endif // !INPUT_FIELD