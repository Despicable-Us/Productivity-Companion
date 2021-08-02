#include "Icon.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(760, 675), "Productivity Companion", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::Event event;

	sf::Texture btn_tex;
	if (!btn_tex.loadFromFile("Images/SessionTrackerIcon2.png"))
		throw "Error in loading the image";


	Icon icon(btn_tex, { 380.f, 300.f });

	auto icon_pressed = [&]()
	{
		std::cout << "Icon pressed" << std::endl;
	};

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		icon.Run_Outside_Event(window, event, icon_pressed);
		window.clear(sf::Color::White);

		icon.Draw_To(window);
		window.display();
	}
}