#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <functional>
#include <ctime>

class InputField
{
	public:
		// UI COMPONENTS
		sf::RectangleShape shape;
		sf::CircleShape Cleft, Cright;
		sf::Text text;
		sf::Font inputFont;

		// SUPPORTING DATA MEMBERS
		std::string inputText;
		std::string bufferString;
		std::string savedString;
		size_t charSize = 16;
		float fieldWidth = 180.f;
		float padX = 14.f;
		float padY = 5.f;
		
		// BOOLEAN DATA MEMBERS
		bool isFocused = false;
		bool mouseHeld = false;

		// STL CONTAINERS AND RECTS
		sf::Vector2i mousePos;
		sf::Vector2f mousePosView;
		sf::Vector2f inputFieldPos;
		sf::Vector2f rectSize;
		sf::FloatRect textBounds;
		sf::FloatRect wholeInputRect;
		sf::FloatRect rectBounds;

		// CONSTRUCTORS AND DESTRUCTOR
		InputField() {} // default 
		InputField(sf::Vector2f fieldPos, sf::Font& font);
		~InputField() {}

		// HELPER, LOADER, EVENT HANDLERS, UPDATERS, RENDERERS
		void LoadText();
		void SetText(std::string inText);
		void CreateInputShape();
		void SetWholeRect();
		void InputEvent(sf::RenderWindow& window, sf::Event& event, bool& inputHide, bool& btnHide, std::vector<std::string>& inputTexts,bool& enter_pressed);
		void InputEvent(sf::RenderWindow& window, sf::Event& event, std::function<void()> func);
		void InputEvent(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, std::string& entered_field_string);
		void DrawTo(sf::RenderWindow& window);
};