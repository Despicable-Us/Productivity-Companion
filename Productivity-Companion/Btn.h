#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <ctime>
#include <functional>

class Btn
{
	public:
		// COMPONENTS FOR SHAPE
		sf::RectangleShape shape;
		sf::CircleShape C1, C2;
		sf::Text text;
		sf::Font uiFont;

		// CONTAINERS AND BOUNDS
		sf::Vector2f inputBtnPos;
		sf::FloatRect textBounds;
		sf::FloatRect shapeBounds;
		sf::Vector2i mousePos;
		sf::Vector2f mousePosView;
		sf::FloatRect wholeBtnRect;

		// STRING DATATYPES
		std::string btnText;
		std::string btnId;

		// INITIALIZERS
		float fixFactor = 4.5f;
		float btnScale = 1.02f;
		uint8_t charSize = 0;

		// BOOLEAN DATA MEMBERS
		bool mouseInside = false;
		bool mouseHeld = false;

		int btnClickedStatus;

		// CONSTRUCTORS AND DESTRUCTOR
		Btn(){}
		Btn(std::string BtnText, sf::Vector2f btnPos, uint8_t charSize, sf::Font& font, const std::string& id = "");
		~Btn(){}

		// REQUIRED LOADERS AND HELPER FUNCTIONS
		void LoadText();
		void SetBtnShape();
		void SetBtnPosition(sf::Vector2f pos);
		void SetText();
		void SetBtnRect();
		void SetFillColor(sf::Color color);
		void SetTextColor(sf::Color color);
		void hoverEffect(bool);
		void checkClicked(sf::RenderWindow&, sf::Event&);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, bool &btnHide);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, std::string name, std::string& selected_session_name);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, bool& btn_show);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, bool& first, bool& second);
		std::string BtnEvents(sf::RenderWindow& window, sf::Event& event);

		// RENDER FUNCTION
		void DrawTo(sf::RenderWindow &window);
};

#endif