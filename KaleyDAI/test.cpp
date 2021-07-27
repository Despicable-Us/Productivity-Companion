
#include "Session.h"
#include <stdc++.h>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode video_mode;
	video_mode.width = 760;
	video_mode.height = 675;
	sf::RenderWindow window(video_mode, "SESSION", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::Event event;

	sf::Font font;
	if (!font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";

	sf::View scroll_view;
	scroll_view.reset(sf::FloatRect(0.f, 0.f, 760.f, 675.f));
	scroll_view.setViewport(sf::FloatRect(0.f, 0.326f, 1.f, 1.f));
	std::string name = "Prajesh";

	Session session(window, "Test");
	bool show_session = false;
	bool show_button = true;

	Btn* newBtn = new Btn("Click Me", { 380.f, 337.5 }, 18, font);
	newBtn->SetFillColor(sf::Color::Black);
	newBtn->text.setFillColor(sf::Color::White);

	std::function<void()> btn_click_event = [&]()
	{
		show_button = false;
		show_session = true;
	};
	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (show_session)
			{
				session.View_Scroll_Event(event, scroll_view);
			}
		}
		newBtn->BtnEvents(window, event, btn_click_event);
		if (show_session)
		{
			session.Run_Events(window, event, show_session, show_button);
		}

		window.clear(sf::Color::White);

		if (show_session)
		{
			window.setView(scroll_view);
			session.Draw_To_View(window);
		}


		window.setView(window.getDefaultView());
		if (show_button)
		{
			newBtn->DrawTo(window);
		}


		if (show_session)
		{
			session.Draw_To_Main_Window(window);
		}

		window.display();
	}
	session.Update_DB_Data();

	return EXIT_SUCCESS;
}
