#pragma once
#include "SFML/Graphics.hpp"
#include "Btn.h"
#include "InputField.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <functional>

#define CIRCLE_R 15.f;

class Session_Tab
{
	public:
		// CONSTRUCTORS AND DESTRUCTORS;
		Session_Tab(){}
		Session_Tab(std::string name, sf::Vector2f pos, sf::Vector2f size, sf::Font& font);
		~Session_Tab();

		// UI COMPONENTS
		Btn* session_btn;
		sf::Font roboto_font;

		float rect_w, rect_h;
		float circle_radius;
		sf::Vector2f rect_pos;
		sf::Vector2f rect_size;
		sf::Vector2f circle_origin;

		sf::Color background_color;
		sf::RectangleShape main_rect;
		sf::RectangleShape up_rect;
		sf::RectangleShape left_rect;
		sf::RectangleShape right_rect;
		sf::RectangleShape bottom_rect;
		sf::CircleShape c_top_left;
		sf::CircleShape c_top_right;
		sf::CircleShape c_bottom_left;
		sf::CircleShape c_bottom_right;
		std::string session_name;

		// ACCESSORS
		sf::Vector2f main_rect_pos;
		sf::Vector2f main_rect_size;

		// HELPER FUNCTION
		void Set_Components();
		void Set_Dimension();
		void Set_Button();

		// UPDATE AND RENDER
		void Draw_To(sf::RenderWindow& window);
};


class Session_Tracker
{
	public:
		// CONSTRUCTORS and DESTRUCTORS
		Session_Tracker(sf::RenderWindow& window);
		~Session_Tracker();

		// UI Components
		sf::Texture texture;
		sf::Sprite background;
		sf::RectangleShape rect;

		// BUTTONS and INPUTFIELD
		Btn* add_session_btn;
		InputField* input_session_field;
		std::function<void()> btn_event_func;
		std::vector<std::function<void()>> all_btn_event_func;

		// COMPONENTS CONTAINER
		std::vector<sf::RectangleShape> rects;
		std::vector<sf::Text> text_vec;
		std::vector<std::string> input_texts;
		std::vector<Session_Tab> session_tab_vec;
		std::vector<std::vector<Session_Tab>> session_tab_container;
		Session_Tab session_tab;

		// SESSION TAB HELPERS
		sf::Vector2f initial_pos;
		sf::Vector2f session_tab_size;

		// UI TYPOGRAPHY
		sf::Font kaushan_font;
		sf::Font roboto_font;
		sf::Text ui_text;
		sf::Text test_text;
		std::vector<sf::Text> al_UI_text;

		// DATA ACCESSORS
		sf::Vector2u win_size;
		sf::Vector2f win_sizeF;

		// BOOLEAN DATA COMPONENTS AND METHODS
		std::function<void()> add_rect;
		std::function<void()> add_session_tab;
		bool btn_hide;
		bool input_hide;

		// INITIALIZERS
		void Init_Variables();
		void Init_Background();
		void Init_UI_Font();
		void Init_UI_Components();
		void Update_Rects();

		bool enter_pressed;

		void Test_Session_Tab_View();

		// EVENTS
		void Run_InputField_Event(sf::RenderWindow& window, sf::Event& event);
		void Run_Btn_Event(sf::RenderWindow& window, sf::Event& event);

		void Render_In_Main_Window(sf::RenderWindow& window);
		void Render_In_View(sf::RenderWindow& window);
};

