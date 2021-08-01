#include "Session_Tracker.h"
#define WIN_WIDTH 760
#define WIN_HEIGHT 675
#define WIN_WIDTHF 760.f
#define WIN_HEIGHTF 675.f
#define VIEW_START 0.326f

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode video_mode;
	video_mode.width = WIN_WIDTH;
	video_mode.height = WIN_HEIGHT;
	
	sf::RenderWindow window(video_mode, "Productivity Companion", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::Event event;
	sf::View scroll_view;
	sf::Image icon_image;
	sf::Texture home_bg_tex;

	if (!icon_image.loadFromFile("Images/icon2.png"))
		throw "Error in loading 'icon.png'";
	window.setIcon(icon_image.getSize().x, icon_image.getSize().y, icon_image.getPixelsPtr());

	if (!home_bg_tex.loadFromFile("Images/test_background.PNG"))
		throw "Error in loading the 'test_background.PNG'";

	sf::Sprite home_bg(home_bg_tex);
	home_bg.setPosition({ 0.f, 0.f });
	scroll_view.reset(sf::FloatRect(0.f, 0.f, WIN_WIDTHF, WIN_HEIGHTF));
	scroll_view.setViewport(sf::FloatRect(0.f, VIEW_START, 1.f, 1.f));
	
	// APP objects instanciation
	Session_Tracker session_app(window);

	// LOADING THE FONT
	sf::Font roboto_font;
	if (!roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading font 'Roboto-Medium.ttf;";

	//BTN and ALL THAT SHITS
	Btn* session_tracker_btn = new Btn("Session Tracker", { 200.f, 300.f }, 16, roboto_font);
	session_tracker_btn->SetFillColor(sf::Color::Black);
	session_tracker_btn->text.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);

		window.draw(home_bg);
		session_tracker_btn->DrawTo(window);

		window.display();
	}

	return EXIT_SUCCESS;
}