//#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "inputField.h"
#include<iostream>
#include<vector>
#include "button.h"
int main()
{
	const char* dir = "C:\\Users\\dell\\source\\repos\\SFML-I\\SFML-I\\task.db";
	std::vector<udh::inputField>::iterator editTaskItr;
	udh::inputField sampletext;
	udh::inputField dummyTask;
	dummyTask.setdata("db testing success");
	sf::Font  fonts;
	fonts.loadFromFile("Fonts/ArialCE.ttf");
	udh::Button textarea("add task", { 700.f,25.f }, { 10.f,10.f }, fonts);
	std::string a;
	std::vector<udh::inputField> textList;
	sf::RenderWindow window(sf::VideoMode(740, 560), "Text Box");
	sf::Event event;
	sf::RectangleShape rectangle2(sf::Vector2f(730.f, 500.f));
	rectangle2.setPosition(sf::Vector2f(5.f, 45.f));
	rectangle2.setFillColor(sf::Color(10, 50, 20));
	rectangle2.setOutlineColor(sf::Color(0, 80, 0));
	rectangle2.setOutlineThickness(2.f);
	//adjusting position of input text wrt to input text area.
	sampletext.setposition(sf::Vector2f(textarea.getbounds().left + 20,
		(textarea.getbounds().top + (textarea.getbounds().height - sampletext.gettext().getCharacterSize()) / 2) / 2));
	//main loop or game loop
	while (window.isOpen())
	{
		//if window gets an event
		while (window.pollEvent(event))
		{
			//checking of close button is cliked
			if (event.type == sf::Event::Closed)
			{
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
				udh::checkAction(event, textList, &window, editTaskItr, sampletext, textarea);
			}
			else
				continue;

		}

		//clearing window
		window.clear(sf::Color(10, 50, 20));
		//drawing textarea 
		textarea.drawTo(window);
		window.draw(rectangle2);
		sampletext.drawtext(&window);
		udh::drawlist(textList, &window);
		window.display();
	}
	for (std::vector<udh::inputField>::iterator itr = textList.begin(); itr < textList.end(); itr++)
	{
		std::cout << itr->getdata();
	}
}