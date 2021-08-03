#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "inputField.h"
#include<iostream>
#include<vector>
#include "button.h"
#include "Database.h"

extern std::vector<udh::inputField> textList;
extern udh::inputField sampletext;
//extern sf::View scroll_view;
extern int viewPos;


#define TEXTAREA_HEIGHT 130.f

class TodoList
{
	//sf::View TaskView;
	sf::RectangleShape scrollBar;
	sf::CircleShape c1, c2;
	sf::Font  fonts;
	std::vector<udh::inputField>::iterator editTaskItr;
	sf::Texture cover;
	sf::Sprite TodoImage;
	udh::Button textarea;
	std::string a;
public:
	TodoList();
	void LoadTodoList();
	void RunTodo(sf::RenderWindow& window, sf::Event event, sf::View&);
	void DrawTodoMainWindow(sf::RenderWindow& window);
	void DrawTodoView(sf::RenderWindow& window);
};