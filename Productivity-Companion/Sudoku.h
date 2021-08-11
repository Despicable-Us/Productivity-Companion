#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define B_WIDTH 64.f
#define B_HEIGHT 64.f

class Box
{
	public:
		sf::RectangleShape shape;
		sf::Font roboto_font;
		sf::Text text;
		bool fixed;
		bool wrong;

		Box();
		Box(float, float);

		void set_text_size(int);
		void load_font();
};

class Bar
{
	sf::RectangleShape line_shape;
	Bar(int, int, float, float);
};


class Sudoku
{
};

