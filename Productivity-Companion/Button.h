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
		sf::RectangleShape shape;
		sf::Text text;
		std::string btnText;
		sf::FloatRect btnRect;
		bool state = false;
		bool editing = false;
		bool adding = false;
	public:
		Button();
		Button(sf::Font& font);
		Button(std::string btnText, sf::Vector2f btnDmn, sf::Vector2f btnPos,
			sf::Font& font);
		void setbtnRect(sf::FloatRect rec);
		void setBtnSize(sf::Vector2f sizeF);
		void setBtnPosition(sf::Vector2f pos);
		void setTextSize(uint8_t size);
		void setTextColor(sf::Color color);
		void setBtnTextFont(sf::Font& font);
		void setTextPos();
		void setbtntext(const char* a);
		void setEditing();
		void unsetEditing();
		void drawTo(sf::RenderWindow& window);
		void setbtncolor(sf::Color color);
		void btnEvents(sf::Event& event, sf::RenderWindow& window, std::function<void()> func);
		void setpressed();
		void releasePressed();
		sf::FloatRect getbounds();
		sf::Vector2f getPosition();
		bool getstate();
		bool IsEditing();
		bool isclicked(sf::Event event, sf::RenderWindow& window);
		bool ispressed(sf::Event event, sf::RenderWindow& window);
		void setoutline(sf::Color col, int width);
		bool getAdding();
		void setAddding();
		void unSetAdding();
	};
}

#endif 
