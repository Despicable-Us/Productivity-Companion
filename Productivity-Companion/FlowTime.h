#pragma once

#include "SFML/Graphics.hpp"
#include "Btn.h"
#include "InputField.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <functional>
#include "sqlite3.h"
#include <string.h>
#define BLUE_THEMED_C 23, 137, 252

class FlowTime
{
	public:
		// CONSTRUCTORS and DESTRUCTORS
		FlowTime();
		FlowTime(sf::RenderWindow& window);
		~FlowTime();

		// UI COMPONENTS
		sf::Texture texture;
		sf::Sprite background;
		sf::RectangleShape rect;

		// BUTTONS and INPUTFIELD and RELATED EVENTS
		Btn* add_flowtime_btn;
		InputField* input_flowtime_field;
		std::function<void()> btn_event_func;

		// COMPONENTS CONTAINER
		std::vector<sf::RectangleShape> rects;
		std::vector<sf::Text> text_vec;
		std::vector<std::string> input_texts;

		// UI TYPOGRAPHY
		sf::Font kaushan_font;
		sf::Font roboto_font;
		sf::Text test_text;

		// DATA ACCESSORS
		sf::Vector2u win_size;
		sf::Vector2f win_sizeF;

		// BOOLEAN DATA COMPONENTS AND METHODS
		bool btn_hide;
		bool input_hide;
		bool enter_pressed;

		// CUSTOM FUNCTIONS 
		std::function<void()> add_rect;
		std::function<void()> add_session_tab;

		// INITIALIZERS and UPDATERS
		void Init_Variables();
		void Init_Background();
		void Init_UI_Font();
		void Init_UI_Components();

		// EVENTS
		void Run_Inside_Event(sf::RenderWindow& window, sf::Event& event, sf::View& view);
		void Run_Outside_Event(sf::RenderWindow& window, sf::Event& event, bool& run_main_window, bool& run_app);
		void Render_In_Main_Window(sf::RenderWindow& window);
		void Render_In_View(sf::RenderWindow& window);


};

