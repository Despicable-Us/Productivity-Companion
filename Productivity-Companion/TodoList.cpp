//#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "inputField.h"
#include<iostream>
#include<vector>
#include "button.h"


int main()
{

	std::vector<udh::inputField>::iterator editTaskItr;
	udh::inputField sampletext;
	udh::inputField dummyTask;
	sf::Font  fonts;
	fonts.loadFromFile("Fonts\\KaushanScript-Regular.ttf");
	/////////////////////////////////////////////////////////
	// Backgound for Todo
	sf::Texture cover;
	if (!cover.loadFromFile("./TextureImages/TodoTexture.jpg"))
	{
		std::cerr << "error loading texture\n";
	}
	sf::Sprite TodoImage;
	TodoImage.setTexture(cover);
	int x, y;
	x = cover.getSize().x;
	y = cover.getSize().y - 100;
	TodoImage.setTextureRect({0,0,x,y});
	TodoImage.setScale(0.75,0.3);
	////////////////////////////////////////////////////////

	float y1(0.3 * y+10);
	udh::Button textarea("add task", { 580.f,25.f }, { 80.f,y1 }, fonts);
	std::string a;
	std::vector<udh::inputField> textList;
	sf::RenderWindow window(sf::VideoMode(740, 560), "My Todos");
	sf::Event event;
	sf::RectangleShape rectangle2(sf::Vector2f(730.f, 560-(y1+39)));
	rectangle2.setPosition(sf::Vector2f(5.f, y1+35));
	rectangle2.setFillColor(sf::Color(200, 180, 200));
	rectangle2.setOutlineColor(sf::Color(80, 80, 80));
	rectangle2.setOutlineThickness(2.f);
	//adjusting position of input text wrt to input text area.
	sampletext.setposition(sf::Vector2f(textarea.getbounds().left + 20,
		textarea.getPosition().y));
	std::cout << textarea.getPosition().y;
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
		window.clear(sf::Color(200, 180, 200));
		//drawing textarea 
		window.draw(rectangle2);
		textarea.drawTo(window);
		window.draw(TodoImage);
		sampletext.drawtext(&window);
		udh::drawlist(textList, &window);
		window.display();
	}
	for (std::vector<udh::inputField>::iterator itr = textList.begin(); itr < textList.end(); itr++)
	{
		std::cout << itr->getdata();
	}
}