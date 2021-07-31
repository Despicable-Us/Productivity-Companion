#include "menu.h"
#include "SFML/Audio.hpp"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("ArialCE.ttf"))
	{
		EXIT_FAILURE;
	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(20);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Monoman (study, chill, relax)  peaceful relaxing music");
	menu[0].setPosition(sf::Vector2f(0, 0));

	menu[1].setFont(font);
	menu[1].setCharacterSize(20);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Late Night Melancholy - (EA7) CHILL Lofi Piano BeatStudy Session(1 hour Loop)");
	menu[1].setPosition(sf::Vector2f(0, 30));

	menu[2].setFont(font);
	menu[2].setCharacterSize(20);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("1 A.M Study Session- lofi hip hopchill beats");
	menu[2].setPosition(sf::Vector2f(0, 60));

	menu[3].setFont(font);
	menu[3].setCharacterSize(20);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Return to Main Menu");
	menu[3].setPosition(sf::Vector2f(0, 100));

	selectedItemIndex = 0;
}

Menu::~Menu()
{
}


void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
