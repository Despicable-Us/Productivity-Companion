#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "menu.h"

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(740, 560), "CHILL MUSIC!");
	sf::Event event;
	sf::Music music[3];

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				window.close();

			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

					
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Music 1 is playing." << std::endl;
						music[0].openFromFile("audio/Monoman (study, chill, relax)  peaceful relaxing music.ogg");
						music[0].setVolume(80);
						for (int i = 0; i < 3; i++)
						{
							music[i].stop();
						}
						music[0].play();
						break;

					case 1:
						std::cout << "Music 2 is playing." << std::endl;
						music[1].openFromFile("audio/Late Night Melancholy - (EA7) CHILL Lofi Piano BeatStudy Session(1 hour Loop).ogg");
						music[1].setVolume(80);
						for (int i = 0; i < 3; i++)
						{
							music[i].stop();
						}
						music[1].play();
						break;

					case 2:
						std::cout << "Music 3 is playing." << std::endl;
						music[2].openFromFile("audio/1 A.M Study Session- lofi hip hopchill beats.ogg");
						music[2].setVolume(80);
						for (int i = 0; i < 3; i++)
						{
							music[i].stop();
						}
						music[2].play();
						break;

					case 3:
						window.close();
						break;
					}
					break;
				}
				break;

			 case sf::Event::Closed:

				window.close();

				break;
			}

		}
		

	    
		window.clear();

		menu.draw(window);

		window.display();
	}
}