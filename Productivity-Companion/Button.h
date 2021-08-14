#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include <functional>
#include <iostream>
/*
	Simple and elegant way to create a button in SFML
	Uses the sf::RectangleShape and the sf::Text class
*/
namespace udh
{

	class Button
	{
	private:
		sf::RectangleShape shape;//rectangle body of button
		sf::Text text;//text to be shown in the button
		std::string btnText;//string of the text to be shown in button
		sf::FloatRect btnRect;//floatrect to set the button
		bool state = false;//stores the state if button is clicked or not
		bool editing = false;//checks if task is being edited or not
		bool adding = false;// checks if new task is being added or not
	public:

		/// <summary>
		/// default constructor
		/// </summary>
		Button();

		/// <summary>
		/// parameterized constructor with font as parameter
		/// </summary>
		/// <param name="font">font for the text to be displayed in button</param>
		Button(sf::Font& font);

		/// <summary>
		/// Overloaded BUTTON constructor
		/// </summary>
		/// <param name="btnText">The string to be written in the button itself</param>
		/// <param name="btnDmn">The dimension / size of the button to be specified</param>
		/// <param name="btnPos">The sf::Vector2f position of the button in the rendered window</param>
		/// <param name="font">The font of the text within the button</param>
		Button(std::string btnText, sf::Vector2f btnDmn, sf::Vector2f btnPos,sf::Font& font);

		/// <summary>
		/// method to set the bounbdary of the button
		/// </summary>
		/// <param name="rec">sf::FloatRect describing boundary of button</param>
		void setbtnRect(sf::FloatRect rec);
		
		/// <summary>
		///method to set seze of the button 
		/// </summary>
		/// <param name="sizeF">sf::Vector2f The dimension / size of the button</param>
		void setBtnSize(sf::Vector2f sizeF);

		/// <summary>
		/// method to set the position of the button within the rendered window
		/// </summary>
		/// <param name="pos">Vector2f as the position with respect to the rendered window</param>
		void setBtnPosition(sf::Vector2f pos);

		/// <summary>
		/// method to set the character size of the text in the button
		/// </summary>
		/// <param name="size">Unsigned INT_8 bit value for the Char size</param>
		void setTextSize(uint8_t size);

		/// <summary>
		/// method to set the color of the text in the button
		/// </summary>
		/// <param name="color"> sf::Color which takes RGA colorspace values</param>
		void setTextColor(sf::Color color);

		/// <summary>
		/// method to set the font of the text in the button
		/// </summary>
		/// <param name="font">&font A reference to the sf::Font</param>
		void setBtnTextFont(sf::Font& font);

		/// <summary>
		/// method to set Text Position  within the button
		/// </summary>
		void setTextPos();

		/// <summary>
		/// method to set the buttonm text as given in parameter
		/// </summary>
		/// <param name="a">const char* to set as button text</param>
		void setbtntext(const char* a);

		/// <summary>
		/// sets editing to true
		/// </summary>
		void setEditing();

		/// <summary>
		/// sets editing to false
		/// </summary>
		void unsetEditing();

		/// <summary>
		/// method to draw the components of button into given window
		/// </summary>
		/// <param name="window">window to draw the button into</param>
		void drawTo(sf::RenderWindow& window);

		/// <summary>
		/// method to set the color of the button rectangle
		/// </summary>
		/// <param name="color">sf::Color</param>
		void setbtncolor(sf::Color color);
		

		/// <summary>
		/// method top set the state of button true
		/// </summary>
		void setpressed();

		/// <summary>
		/// method to set the state of button false and button text to "Add Task"
		/// </summary>
		void releasePressed();

		/// <summary>
		/// method to get boundary of the button
		/// </summary>
		/// <returns>Global bounding rectangle of the button</returns>
		sf::FloatRect getbounds();

		/// <summary>
		/// method to get position of button
		/// </summary>
		/// <returns>coordinate to the current position of the button</returns>
		sf::Vector2f getPosition();

		/// <summary>
		/// member function
		/// </summary>
		/// <returns>state of the button</returns>
		bool getstate();

		/// <summary>
		/// member function
		/// </summary>
		/// <returns>bool wheter task is being edited or not</returns>
		bool IsEditing();

		/// <summary>
		/// method to check if the button is clicked and sets state to true if the button was clicked
		/// </summary>
		/// <param name="event">sf::Event containing the user event</param>
		/// <param name="window">refrence of renderwindow where event was carried out</param>
		/// <returns>state of the button</returns>
		bool isclicked(sf::Event event, sf::RenderWindow& window);

		/// <summary>
		/// method to set the state to true if the button is clicked and remove button text
		/// </summary>
		/// <param name="event">sf::Event containing the user event</param>
		/// <param name="window">refrence of renderwindow where event was carried out</param>
		/// <returns>state of the button</returns>
		bool ispressed(sf::Event event, sf::RenderWindow& window);

		/// <summary>
		/// method to set the outline of the button
		/// </summary>
		/// <param name="col">sf::Color value of color to set outline to</param>
		/// <param name="width">width of the outline</param>
		void setoutline(sf::Color col, int width);

		/// <summary>
		/// member function
		/// </summary>
		/// <returns>bool whether task is being added or not</returns>
		bool getAdding();

		/// <summary>
		/// method to set adding to true (that tells task is being added)
		/// </summary>
		void setAddding();

		/// <summary>
		/// method to set adding to false (tells adding task is completed)
		/// </summary>
		void unSetAdding();
	};
}

#endif