#include "SFML/Graphics.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(740, 560), "Button", sf::Style::Default, settings);


	sf::Vector2f winCenter;
	winCenter.x = window.getSize().x / 2.f;
	winCenter.y = window.getSize().y / 2.f;

	sf::Font font;
	if (!font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium' font";

	float circleRadius = 20.f;
	sf::Vector2f circleVec2f({ circleRadius, circleRadius });
	float rectW = 300.f, rectH = 180.f;
	sf::Color color(23, 137, 252);
	

	sf::RectangleShape mainRect({ rectW, rectH});
	sf::RectangleShape upRect({ rectW, circleRadius }), leftRect({ circleRadius, rectH }), rightRect({ circleRadius, rectH }), bottomRect({ rectW, circleRadius });
	mainRect.setOrigin({ mainRect.getSize().x / 2, mainRect.getSize().y / 2 });
	mainRect.setPosition(winCenter);

	sf::Vector2f mainRectPos = mainRect.getPosition();
	sf::Vector2f mainRectSize = mainRect.getSize();

	sf::CircleShape CTopLeft(circleRadius), CTopRight(circleRadius), CBottomLeft(circleRadius), CBottomRight(circleRadius);
	CTopLeft.setOrigin(circleVec2f);
	CTopRight.setOrigin(circleVec2f);
	CBottomLeft.setOrigin(circleVec2f);
	CBottomRight.setOrigin(circleVec2f);

	CTopLeft.setPosition({ mainRectPos.x - mainRectSize.x / 2, mainRectPos.y - mainRectSize.y / 2 });
	CTopRight.setPosition({ mainRectPos.x + mainRectSize.x / 2, mainRectPos.y - mainRectSize.y / 2 });
	CBottomLeft.setPosition({ mainRectPos.x - mainRectSize.x / 2, mainRectPos.y + mainRectSize.y / 2 });
	CBottomRight.setPosition({ mainRectPos.x + mainRectSize.x / 2, mainRectPos.y + mainRectSize.y / 2 });
	
	upRect.setOrigin({ upRect.getSize().x / 2, upRect.getSize().y / 2});
	leftRect.setOrigin({ leftRect.getSize().x / 2, leftRect.getSize().y / 2 });
	rightRect.setOrigin({ rightRect.getSize().x / 2, rightRect.getSize().y / 2 });
	bottomRect.setOrigin({ bottomRect.getSize().x / 2, bottomRect.getSize().y / 2 });

	upRect.setPosition({mainRectPos.x, mainRectPos.y - mainRectSize.y / 2 - upRect.getSize().y/2});
	bottomRect.setPosition({ mainRectPos.x, mainRectPos.y + mainRectSize.y / 2 + upRect.getSize().y / 2 });
	leftRect.setPosition({ mainRectPos.x - mainRectSize.x / 2 - leftRect.getSize().x / 2, mainRectPos.y });
	rightRect.setPosition({ mainRectPos.x + mainRectSize.x / 2 + leftRect.getSize().x / 2, mainRectPos.y });


	CTopLeft.setFillColor(color);
	CTopRight.setFillColor(color);
	CBottomLeft.setFillColor(color);
	CBottomRight.setFillColor(color);
	upRect.setFillColor(color);
	leftRect.setFillColor(color);
	rightRect.setFillColor(color);
	bottomRect.setFillColor(color);
	mainRect.setFillColor(color);




	srand(static_cast<unsigned>(time(NULL)));

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
			
		}


		window.clear(sf::Color::White);
		window.draw(mainRect);
		window.draw(CTopLeft);
		window.draw(CTopRight);
		window.draw(CBottomLeft);
		window.draw(CBottomRight);

		window.draw(upRect);
		window.draw(leftRect);
		window.draw(rightRect);
		window.draw(bottomRect);

		window.display();
	}
}