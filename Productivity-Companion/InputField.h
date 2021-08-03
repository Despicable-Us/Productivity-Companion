#pragma once
#ifndef INPUT_FIELD
#define INPUT_FIELD

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"SFML/Graphics.hpp"
#include<string.h>
#include"button.h"
#include <Windows.h>
#include <time.h>
#include "Icon.h"

namespace udh
{
	class inputField
	{
		std::string text; 
		
		sf::Font font;
		int creationDay;
	public:
		sf::RectangleShape crossline;
		bool completed = false;
		udh::Button done;
		udh::Button del;
		udh::Button edit;
		sf::Texture del_tex, edit_tex;
		Icon del_icon, edit_icon;
		sf::Text textdata;
		inputField();

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

		void setstatus(bool a)
		{
			this->completed = a;
		}

		void setCreationTime();

		bool getstatus();

		int getDay();

		void setday(int a);

		
	};

	/// <summary>
	/// draw all the tasklist
	/// </summary>
	/// <param name="textlist">A vector containing inputfield objects to draw</param>
	/// <param name="window">A refrence of type Renderwindow to draw the list into</param>
	void drawlist(std::vector<udh::inputField>& textlist, sf::RenderWindow* window);

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
		std::vector<udh::inputField>::iterator& itredit, udh::inputField& sample, udh::Button& textarea);

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
	void addTask(udh::inputField& sampletext, std::string& a, sf::Event event, std::vector<udh::inputField>& textlist, udh::Button textarea);
}
#endif // !INPUT_FIELD