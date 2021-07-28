#include <stdc++.h>
#include "SFML/Graphics.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML ROCKS", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	sf::Vector2f winCenter(window.getSize().x / 2, window.getSize().y / 2);

	sf::CircleShape shape(100.f);
	shape.setPosition(sf::Vector2f(winCenter.x - shape.getRadius(), winCenter.y - shape.getRadius()));
	shape.setFillColor(sf::Color(203, 199, 108));

	sf::CircleShape overLay(90.f);
	overLay.setPosition(sf::Vector2f(winCenter.x - overLay.getRadius(), winCenter.y - overLay.getRadius()));
	overLay.setFillColor(sf::Color(228, 229, 163));

	sf::CircleShape dragger(15.f);
	dragger.setOrigin(sf::Vector2f(15.f, 15.f));
	dragger.setPosition(sf::Vector2f(winCenter.x, winCenter.y - 95.f));
	dragger.setFillColor(sf::Color(139, 194, 48));

	sf::CircleShape filler(6.f);
	filler.setOrigin(sf::Vector2f(6.f, 6.f));
	filler.setPosition(sf::Vector2f(winCenter.x, winCenter.y - 95.f));
	filler.setFillColor(sf::Color(139, 194, 48));

	std::vector<sf::Vector2f> fillersPos;
	sf::Vector2f filPos;

	sf::Vector2i currentMousePos;
	sf::Vector2f mousePosView;
	sf::Vector2f unitDir;
	float dirDistance;

	sf::FloatRect draggerRect;
	const sf::Vector2f draggerInitPos(dragger.getPosition());
	const sf::Vector2f draggerInitLowPos(sf::Vector2f(dragger.getPosition().x, dragger.getPosition().y + 190.f));
	sf::Vector2f draggerCurrPos;

	sf::Texture imageTex;
	if (!imageTex.loadFromFile("Texture/tree.png"))
		throw "Error in loading the file!!!";

	sf::Sprite tree;
	//imageTex.setSmooth(true);
	tree.setTexture(imageTex);
	tree.setOrigin({ tree.getGlobalBounds().width / 2, tree.getGlobalBounds().height / 2 });
	tree.setPosition({winCenter.x , winCenter.y + 13.f});

	bool mouseHeld = false;
	bool leftClickDown = false;

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
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						window.close();
					break;
			}
		}
		draggerRect = dragger.getGlobalBounds();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			currentMousePos = sf::Mouse::getPosition(window);
			mousePosView = static_cast<sf::Vector2f>(currentMousePos);

			if (!mouseHeld && draggerRect.contains(mousePosView))
			{
				mouseHeld = true;
				leftClickDown = true;
			}
			else if (leftClickDown) 
			{
				unitDir = mousePosView - winCenter;
				dirDistance = sqrt(pow(unitDir.x, 2) + pow(unitDir.y, 2));
				unitDir = { unitDir.x / dirDistance, unitDir.y / dirDistance };
				dragger.setPosition({ winCenter.x + unitDir.x * 95.f, winCenter.y + unitDir.y * 95.f });
				draggerCurrPos = dragger.getPosition();

				fillersPos.clear();

				if (mousePosView.x > winCenter.x)
				{

					for (float i = draggerInitPos.y; i < draggerCurrPos.y; i += 0.1f)
					{
						filPos = sf::Vector2f(winCenter.x + sqrt(pow(95.f, 2) - pow(i - winCenter.y, 2)), i);
						fillersPos.push_back(sf::Vector2f(filPos));
					}
				}
				else if (mousePosView.x <= winCenter.x)
				{
					for (float i = draggerInitPos.y; i < draggerInitLowPos.y; i += 0.1f)
					{
						filPos = sf::Vector2f(winCenter.x + sqrt(pow(95.f, 2) - pow(i - winCenter.y, 2)), i);
						fillersPos.push_back(sf::Vector2f(filPos));
					}

					for (float i = draggerInitLowPos.y; i >= draggerCurrPos.y; i -= 0.1f)
					{

						filPos = sf::Vector2f(winCenter.x - sqrt(pow(95.f, 2) - pow(i - winCenter.y, 2)), i);
						fillersPos.push_back(sf::Vector2f(filPos));
					}
				}
			}
			//else if (leftClickDown && draggerRect.contains(mousePosView)) //&& shapeRect.contains(mousePosView) 
			//{
			//	unitDir = mousePosView - winCenter;
			//	dirDistance = sqrt(pow(unitDir.x, 2) + pow(unitDir.y, 2));
			//	unitDir = { unitDir.x / dirDistance, unitDir.y / dirDistance };
			//	//std::cout << "DIRX: " << unitDir.x << "\nDIRY: " << unitDir.y << std::endl;
			//	dragger.setPosition({ winCenter.x + unitDir.x * 95.f, winCenter.y + unitDir.y * 95.f });
			//}
		}
		else
		{
			mouseHeld = false;
			leftClickDown = false;
		}
		

		window.clear(sf::Color(80, 163, 135));

		/*----------------------------------------DRAW AND RENDER-------------------------------------------*/
		window.draw(shape);
		window.draw(overLay);
		for (size_t i = 0; i < fillersPos.size(); i++)
		{
			filler.setPosition(fillersPos[i]);
			window.draw(filler);
		}
		window.draw(tree);
		window.draw(dragger);
		window.display();
	}

}