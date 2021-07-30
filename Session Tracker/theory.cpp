#include "SFML/Graphics.hpp"
#include <iostream>
#include "Btn.h"
#include <stdc++.h>


int main()
{
	sf::RenderWindow window(sf::VideoMode(760, 675), "Something", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	sf::View view;
	view.reset(sf::FloatRect(0.f, 0.f, 760.f, 675.f));
	view.setViewport(sf::FloatRect(0.f, 0.25f, 1.f, 0.75f));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		window.clear(sf::Color(13, 13, 117));




		window.display();
	}
}