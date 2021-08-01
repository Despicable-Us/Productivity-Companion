#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "inputField.h"
#include<iostream>
#include<vector>
#include "button.h"
#include "Database.h"
std::vector<udh::inputField> textList;
udh::inputField sampletext;
int viewPos;
class TodoList
{
	sf::ContextSettings settings;
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
	TodoList() :c1(15.f), c2(15.f), TaskView({ 0.f,0.f,760.f,675.f }),
		window(sf::VideoMode(760, 675), "My Todos", sf::Style::Titlebar | sf::Style::Close, settings),
		textarea("add task", { 580.f,30.f }, { 80.f,180 }, fonts)
	{
	
	}
};