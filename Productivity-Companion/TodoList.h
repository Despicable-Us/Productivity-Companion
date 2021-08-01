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
extern int viewPos;
class TodoList
{
	sf::View TaskView;
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
	void RunTodo(sf::RenderWindow& window, sf::Event event);
	void DrawTodo(sf::RenderWindow& window);
};