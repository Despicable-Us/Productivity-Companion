#include "SFML/Graphics.hpp"
#include <stdc++.h>
#include "Sudoku.h"


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode video_mode;
	video_mode.width = 760;
	video_mode.height = 675;
	sf::RenderWindow window(video_mode, "SUDOKU", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(90);
	sf::Event event;

	bool run_main_window = false;
	bool run_app = true;

	sf::Font roboto_font;
	roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf");

	srand(time(NULL));

	Sudoku sudoku;


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		sudoku.Run_Events(window, event);
		
			
		window.clear(sf::Color(220,220,220));

		sudoku.Render_To_Main_Window(window);

		window.display();
	}
	return EXIT_SUCCESS;
}