#include "Session_Tracker.h"
#include "Icon.h"
#include "timeSetter.h"
#include "TodoList.h"
#include "Study_Planner.h"
#include "Sudoku.h"

#define WIN_WIDTH 760
#define WIN_HEIGHT 675
#define WIN_WIDTHF 760.f
#define WIN_HEIGHTF 675.f
#define VIEW_START 0.326f
#define ICON_HEIGHT 370.f
#define APP_NAME_HEIGHT 438.f

std::vector<udh::inputField> textList;
std::vector<udh::inputField> completed;
std::vector<udh::inputField> studyTextList;
udh::inputField sampletext;
int viewPos;

sqlite3* DB;

// BOOLEAN 
bool run_main_window = true;
bool run_pomo_timer = false;
bool run_session_tracker = false;
bool run_todo_list = false;
bool run_study_planner = false;
bool run_sudoku = false;

std::vector<std::string> quote_vec =
{
	"Work hard in silence, let success make the noise.",
	"Experience is the name everyone gives to their mistakes.",
	"Good things take time and dedication.",
	"Dream big, work hard.",
	"Positive mindset enlightens dark paths.",
	"Do the best, be the best.",
	"Slow and steady wins the race.",
	"Belive in yourself and anything is possible.",
	"A year from now you may wish you started today.",
	"Be boundless, seek discomfort.",
	"Don't allow yourself to be ordinary.",
	"You can and you will !",
	"Stay positive and never give up.",
	"Every moment is a fresh beginning.",
	"Dream more often than you sleep."

};

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode video_mode;
	video_mode.width = WIN_WIDTH;
	video_mode.height = WIN_HEIGHT;
	sf::RenderWindow window(video_mode, "Productivity Companion", sf::Style::Titlebar | sf::Style::Close,settings);
	window.setFramerateLimit(60);

	srand(static_cast<unsigned>(time(NULL)));
	int exit = sqlite3_open("Productivity_companion.db", &DB);

	sf::Event event;
	sf::View scroll_view;
	sf::Image homepage_icon_image;
	sf::Texture home_bg_tex;

	// LOADING AND SETTING THE ICON
	if (!homepage_icon_image.loadFromFile("Texture/app_icon.png"))
		throw "Error in loading 'app_icon.png'";
	window.setIcon(homepage_icon_image.getSize().x, homepage_icon_image.getSize().y, homepage_icon_image.getPixelsPtr());

	// LOADING AND SETTING THE BACKGROUND IMAGE (PRIMARY AND SECONDARY)
	if (!home_bg_tex.loadFromFile("Texture/homepage.PNG"))
		throw "Error in loading the 'homepage.PNG'";

	sf::Sprite home_bg(home_bg_tex);
	home_bg.setPosition({ 0.f, 0.f });
	scroll_view.reset(sf::FloatRect(0.f, 0.f, WIN_WIDTHF, WIN_HEIGHTF));
	scroll_view.setViewport(sf::FloatRect(0.f, VIEW_START, 1.f, 1.f));
	sf::Texture sec_back;

	if (!sec_back.loadFromFile("Texture/low_background_cover.jpg"))
		throw "Error in loading 'low_background_cover.jpg'";

	sf::Sprite sec_back_sprite(sec_back);
	sec_back_sprite.setPosition({ 0.f, 226.f });
	
	// LOADING THE FONT
	sf::Font roboto_font;
	if (!roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading font 'Roboto-Medium.ttf;";

	// LOADING TEXTURES FOR THE APP ICONS
	sf::Texture pomo_timer_tex, session_tracker_tex, todo_list_tex, study_planner_tex, sudoku_tex;
	if (!pomo_timer_tex.loadFromFile("Texture/PomoTimerIcon.png"))
		throw "Error in loading the file";
	if(!session_tracker_tex.loadFromFile("Texture/SessionTrackerIcon.png"))
		throw("Error in loading the file");
	if (!todo_list_tex.loadFromFile("Texture/TodoListIcon.png"))
		throw("Error in loading the file");
	if (!study_planner_tex.loadFromFile("Texture/StudyPlannerIcon.png"))
		throw("Error in loading the file");
	if (!sudoku_tex.loadFromFile("Texture/sudoku_icon.png"))
		throw "Error in loading the file";

	// INSTANCIATING THE ICON FOR ALL APPS
	Icon pomo_timer_icon(pomo_timer_tex, { 140.f, ICON_HEIGHT }), session_tracker_icon(session_tracker_tex, {300.f, ICON_HEIGHT}), 
		 todo_list_icon(todo_list_tex, { 460.f, ICON_HEIGHT }), study_planner_icon(study_planner_tex, {620.f, ICON_HEIGHT}),
		 sudoku_icon(sudoku_tex, {140.f, 518.f});

	udh::open_db();

	// APP OBJECTS INSTANCIATIONS
	dial::timeSetter timeDial(window);   // POMO TIMER
	Session_Tracker session_app(window); // SESSION TRACKER
	TodoList todolist;					 // TO-DO LIST
	Study_Planner study_planner(window); // STUDY PLANNER
	Sudoku sudoku_app;					 //	SUDOKU

	//creating tables
	udh::createPlannerTable();
	udh::createPlannerListTable();
	udh::create_main_session_table();
	udh::create_session_list_table();

	// LAMBDA EXPRESSIONS AND FUNCTIONS
	auto pomo_timer_func = [&]()
	{
		run_main_window = false;
		run_pomo_timer = true;
	};
	auto session_tracker_func = [&]()
	{
		run_main_window = false;
		run_session_tracker = true;
		session_app.first_time = true;
	};
	auto todo_list_func = [&]()
	{
		run_main_window = false;
		todolist.LoadTodoList();
		run_todo_list = true;
	};
	auto study_planner_func = [&]()
	{
		run_main_window = false;
		run_study_planner = true;
		study_planner.first_time = true;
	};
	auto sudoku_func = [&]()
	{
		run_main_window = false;
		run_sudoku = true;
		sudoku_app.stop_watch.restart();
	};

	// APP NAMES
	sf::Text pomo_timer_text("Pomo Timer", roboto_font, 14),
		     session_tracker_text("Session Tracker", roboto_font, 14),
		     todo_list_text("To-do List", roboto_font, 14),
		     study_planner_text("Study Planner", roboto_font, 14),
			 sudoku_text("Sudoku", roboto_font, 14);

	pomo_timer_text.setOrigin({ pomo_timer_text.getGlobalBounds().width / 2.f, pomo_timer_text.getGlobalBounds().height / 2.f });
	session_tracker_text.setOrigin({ session_tracker_text.getGlobalBounds().width / 2.f, session_tracker_text.getGlobalBounds().height / 2.f });
	todo_list_text.setOrigin({ todo_list_text.getGlobalBounds().width / 2.f, todo_list_text.getGlobalBounds().height / 2.f });
	study_planner_text.setOrigin({ study_planner_text.getGlobalBounds().width / 2.f, study_planner_text.getGlobalBounds().height / 2.f });
	sudoku_text.setOrigin({ sudoku_text.getGlobalBounds().width / 2.f, sudoku_text.getGlobalBounds().height / 2.f });

	pomo_timer_text.setPosition({140.f, APP_NAME_HEIGHT});
	session_tracker_text.setPosition({ 300.f, APP_NAME_HEIGHT });
	todo_list_text.setPosition({ 460.f, APP_NAME_HEIGHT });
	study_planner_text.setPosition({ 620.f, APP_NAME_HEIGHT });
	sudoku_text.setPosition({ 140.f, 586.f });

	pomo_timer_text.setFillColor(sf::Color::Black);
	session_tracker_text.setFillColor(sf::Color::Black);
	todo_list_text.setFillColor(sf::Color::Black);
	study_planner_text.setFillColor(sf::Color::Black);
	sudoku_text.setFillColor(sf::Color::Black);

	sf::Font kaushan_font;
	if (!kaushan_font.loadFromFile("Fonts/KaushanScript-Regular.ttf"))
		throw "Error in loading the font 'KaushanScript-Regular.ttf";

	sf::Text quote("\"" + quote_vec[rand() % quote_vec.size()]  + "\"" , kaushan_font, 24);
	quote.setFillColor(sf::Color::Black);
	quote.setOrigin({ quote.getGlobalBounds().width / 2, quote.getGlobalBounds().height / 2 });
	quote.setPosition({ 380.f, 260.f });


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (window.hasFocus())
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
					todolist.RunTodo(window, event, scroll_view, run_main_window, run_todo_list);
				}

				if (run_study_planner)
				{
					study_planner.Run_Inside_Event(window, event, scroll_view);
				}

				if (event.type == sf::Event::Closed)
				{
					window.close();
					sqlite3_close(DB);
				}
			}
		}

		if (run_main_window&&window.hasFocus())
		{
			pomo_timer_icon.Run_Outside_Event(window, event, pomo_timer_func);
			session_tracker_icon.Run_Outside_Event(window, event, session_tracker_func);
			todo_list_icon.Run_Outside_Event(window, event, todo_list_func);
			study_planner_icon.Run_Outside_Event(window, event, study_planner_func);
			sudoku_icon.Run_Outside_Event(window, event, sudoku_func);
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
		
		if (run_todo_list)
		{
			window.setTitle("To-do List");
			window.clear(sf::Color::White);
		}

		if (run_study_planner)
		{
			window.setTitle("Study Planner");
			study_planner.Run_Outside_Event(window, event, run_main_window, run_study_planner);
			window.clear(sf::Color::White);
		}

		if (run_sudoku)
		{
			window.setTitle("Sudoku");
			sudoku_app.Run_Events(window, event, run_main_window, run_sudoku);
			window.clear(sf::Color::White);
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
		if (run_study_planner)
		{
			study_planner.Render_In_View(window);
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
		if (run_study_planner)
		{
			study_planner.Render_In_Main_Window(window);
		}
		if (run_sudoku)
		{
			sudoku_app.Render_To_Main_Window(window);
		}

		if (run_main_window)
		{
			window.draw(sec_back_sprite);
			window.draw(home_bg);
			pomo_timer_icon.Draw_To(window);
			session_tracker_icon.Draw_To(window);
			todo_list_icon.Draw_To(window);
			study_planner_icon.Draw_To(window);
			sudoku_icon.Draw_To(window);
			window.draw(pomo_timer_text);
			window.draw(session_tracker_text);
			window.draw(todo_list_text);
			window.draw(study_planner_text);
			window.draw(sudoku_text);
			window.draw(quote);
		}

		window.display();
	}
	return EXIT_SUCCESS;
}