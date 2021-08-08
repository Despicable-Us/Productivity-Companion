#include "SFML/Graphics.hpp"
#include <stdc++.h>
#include "FlowTime.h"

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
	sf::View scroll_view;
	scroll_view.reset({ 0.f, 0.f, 760.f, 675.f });
	scroll_view.setViewport({ 0.f, 0.3259, 1.f, 1.f });

	FlowTime flow_time(window);




	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			flow_time.Run_Inside_Event(window, event, scroll_view);
		}

		flow_time.Run_Outside_Event(window, event, run_main_window, run_app);
			
		window.clear(sf::Color::White);

		flow_time.Render_In_Main_Window(window);

		window.display();
	}
	//session_app.Update_DB_Data();
	return EXIT_SUCCESS;
}