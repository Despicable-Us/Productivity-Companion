#include "Session_Tracker.h"
#include "Study_Planner.h"
#include "InputTodo.h"

std::vector<udh::inputField> textList;
udh::inputField sampletext;
int viewPos;



int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode video_mode;
	video_mode.width = 760;
	video_mode.height = 675;
	sf::RenderWindow window(video_mode, "STUDY PLAN APP", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::Event event;

	sf::View session_list_view;
	session_list_view.reset(sf::FloatRect(0.f, 0.f, 760.f, 675.f));
	session_list_view.setViewport(sf::FloatRect(0.f, 0.326f, 1.f, 1.f));

	Session_Tracker session_app(window);
	Study_Planner study_planner(window);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//session_app.Run_Inside_Event(window, event, session_list_view);
			study_planner.Run_Inside_Event(window, event, session_list_view);
		}
		//session_app.Run_Outside_Event(window, event);
		study_planner.Run_Outside_Event(window, event);

		window.clear(sf::Color::White);
		window.setView(session_list_view);
		//session_app.Render_In_View(window);
		study_planner.Render_In_View(window);

		window.setView(window.getDefaultView());
		//session_app.Render_In_Main_Window(window);
		study_planner.Render_In_Main_Window(window);
		window.display();
	}
	//session_app.Update_DB_Data();
	return EXIT_SUCCESS;
}