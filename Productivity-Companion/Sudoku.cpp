#include "Sudoku.h"

Box::Box()
{
}

Box::Box(float width, float height)
{
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(sf::Color(250, 250, 250));
	this->text.setCharacterSize(38);
	this->text.setFillColor(sf::Color(52, 72, 97));
}

void Box::set_text_size(int size)
{
	this->text.setCharacterSize(size);
}

void Box::load_font()
{
	if (!roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading the font 'Roboto-Medium.ttf'";
	text.setFont(roboto_font);
}

Bar::Bar(int x_pos, int y_pos, float w, float h)
{
	this->line_shape.setSize(sf::Vector2f(w, h));
	this->line_shape.setPosition(sf::Vector2f(100.f + x_pos * 66.f, 150.f + y_pos * 66.f));
	this->line_shape.setFillColor(sf::Color(52, 72, 97));
}
