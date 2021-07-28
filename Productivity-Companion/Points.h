#pragma once
#ifndef POINTS
#define POINTS
#include <SFML\graphics.hpp>
#include <math.h>
#include <iostream>
#include <fstream>

#define POINT_TEXT_COLOR 35,40,52
#define POINT_RECT_COLOR 251,208,60

class Points
{
protected:
	sf::Texture coinTexture;
	sf::RectangleShape coinRect;
	sf::Font coinFont;
	sf::Text points;
	sf::RectangleShape pointRect;
	sf::CircleShape pointCircle;

	std::fstream file;

public:
	//initiates points(sf::Text) and display components
	void initiatePoints();
	//updates points : after timer is stopped or it completes
	void updatePoints(float a);
	//displays all the components
	void displayPoints(sf::RenderWindow&);

};
#endif
