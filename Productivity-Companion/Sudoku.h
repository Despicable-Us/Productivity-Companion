#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "Btn.h"

#define B_WIDTH 54.f
#define B_HEIGHT 54.f
#define CANVAS_W 496.f
#define CANVAS_H 496.f
#define TOGGLER_C_R 15.f
#define TOGGLER_WIDTH 30.f

class Box
{
	public:
		sf::RectangleShape shape;
		sf::Font roboto_font;
		sf::Text text;
		bool fixed;
		bool wrong;

		Box();
		Box(sf::Font*, float, float);

		void Set_Text_Size(int);
};

class Bar
{
	public:
		sf::RectangleShape line_shape;
		Bar();
		Bar(int, int, float, float);
};


class Sudoku
{
	public:
		// CONSTRUCTORS and DESTRUCTORS
		Sudoku();
		~Sudoku();

		// UI COMPONENTS
		sf::RectangleShape canvas;
		sf::Font roboto_font;
		sf::Font kaushan_font;
		sf::Text assist_text;
		sf::Texture background_tex;
		sf::Sprite background;

		// TOGGLER
		sf::RectangleShape main_rect;
		sf::CircleShape rect_circle;
		sf::CircleShape c_left, c_right;


		// COMPONETNS
		sf::Vector2f mouse_pos;
		sf::Vector2f selected_num_pad_pos;
		sf::Vector2f selected_bos_pos;
		std::string selected_num_pad;
		std::string selected_box_string;
		sf::Vector2i selected_cell_pos;


		int prev_NP_x;
		int prev_NP_y;
		int prev_box_x;
		int prev_box_y;
		int x, y;
		bool mouse_held;
		bool selected;
		bool value_inserted_in_cell;
		bool assists;
		bool toggler_held;
		Btn* remove_btn;

		// CONTAINERS
		std::vector<Bar> Bars;
		std::vector<std::vector<Box>> Boxes;
		std::vector<std::vector<int>> sudoku;
		std::vector<std::vector<std::string>> solved;
		std::vector<std::vector<std::string>> check_box;
		std::vector<std::vector<Box>> Num_Pads;

		// LOADER FUNCTIONS
		void Load_Containers();
		void Load_UI_Components();
		void Load_Boxes();
		void Load_Font();
		void Load_Toggler();

		// HELPER && EVENT FUNCTIONS
		void Run_Events(sf::RenderWindow& , sf::Event );
		void Run_Num_Pads_Events(sf::RenderWindow&, sf::Event);
		void Run_Box_Events(sf::RenderWindow&, sf::Event);
		void Run_Other_Events(sf::Event);
		void Run_Toggler_Event(sf::Event);
		bool Detect_Click(sf::Vector2f m_click, sf::Vector2f entity_click, sf::Vector2f DMNS);
		void Color_Boxes_On_Select(int i, int j, bool clear);
		void Same_Cell_Update(std::string item);
		void Clear_Box_Color();
		void Check_Wrong_Inputs();
		void Undo_Wrong_Highlight();
		std::function<void()> remove_btn_func;

		// SUDOKU GENERATOR
		void Generate_Sudoku();
		std::vector<int> rem;
		int random_int;
		bool Solve_Sudoku(std::vector<std::vector<int>>&);
		bool Find_Zero(std::vector<std::vector<int>>, int&, int&);
		bool Safe_To_Assign(std::vector<std::vector<int>> graph, int i, int j, int num);
		bool Compare(std::vector<std::vector<int>> test1, std::vector<std::vector<int>> test2);
		std::vector<std::vector<int>> copy_sudoku;
		std::vector<std::vector<int>> copy_vec;
		void Find_Random_Pos(std::vector<std::vector<int>> graph, int& r, int& c);


		// RENDERING 
		void Render_To_Main_Window(sf::RenderWindow& );
};