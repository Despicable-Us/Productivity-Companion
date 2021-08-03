#include "Session_Tracker.h"
#include "Icon.h"
#include "timeSetter.h"
#include "TodoList.h"

#define WIN_WIDTH 760
#define WIN_HEIGHT 675
#define WIN_WIDTHF 760.f
#define WIN_HEIGHTF 675.f
#define VIEW_START 0.326f
#define ICON_HEIGHT 380.f
#define APP_NAME_HEIGHT 448.f

std::vector<udh::inputField> textList;
udh::inputField sampletext;
int viewPos;

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode video_mode;
	video_mode.width = WIN_WIDTH;
	video_mode.height = WIN_HEIGHT;
	
	sf::RenderWindow window(video_mode, "Productivity Companion", sf::Style::Titlebar | sf::Style::Close,settings);
	window.setFramerateLimit(120);
	sf::Event event;
	sf::View scroll_view;
	sf::Image homepage_icon_image;
	sf::Texture home_bg_tex;

	// LOADING AND SETTING THE ICON
	if (!homepage_icon_image.loadFromFile("Images/icon2.png"))
		throw "Error in loading 'icon.png'";
	window.setIcon(homepage_icon_image.getSize().x, homepage_icon_image.getSize().y, homepage_icon_image.getPixelsPtr());

	// LOADING AND SETTING THE BACKGROUND IMAGE
	if (!home_bg_tex.loadFromFile("Images/test_background.PNG"))
		throw "Error in loading the 'test_background.PNG'";
	sf::Sprite home_bg(home_bg_tex);
	home_bg.setPosition({ 0.f, 0.f });
	scroll_view.reset(sf::FloatRect(0.f, 0.f, WIN_WIDTHF, WIN_HEIGHTF));
	scroll_view.setViewport(sf::FloatRect(0.f, VIEW_START, 1.f, 1.f));
	sf::Texture sec_back;
	if (!sec_back.loadFromFile("Images/sec_back6.jpg"))
		throw "Lauda lai";

	sf::Sprite sec_back_sprite(sec_back);
	sec_back_sprite.setPosition({ 0.f,226.f });

	
	// LOADING THE FONT
	sf::Font roboto_font;
	if (!roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading font 'Roboto-Medium.ttf;";

	// LOADING TEXTURES FOR THE APP ICONS
	sf::Texture pomo_timer_tex, session_tracker_tex, todo_list_tex, study_planner_tex;
	if (!pomo_timer_tex.loadFromFile("Images/PomoTimerIcon5.png"))
		throw "Error in loading the file";
	if(!session_tracker_tex.loadFromFile("Images/SessionTrackerIcon2.png"))
		throw("Error in loading the file");
	if (!todo_list_tex.loadFromFile("Images/TodoListIcon1.png"))
		throw("Error in loading the file");
	if (!study_planner_tex.loadFromFile("Images/StudyPlannerIcon1.png"))
		throw("Error in loading the file");

	// INSTANCIATING THE ICON FOR ALL APPS
	Icon pomo_timer_icon(pomo_timer_tex, { 140.f, ICON_HEIGHT }), session_tracker_icon(session_tracker_tex, {300.f, ICON_HEIGHT}), 
		 todo_list_icon(todo_list_tex, { 460.f, ICON_HEIGHT }), study_planner_icon(study_planner_tex, {620.f, ICON_HEIGHT});

	// BOOLEAN AND LAMBDA EXPRESSIONS
	bool run_main_window = true;
	bool run_pomo_timer = false;
	bool run_session_tracker = false;
	bool run_todo_list = false;
	bool run_study_planner = false;
	auto pomo_timer_func = [&]()
	{
		run_main_window = false;
		run_pomo_timer = true;
	};
	auto session_tracker_func = [&]()
	{
		run_main_window = false;
		run_session_tracker = true;
	};
	auto todo_list_func = [&]()
	{
		run_main_window = false;
		run_todo_list = true;
	};
	auto study_planner_func = [&]()
	{
		std::cout << "Study Planner App Launch" << std::endl;
	};

	// APP OBJECTS INSTANCIATIONS
	dial::timeSetter timeDial(window);   // POMO TIMER
	Session_Tracker session_app(window); // SESSION TRACKER
	TodoList todolist;
	todolist.LoadTodoList();

	// APP NAMES
	sf::Text pomo_timer_text("Pomo Timer", roboto_font, 14),
		     session_tracker_text("Session Tracker", roboto_font, 14),
		     todo_list_text("To-do List", roboto_font, 14),
		     study_planner_text("Study Planner", roboto_font, 14);

	pomo_timer_text.setOrigin({ pomo_timer_text.getGlobalBounds().width / 2.f, pomo_timer_text.getGlobalBounds().height / 2.f });
	session_tracker_text.setOrigin({ session_tracker_text.getGlobalBounds().width / 2.f, session_tracker_text.getGlobalBounds().height / 2.f });
	todo_list_text.setOrigin({ todo_list_text.getGlobalBounds().width / 2.f, todo_list_text.getGlobalBounds().height / 2.f });
	study_planner_text.setOrigin({ study_planner_text.getGlobalBounds().width / 2.f, study_planner_text.getGlobalBounds().height / 2.f });

	pomo_timer_text.setPosition({140.f, APP_NAME_HEIGHT});
	session_tracker_text.setPosition({ 300.f, APP_NAME_HEIGHT });
	todo_list_text.setPosition({ 460.f, APP_NAME_HEIGHT });
	study_planner_text.setPosition({ 620.f, APP_NAME_HEIGHT });

	pomo_timer_text.setFillColor(sf::Color::Black);
	session_tracker_text.setFillColor(sf::Color::Black);
	todo_list_text.setFillColor(sf::Color::Black);
	study_planner_text.setFillColor(sf::Color::Black);



	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (run_session_tracker)
			{
				session_app.Run_Inside_Event(window, event, scroll_view);
			}
			if (run_pomo_timer)
			{
				timeDial.dialPollEvents(window, event);
			}
			if (run_todo_list)
			{
				todolist.RunTodo(window, event, scroll_view);
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (run_main_window)
		{
			pomo_timer_icon.Run_Outside_Event(window, event, pomo_timer_func);
			session_tracker_icon.Run_Outside_Event(window, event, session_tracker_func);
			todo_list_icon.Run_Outside_Event(window, event, todo_list_func);
			study_planner_icon.Run_Outside_Event(window, event, study_planner_func);
			window.setTitle("Productivity Companion");
			window.clear(sf::Color::White);
		}
		if (run_session_tracker)
		{
			session_app.Run_Outside_Event(window, event, run_main_window, run_session_tracker);
			window.setTitle("Session Tracker");
			window.clear(sf::Color::White);
		}
		if (run_pomo_timer)
		{
			timeDial.dialUpdateFromEvents(window, event, run_main_window, run_pomo_timer);
			window.setTitle("Pomo Timer");
			window.clear(sf::Color(35, 40, 52));
		}
		


		// VIEW
		window.setView(scroll_view);
		if (run_session_tracker)
		{
			session_app.Render_In_View(window);
		}
		if (run_todo_list)
		{
			todolist.DrawTodoView(window);
		}

		// WINDOW
		window.setView(window.getDefaultView());

		if (run_session_tracker)
		{
			session_app.Render_In_Main_Window(window);
		}
		if (run_pomo_timer)
		{
			timeDial.dialDrawComponents(window);
		}

		if (run_todo_list)
		{
			todolist.DrawTodoMainWindow(window);
		}

		if (run_main_window)
		{
			window.draw(sec_back_sprite);
			window.draw(home_bg);
			pomo_timer_icon.Draw_To(window);
			session_tracker_icon.Draw_To(window);
			todo_list_icon.Draw_To(window);
			study_planner_icon.Draw_To(window);
			window.draw(pomo_timer_text);
			window.draw(session_tracker_text);
			window.draw(todo_list_text);
			window.draw(study_planner_text);
		}

		window.display();
	}
	session_app.Update_DB_Data();

	return EXIT_SUCCESS;
}