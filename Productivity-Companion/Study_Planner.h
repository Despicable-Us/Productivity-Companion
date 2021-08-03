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
#include "TodoList.h"

#define BORDER_RADIUS_S 15.f;
#define ADD_COLOR 231, 60, 60
#define APP_THEME_COLOR 236,155,0
//242, 90, 78
class Planner_Tab
{
	public:
		// CONSTRUCTORS AND DESTRUCTORS;
		Planner_Tab();
		Planner_Tab(std::string name, sf::Vector2f pos, sf::Vector2f size, sf::Font& font);
		~Planner_Tab();

		// UI COMPONENTS
		Btn* planner_btn;
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
		std::string plan_sheet_name;

		// HELPER FUNCTION
		void Set_Components();
		void Set_Dimension();
		void Set_Button();

		// UPDATE AND RENDER
		void Draw_To(sf::RenderWindow& window);

		Btn* delete_btn;
};


class Study_Planner
{
	public:
		// CONSTRUCTORS AND DESTRUCTORS
		Study_Planner();
		Study_Planner(sf::RenderWindow& window);
		~Study_Planner();

		// UI Components
		sf::Texture texture;
		sf::Sprite background;
		sf::RectangleShape rect;

		// BUTTONS and INPUTFIELD and RELATED EVENTS
		Btn* add_planner_btn;
		InputField* input_planner_field;
		std::function<void()> btn_event_func;
		std::function<void()> delete_event_func;

		// COMPONENTS CONTAINER
		std::vector<sf::RectangleShape> rects;
		std::vector<sf::Text> text_vec;
		std::vector<std::string> input_texts;

		// PLAN SHEET VIEW COMPONENTS
		Planner_Tab planner_tab;
		std::vector<Planner_Tab> planner_tab_vec;

		// PLANNER TAB COMPONENT DIMENSION AND POSITION
		sf::Vector2f initial_pos;
		sf::Vector2f planner_tab_size;

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
		//bool update_total_time_list;

		// CUSTOM FUNCTIONS 
		std::function<void()> add_rect;
		std::function<void()> add_planner_tab;

		// INITIALIZERS and UPDATERS
		void Init_Variables();
		void Init_Background();
		void Init_UI_Font();
		void Init_UI_Components();
		void Update_Rects();
		void Update_Rects_After_DB();
		void Alter_Planner_Tab_View();

		// EVENTS
		void Run_Inside_Event(sf::RenderWindow& window, sf::Event& event, sf::View& view);
		void Run_Outside_Event(sf::RenderWindow& window, sf::Event& event);
		void Render_In_Main_Window(sf::RenderWindow& window);
		void Render_In_View(sf::RenderWindow& window);

		// POP UP MESSAGE
		Pop_Up_Message* pop_up;
		bool show_pop_up;
		bool delete_db_data;
		sf::RectangleShape blur_overlay;
		bool show_blur_overlay;

		// TODO LIST PART
		TodoList *plan_sheet;
		bool show_planner_list;
		bool show_planner_tab;
		std::vector<std::string> new_added_plan_sheet;
		void Get_DB_Data();
		void Update_DB_Data();
		const char* dir;
		std::string selected_planner_sheet_name;

};

namespace study_planner
{
	static int callback(void*, int, char**, char**);
	static int select_data(const char*);
	static int insert_data(const char*);
	static int delete_planner_tab(const char*, std::string);
	static int insert_new_plan_sheet(const char*, std::string);
}
