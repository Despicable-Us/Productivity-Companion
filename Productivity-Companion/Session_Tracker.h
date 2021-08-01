#pragma once
#include "SFML/Graphics.hpp"
#include "Btn.h"
#include "InputField.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <functional>
#include "Session.h"
#include "sqlite3.h"
#include <string.h>
#include "Pop_Up_Message.h"

#define BORDER_RADIUS 15.f;
#define BLUE_THEMED_C 23, 137, 252

class Session_Tab
{
	public:
		// CONSTRUCTORS AND DESTRUCTORS;
		Session_Tab();
		Session_Tab(std::string name, sf::Vector2f pos, sf::Vector2f size, sf::Font& font);
		~Session_Tab();

		// UI COMPONENTS
		Btn* session_btn;
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
		sf::Text total_time_info;

		// ACCESSORS
		sf::Vector2f main_rect_pos;
		sf::Vector2f main_rect_size;
		std::string session_name;

		// HELPER FUNCTION
		void Set_Components();
		void Set_Dimension();
		void Set_Button();

		// UPDATE AND RENDER
		void Draw_To(sf::RenderWindow& window);
		void Set_Total_Time_Text(std::string);

		Btn* delete_btn;
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

		// BUTTONS and INPUTFIELD and RELATED EVENTS
		Btn* add_session_btn;
		InputField* input_session_field;
		std::function<void()> btn_event_func;
		std::function<void()> delete_event_func;

		// COMPONENTS CONTAINER
		std::vector<sf::RectangleShape> rects;
		std::vector<sf::Text> text_vec;
		std::vector<std::string> input_texts;

		// SESSION VIEW COMPONENTS
		Session_Tab session_tab;
		std::vector<Session_Tab> session_tab_vec;

		// SESSION TAB COMPONENT DIMENSION AND POSITION
		sf::Vector2f initial_pos;
		sf::Vector2f session_tab_size;

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
		bool btn_show;
		bool update_total_time_list;

		// CUSTOM FUNCTIONS 
		std::function<void()> add_rect;
		std::function<void()> add_session_tab;

		// INITIALIZERS and UPDATERS
		void Init_Variables();
		void Init_Background();
		void Init_UI_Font();
		void Init_UI_Components();
		void Update_Rects();
		void Update_Rects_After_DB();
		void Alter_Session_Tab_View();

		// EVENTS
		void Run_Inside_Event(sf::RenderWindow& window, sf::Event& event, sf::View& view);
		void Run_Outside_Event(sf::RenderWindow& window, sf::Event& event);
		void Render_In_Main_Window(sf::RenderWindow& window);
		void Render_In_View(sf::RenderWindow& window);

		// SESSION
		Session* session;
		bool show_session;
		bool show_session_tab;
		std::vector<std::string> new_added_session;
		void Get_DB_Data();
		void Update_DB_Data();
		const char* dir;
		std::string selected_session_name;

		void Set_DB_Data_To_View();
		void Set_DB_Total_Time_List();
		sf::RectangleShape blur_overlay;
		bool show_blur_overlay;

		// POP UP MESSAGE
		Pop_Up_Message* pop_up;
		bool show_pop_up;
		bool delete_db_data;
};

// DATABASE RELATED
namespace session_tracker
{
	static int callback(void*, int, char**, char**);
	static int select_data(const char*);
	static int insert_data(const char*);
	static int fetch_total_time_list(const char*, std::string);
	static int call_back_total_time_list(void*, int, char**, char**);
	static int delete_session_tab(const char*, std::string);
	static int insert_new_session(const char*, std::string);
}