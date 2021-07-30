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
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(760, 675), "My Todos",sf::Style::Titlebar|sf::Style::Close,settings);
	sf::View TaskView({0.f,0.f,760.f,675.f});
	sf::RectangleShape scrollBar;
	sf::CircleShape c1(15.f), c2(15.f);
	c1.setFillColor(sf::Color(235, 235, 235));
	c2.setFillColor(sf::Color(235, 235, 235));
	c1.setPosition(65.f, 180.f);
	c2.setPosition(645.f, 180.f);
	scrollBar.setPosition(741,169);
	std::vector<udh::inputField>::iterator editTaskItr;
	sf::Font  fonts;
	fonts.loadFromFile("Fonts\\KaushanScript-Regular.ttf");
	/////////////////////////////////////////////////////////
	// Backgound for Todo
	sf::Texture cover;
	if (!cover.loadFromFile("./TextureImages/TodoTexture1.jpg"))
	{
		std::cerr << "error loading texture\n";
	}
	sf::Sprite TodoImage;
	TodoImage.setTexture(cover);
	int x, y;
	x = cover.getSize().x;
	y = cover.getSize().y;
	std::cout <<"\ny=" <<y<<"\n";
	TodoImage.setTextureRect({0,0,x,y});
	TodoImage.setScale(0.75,0.39);

	
	udh::Button textarea("add task", { 580.f,30.f }, { 80.f,180 }, fonts);
	TaskView.setViewport({0.f,0.3259,1.f,1.f});
	std::string a;
	sf::Event event;

	//adjusting position of input text wrt to input text area.
	sampletext.setposition(sf::Vector2f(textarea.getbounds().left + 20,
		textarea.getPosition().y));
	////////////////////////////////////////////////////////////////
	//database creating and loading
	udh::createDB("Productivity_companion.db");
	udh::createTaskTable("Productivity_companion.db");
	udh::LoadTaskList("Productivity_companion.db");
	std::cout << "\nsize:" << textList.size()<<"\n";
	sampletext.setdata("");
	sampletext.setstatus(false);
	///////////////////////////////////////////////////////////////
	//main loop or game loop
	while (window.isOpen())
	{
		//if window gets an event
		while (window.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				int size= textList.size()*50;
				while (!event.KeyReleased)
				{
					continue;
				}
				if (viewPos < size - 455)
				{
					TaskView.move(0.f, 50.f);
					viewPos += 50;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				while (!event.KeyReleased)
				{
					continue;
				}
				if (viewPos != 0)
				{
					TaskView.move(0.f, -50.f);
					viewPos -= 50;
				}
			}
			//checking of close button is cliked
			if (event.type == sf::Event::Closed)
			{
				udh::deleteData("Productivity_companion.db");
				udh::createTaskTable("Productivity_companion.db");
				for (std::vector<udh::inputField>::iterator itr = textList.begin(); itr < textList.end(); itr++)
				{
					udh::insertTaskData("Productivity_companion.db", *itr);
				}
				window.close();
			}
			//checking if textarea is clicked
			if (textarea.isclicked(event, window))
			{
				if (!textarea.IsEditing())
				{
					udh::addTask(sampletext, a, event, textList, textarea);
				}
				else
				{
					udh::editTask(sampletext, a, event, editTaskItr, textarea);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				sampletext.setdata("");
				//checking if user marked any task complete
				//window.setView(TaskView);
				udh::checkAction(event, textList, &window, editTaskItr, sampletext, textarea);
				//window.setView(window.getDefaultView());
			}
		}

		//clearing window
		window.clear(sf::Color(200, 180, 200));
		//drawing textarea 
		//window.draw(rectangle2);
		window.draw(TodoImage);
		textarea.drawTo(window);
		window.draw(c1);
		window.draw(c2);
		sampletext.drawtext(&window);
		window.setView(TaskView);
		udh::drawlist(textList, &window);
		window.setView(window.getDefaultView());
		window.display();
	}
	for (std::vector<udh::inputField>::iterator itr = textList.begin(); itr < textList.end(); itr++)
	{
		std::cout << itr->getdata();
	}
}