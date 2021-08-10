#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "InputTodo.h"
#include<iostream>
#include<vector>
#include "button.h"
#include "Database.h"
#include "Btn.h"
#include <functional>

extern std::vector<udh::inputField> textList;
extern std::vector<udh::inputField> completed;
extern udh::inputField sampletext;
extern int viewPos;

#define TEXTAREA_HEIGHT 125.f

class TodoList
{
	sf::RectangleShape scrollBar;
	sf::CircleShape c1, c2;
	sf::Font fonts, roboto_font;
	std::vector<udh::inputField>::iterator editTaskItr;
	sf::Texture cover;
	sf::Sprite TodoImage;
	udh::Button textarea;
	std::string a;
public:

	Btn* home_back_btn;
	std::function<void()> home_back_btn_func;
	bool home_back_btn_clicked;
	sf::Text background_text;
	std::string plan_sheet_name;
	bool is_planner_sheet;

	TodoList();
	TodoList(std::string);
	void Reset_Functions(std::string);
	void LoadDB();
	void LoadTodoList();
	void RunTodo(sf::RenderWindow& window, sf::Event event, sf::View&, bool&, bool&);
	void DrawTodoMainWindow(sf::RenderWindow& window);
	void DrawTodoView(sf::RenderWindow& window);
	void Update_DB();
};