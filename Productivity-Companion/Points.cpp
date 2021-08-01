#include "Points.h"


void Points::initiatePoints()
{
	//loading coin texture
	if (!this->coinTexture.loadFromFile("TextureImages/Coin1.png")) {
		std::cout << "Coin texture couldn't be added" << std::endl;
	}
	if (!coinFont.loadFromFile("Fonts/ArialCE.ttf")) {
		std::cout << "Coin font couldn't be loaded" << std::endl;
	}

	float length = 40.0f;
	float height = 40.0f;

	coinRect.setSize(sf::Vector2f(length, height));
	coinRect.setOrigin(sf::Vector2f(length / 2.0f, height / 2.f));
	coinRect.setPosition(35.0f, 90.0f);	//-------------------------------------------------> position
	coinRect.setTexture(&coinTexture);

	points.setFont(coinFont);
	points.setCharacterSize(int(length - 10.0f)); //arguement is unsigned int
	points.setStyle(sf::Text::Bold);
	points.setPosition(coinRect.getPosition().x + 25, coinRect.getPosition().y - 20);
	points.setFillColor(sf::Color(sf::Color(POINT_TEXT_COLOR)));

	//getting points to display from input file
	int tempPoints;
	file.open("pomoPoints.txt", std::ios::in);
	if (!file.is_open()) {
		std::cout << "this must run here" << std::endl;
		file.open("pomoPoints.txt", std::ios::out);
		file << 0;
	}
	file.close();
	file.open("pomoPoints.txt", std::ios::in);
	file >> tempPoints;
	file.close();

	points.setString(std::to_string(tempPoints));
  

	pointRect.setFillColor(sf::Color(POINT_RECT_COLOR));
	pointRect.setOrigin(0, height / 2);
	pointRect.setPosition(coinRect.getPosition().x, coinRect.getPosition().y);
	//to set length of the display box according to lenght of points
	double mult = 1.0 - (log10( points.getString().getSize()) / 10.0f) * 4;
	pointRect.setSize(sf::Vector2f(points.getCharacterSize() * (points.getString().getSize()) * float(mult), height));

	pointCircle.setFillColor(sf::Color(POINT_RECT_COLOR));
	pointCircle.setRadius(length / 2.0f);
	pointCircle.setOrigin(pointCircle.getRadius(), pointCircle.getRadius());
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
