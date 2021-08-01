#pragma once
#include "SFML/Graphics.hpp"
#include <stdc++.h>
#include "Btn.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <sqlite3.h>
#include <chrono>
#include <ctime>
#include <time.h>

#define TEXT_CHAR_SIZE 16
#define DETAIL_BAR_WIDTH 700.f
#define DATE_BAR_WIDTH 300.f
#define RECT_H 30.f
#define CIRCLE_R 15.f
#define TIME_STAMP_POSX 30.f
#define TIME_DURATION_POSX 510.f
#define DATE_TEXT_POSX 70.f
#define DATE_TEXT_POSY_OFFSET 3.f
#define BG_NAME_CIRCLE_R 6.f
#define TRACKER_CIRCLE_R 5.f

#define DETAIL_BAR_C 230, 230, 230
#define DATE_BAR_C 41, 41, 41
#define BG_CIRCLE_FILL_C 8, 218, 145
#define START_BTN_COLOR 24, 171, 14
#define STOP_BTN_COLOR 247, 12, 55

class Record
{
	public:
		// DESIGN 
		sf::RectangleShape rect;
		sf::CircleShape c_left, c_right;
		sf::Font font;
		sf::Text time_stamp_text;
		sf::Text time_duration_text;
		sf::Text date_text;

		// DATA
		std::vector<std::string> record_data;
		sf::Vector2f rect_pos;
		sf::FloatRect rect_bounds;
		sf::FloatRect time_stamp_bounds;
		sf::FloatRect time_duration_bounds;

		// BASIC
		float rect_w, rect_h, circle_radius;
		bool is_bar = false;
		bool date_bar;

		// CONSTRUCTORS 
		Record();
		Record(sf::Font& f, bool is_date = 0);
		void Set_Text(std::vector<std::string> data);
		void Set_Text(std::string data);
		void Set_Rect_Position(sf::Vector2f pos);
		void Draw_To(sf::RenderWindow& window);
};

// Date in string to vector of integer converter
std::vector<int> Convert_Date_To_Vec(std::string date_string);

// A comparator class supplied to the map 
// to sort the map according to the key i.e. date
class Comparator_Func
{
	public:
		bool operator()(const std::string& first, const std::string& second) const;
};

class Session
{
	public:
		// WINDOW PROPERTIES
		sf::RenderWindow window;
		sf::Vector2u win_size;
		sf::Vector2f win_sizeF;
		sf::Vector2f win_center;

		// Loading TEXTURE, SPRITE, FONT
		sf::Texture bg_image_tex, bg_stop_tex;
		sf::Font kaushan_font, roboto_font;
		sf::Sprite bg_image, bg_stop_image;

		// BACKGROUND Name and design
		sf::Text session_text;
		sf::CircleShape circle;

		// UI Components
		Btn* toggle_btn;
		Btn* home_btn;
		bool home_btn_clicked;
		bool btn_color_toggle;
		std::string session_name;
		sf::RectangleShape scroll_bar;
		bool show_scroll_bar;

		// CLOCK 
		sf::Clock clock;
		sf::Text timer_text, tracker_text, designate_time_text;
		sf::CircleShape tracking_shape;
		std::string time_to_str;
		int seconds = 0;
		int mili_sec = 0;
		int ms = 0;
		float t1;
		sf::Int32 t2;
		bool timer_on;
		bool show_timer;

		// RECORDS and its Components
		Record detail_record, date_record;
		std::vector<Record> records_table;
		std::string date_string;
		std::ostringstream ss;
		std::vector<std::string> time_data;

		// TIME DATA (interval, date)
		std::string start_time;
		std::string end_time;
		std::string mS;
		std::string hours;
		std::string minutes;
		std::string duration;
		std::string start_timer;
		std::string end_timer;
		std::string timer_string;

		// WRAPPER FUNCTION for Button
		std::function<void()> Btn_Trigger;
		std::function<void()> Home_Btn_Trigger;

		// CONSTRUCTORS
		Session();
		Session(sf::RenderWindow& window, std::string name);

		// INITIALITERS and LOADERS
		void Init_Variables();
		void Load_Tex_Font();
		void Set_Bg_Images_Pos();
		void load_session_name();
		void Init_UI_Components();
		void Create_Toggle_Btn();
		void Load_Clock_Components(); 
		void Today_Date();
		void Create_Home_Btn();
		void Get_DB_Data();
		void Update_DB_Data();
		void Run_Functions(std::string name);

		// HELPER COMPONENTS FOR DB
		std::map<std::string, std::vector<std::vector<std::string>>, Comparator_Func> data_to_map;
		std::map<std::string, std::vector<std::vector<std::string>>>::iterator it;
		std::vector<std::vector<std::string>> added_vectors;
		const char* dir;

		// PARSER FUNCTIONS
		void Map_To_Records_Vec();
		std::string Timer_Duration(std::vector<int> start, std::vector<int> end);
		std::vector<int> Convert_Data(std::string data_time);

		// RUNNING EVENTS
		void Run_Events(sf::RenderWindow& window, sf::Event& event, bool& show_session, bool& show_button, bool& update_total_time_list);
		void Timer_Run_Event();
		void View_Scroll_Event(sf::Event& event, sf::View& scroll_view);

		// RENDERER
		void Draw_To_View(sf::RenderWindow& window);
		void Draw_To_Main_Window(sf::RenderWindow& window);

		void Reset_Scroll_Bar_And_View(sf::View& view);
		bool reset_view;
};

// DATABASE HELPER FUNCTION
std::vector<std::string> string_to_2dVec_parser(char* row);

namespace session_detail
{
	static int callback(void*, int, char**, char**);
	static int insert_data(const char* s, std::string total_time);
	static int select_data(const char* s, std::string selected_data);
}
