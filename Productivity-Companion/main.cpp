#include "TodoList.h"
std::vector<udh::inputField> textList;
udh::inputField sampletext;
int viewPos;
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(760, 675), "My Todos", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::Event event;
	TodoList todolist;
	todolist.LoadTodoList();

	sf::View scroll_view;
	scroll_view.reset(sf::FloatRect(0.f, 0.f, 760.f, 675.f));
	scroll_view.setViewport({ 0.f, 0.3259, 1.f, 1.f });

	while (window.isOpen())
	{
		//if window gets an event
		while (window.pollEvent(event))
		{
			todolist.RunTodo(window, event, scroll_view);
		}


		window.clear(sf::Color::White);

		//VIEW SECTION
		window.setView(scroll_view);
		todolist.DrawTodoView(window);


		// WINDOW
		window.setView(window.getDefaultView());
		todolist.DrawTodoMainWindow(window);
		window.display();
	}
};