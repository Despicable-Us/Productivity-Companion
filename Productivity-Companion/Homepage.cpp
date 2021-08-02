#include "Session_Tracker.h"
#include "Icon.h"
#define WIN_WIDTH 760
#define WIN_HEIGHT 675
#define WIN_WIDTHF 760.f
#define WIN_HEIGHTF 675.f
#define VIEW_START 0.326f
#define ICON_HEIGHT 380.f

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
	

	// LOADING THE FONT
	sf::Font roboto_font;
	if (!roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading font 'Roboto-Medium.ttf;";


	// Texture loading for the apps
	sf::Texture pomo_timer_tex, session_tracker_tex, todo_list_tex, study_planner_tex;
	if (!pomo_timer_tex.loadFromFile("Images/PomoTimerIcon5.png"))
		throw "Error in loading the file";
	if(!session_tracker_tex.loadFromFile("Images/SessionTrackerIcon2.png"))
		throw("Error in loading the file");
	if (!todo_list_tex.loadFromFile("Images/TodoListIcon1.png"))
		throw("Error in loading the file");
	if (!study_planner_tex.loadFromFile("Images/StudyPlannerIcon1.png"))
		throw("Error in loading the file");

	Icon pomo_timer_icon(pomo_timer_tex, { 140.f, ICON_HEIGHT }), session_tracker_icon(session_tracker_tex, {300.f, ICON_HEIGHT}), 
		 todo_list_icon(todo_list_tex, { 460.f, ICON_HEIGHT }), study_planner_icon(study_planner_tex, {620.f, ICON_HEIGHT});

	sf::Texture sec_back;
	if (!sec_back.loadFromFile("Images/sec_back6.jpg"))
		throw "Lauda lai";
	
	sf::Sprite sec_back_sprite(sec_back);
	sec_back_sprite.setPosition({ 0.f,226.f });



	bool run_main_window = true;
	bool run_pomo_timer = false;
	bool run_session_tracker = false;
	bool run_todo_list = false;
	bool run_study_planner = false;

	auto pomo_timer_func = [&]()
	{
		std::cout << "Pomo Timer App Launch" << std::endl;
	};
	
	auto session_tracker_func = [&]()
	{
		run_main_window = false;
		run_session_tracker = true;
	};

	auto todo_list_func = [&]()
	{
		std::cout << "To-do List App Launch" << std::endl;
	};

	auto study_planner_func = [&]()
	{
		std::cout << "Study Planner App Launch" << std::endl;
	};



	// APP objects instanciation
	Session_Tracker session_app(window);


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (run_session_tracker)
			{
				session_app.Run_Inside_Event(window, event, scroll_view);
			}
		}
		if (run_main_window)
		{
			pomo_timer_icon.Run_Outside_Event(window, event, pomo_timer_func);
			session_tracker_icon.Run_Outside_Event(window, event, session_tracker_func);
			todo_list_icon.Run_Outside_Event(window, event, todo_list_func);
			study_planner_icon.Run_Outside_Event(window, event, study_planner_func);
		}
		if (run_session_tracker)
		{
			session_app.Run_Outside_Event(window, event, run_main_window, run_session_tracker);
		}

		window.clear(sf::Color::White);


		window.setView(scroll_view);
		if (run_session_tracker)
		{
			session_app.Render_In_View(window);
		}

		window.setView(window.getDefaultView());

		if (run_session_tracker)
		{
			session_app.Render_In_Main_Window(window);
		}
		if (run_main_window)
		{
			window.draw(sec_back_sprite);
			window.draw(home_bg);
			pomo_timer_icon.Draw_To(window);
			session_tracker_icon.Draw_To(window);
			todo_list_icon.Draw_To(window);
			study_planner_icon.Draw_To(window);
		}

		window.display();
	}
	session_app.Update_DB_Data();

	return EXIT_SUCCESS;
}