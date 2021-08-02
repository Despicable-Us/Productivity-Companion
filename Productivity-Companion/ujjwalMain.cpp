#include <iostream>
#include <SFML\graphics.hpp>
#include <math.h>

#include "timeSetter.h"
#include "toggleMusic.h"
#include "Btn.h"

int main() {
    sf::Font font;
    if (!font.loadFromFile("Fonts/Roboto-Medium.ttf")) {
        throw "Font in musicOptions is not loading";
    }
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

