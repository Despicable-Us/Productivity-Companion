#include "SFML/Graphics.hpp"
#include <stdc++.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 546), "SFML WORKS");
	window.setFramerateLimit(60);

	sf::Image image;
	if (!image.loadFromFile("Images/background.jpg"))
		return EXIT_FAILURE;
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite background;
	background.setTexture(texture);
	background.setPosition({ 0.f, 0.f });

	srand(static_cast<unsigned>(time(NULL)));
	sf::RectangleShape filler;
	std::vector<sf::RectangleShape> fillers;
	filler.setPosition({ 0.f, 0.f });
	filler.setSize({ 800.f, 30.f });
	

	// understanding the view thingy
	sf::View view;
	view.reset(sf::FloatRect(0.f, 0.f, 800.f, 546.f));
	//view.setCenter({ 400.f, 273.f });
	//view.setSize({ 800.f, 546.f });
	view.setViewport(sf::FloatRect(0.f, 0.355f, 1.f, 1.f));
	
	
	bool spaceDown = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (fillers.size() > 11)
				{
					if (event.mouseWheel.delta <= -1)
					{
						std::cout << "Down detedted!" << std::endl;
						view.move(0.f, 32.f);
					}
					else if (event.mouseWheel.delta >= 1)
					{
						std::cout << "Up detedted!" << std::endl;
						view.move(0.f, -32.f);
					}
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!spaceDown)
			{
				if (fillers.empty())
				{
					filler.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
					fillers.push_back(sf::RectangleShape(filler));
				}
				else
				{
					sf::Vector2f lastFillerPos = fillers[fillers.size() - 1].getPosition();
					filler.setPosition({ 0.f, lastFillerPos.y + 32.f });
					filler.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
					fillers.push_back(sf::RectangleShape(filler));
				}
				spaceDown = true;
			}
		}
		else
		{
			spaceDown = false;
		}


		window.clear(sf::Color(13, 13, 39));
		window.setView(view);
		for (auto& filler : fillers)
		{
			window.draw(filler);
		}
		window.setView(window.getDefaultView());
		window.display();
	}
}