#include "SFML/Graphics.hpp"
#include <stdc++.h>
#include "Btn.h"
#include <Windows.h>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode video_mode;
	video_mode.width = 760;
	video_mode.height = 675;
	sf::RenderWindow window(video_mode, "STUDY PLAN APP", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::Event event;


	bool run_main_window = false;
	bool run_app = true;

	sf::Font roboto_font;
	roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf");
	Btn* btn1 = new Btn("Btn 1", { 200.f, 300.f }, 16, roboto_font);
	Btn* btn2 = new Btn("Btn 2", { 210.f, 280.f }, 16, roboto_font);

	bool btn1show = true;
	bool btn2show = false;
	auto btn1_func = [&]()
	{
		btn1show = false;
		btn2show = true;
		std::cout << "Button 1 pressed.\n";
		sf::sleep(sf::milliseconds(100));
	};

	auto btn2_func = [&]()
	{
		btn1show = true;
		btn2show = false;
		std::cout << "Button 2 pressed.\n";
	};

	btn1->SetFillColor(sf::Color::Black);
	btn2->SetFillColor(sf::Color::Black);
	btn1->text.setFillColor(sf::Color::White);
	btn2->text.setFillColor(sf::Color::White);



	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}
		if(btn1show)
			btn1->BtnEvents(window, event, btn1_func);
		
		if(btn2show)
			btn2->BtnEvents(window, event, btn2_func);

		window.clear(sf::Color::White);

		if(btn1show)
			btn1->DrawTo(window);
		if(btn2show)
			btn2->DrawTo(window);

		window.display();
	}
	//session_app.Update_DB_Data();
	return EXIT_SUCCESS;
}