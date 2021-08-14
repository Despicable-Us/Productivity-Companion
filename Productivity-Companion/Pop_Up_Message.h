#pragma once
#include "SFML/Graphics.hpp"
#include "Btn.h"
#include "InputField.h"

class Pop_Up_Message
{
	public:
		// CONSTRUCTORS AND DESTRUCTORS
		Pop_Up_Message();
		Pop_Up_Message(std::string, sf::Font&);
		~Pop_Up_Message();

		// BUTTON AND FIELD 
		Btn* cancel_btn, *confirm_btn;
		InputField* field;
		sf::Font roboto_font;

		// DIMENSION COMPONENTS
		float rect_w, rect_h;
		float circle_radius;
		sf::Vector2f rect_pos;
		sf::Vector2f rect_size;
		sf::Vector2f circle_origin;

		// UI DESIGN COMPONENTS
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

		// ACCESSORS
		sf::Vector2f main_rect_pos;
		sf::Vector2f main_rect_size;
		std::string session_name;

		// HELPER FUNCTION
		void Load_Font();
		void Set_Components();
		void Set_Dimension();
		void Set_Button_And_InputField();
		void Set_Text_Font();

		// UPDATE AND RENDER
		void Draw_To(sf::RenderWindow& window);
		
		// UI TEXT
		sf::Text sure_text;
		sf::Text confirm_text;

		void Run_Inside_Event(sf::RenderWindow& window, sf::Event& event);
		void Run_Outside_Event(sf::RenderWindow& window, sf::Event& event, bool& show_btn, bool& show_pop_up, bool& delete_db_data);
		void Set_Session_Name(std::string);

		// LAMBDA EXPRESSIONS, BOOLEAN AND STRINGS
		std::function<void()> input_func;
		std::function<void()> confirm_func;
		std::function<void()> cancel_func;
		std::string input_field_string;
		bool* overlay, * popup, *run_delete;
};