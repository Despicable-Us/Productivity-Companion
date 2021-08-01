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
	while (window.isOpen())
	{
		//if window gets an event
		while (window.pollEvent(event))
		{
			todolist.RunTodo(window, event);
		}

		todolist.DrawTodo(window);
	}
};