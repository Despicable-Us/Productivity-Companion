#include "Points.h"


void Points::initiatePoints(sf::RenderWindow &window)
{
	//loading coin texture
	if (!this->coinTexture.loadFromFile("Texture/Coin1.png")) {
		std::cout << "Coin texture couldn't be added" << std::endl;
	}
	if (!coinFont.loadFromFile("Fonts/ArialCE.ttf")) {
		std::cout << "Coin font couldn't be loaded" << std::endl;
	}

	float length = 33.0f;
	float height = 33.0f;
	float posx = window.getSize().x - length;

	coinRect.setSize(sf::Vector2f(length, height));
	coinRect.setOrigin(sf::Vector2f(length / 2.0f, height / 2.f));
	coinRect.setTexture(&coinTexture);

	points.setFont(coinFont);
	points.setCharacterSize(int(length - 10.0f)); //arguement is unsigned int
	points.setStyle(sf::Text::Bold);
	points.setFillColor(sf::Color(sf::Color(POINT_TEXT_COLOR)));

	//getting points to display from input file
	int tempPoints;
	file.open("pomoPoints.txt", std::ios::in);
	if (!file.is_open()) {
		file.open("pomoPoints.txt", std::ios::out);
		file << 0;
	}
	file.close();
	file.open("pomoPoints.txt", std::ios::in);
	file >> tempPoints;
	file.close();

	points.setString(std::to_string(tempPoints));

	//to set length of the display box according to lenght of points
	double mult = 1.0 - (log10( points.getString().getSize()) / 10.0f) * 4;

	pointRect.setFillColor(sf::Color(POINT_RECT_COLOR));
	pointRect.setOrigin(0, height / 2);
	pointRect.setSize(sf::Vector2f(points.getCharacterSize() * ((points.getString().getSize()+0.5f) * float(mult)), height));

	pointCircle.setFillColor(sf::Color(POINT_RECT_COLOR));
	pointCircle.setRadius(length / 2.0f);
	pointCircle.setOrigin(pointCircle.getRadius(), pointCircle.getRadius());

	coinRect.setPosition(posx - pointRect.getSize().x , 30.0f);	//-------------------------------------------------> position
	points.setPosition(coinRect.getPosition().x + 20, coinRect.getPosition().y - 15);
	pointRect.setPosition(coinRect.getPosition().x, coinRect.getPosition().y);
	pointCircle.setPosition(pointRect.getPosition().x + pointRect.getSize().x, pointRect.getPosition().y);
  
}

void Points::updatePoints(float a)
{
	float temp = std::stof(std::string(points.getString())); // string to float
	float addedPoints = temp + a;
	//points don't go below zero
	if (addedPoints < 0) {
		addedPoints = 0;
	}
	file.open("pomoPoints.txt", std::ios::out);
	file << addedPoints;
	points.setString(std::to_string(int(addedPoints)));
	file.close();
}

void Points::displayPoints(sf::RenderWindow& window)
{
	window.draw(pointRect);
	window.draw(pointCircle);
	window.draw(coinRect);
	window.draw(points);
}
