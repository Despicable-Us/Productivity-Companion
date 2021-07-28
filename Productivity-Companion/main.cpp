#include <iostream>
#include <SFML\graphics.hpp>
#include <math.h>

#include "timeSetter.h"
#include "toggleMusic.h"

#define LIGHT_GREEN 54,115,0

sf::Color lightGreen = sf::Color(LIGHT_GREEN);
sf::Color yellow = sf::Color(228, 228, 163);
sf::Color darkGreen = sf::Color(85, 152, 12);
sf::Color blue = sf::Color(81, 163, 135);


int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(760, 675), "Timer", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	dial::timeSetter timeDial(window);

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            timeDial.dialPollEvents(window, event);
        }
        timeDial.dialUpdateFromEvents(window);

        window.clear(sf::Color(BACKGROUND_COLOR));
        timeDial.dialDrawComponents(window);     
        window.display();
    }
	return 0;
}

