#include "TodoList.h"


TodoList::TodoList() :c1(15.f), c2(15.f),
	textarea("Add Task", { 580.f,30.f }, { 90.f, TEXTAREA_HEIGHT }, fonts)
{
	//textarea.setbtntext("add task");
	//textarea.setBtnPosition({ 80.f, 180.f });
	//textarea.setbtnRect({ 80.f,180.f,580.f,30.f});
	//textarea.setTextPos();

	scrollBar.setFillColor(sf::Color(100, 100, 100));
	scrollBar.setPosition(741, 169);

	c1.setFillColor(sf::Color(235, 235, 235));
	c2.setFillColor(sf::Color(235, 235, 235));
	c1.setPosition(75.f, TEXTAREA_HEIGHT);
	c2.setPosition(655.f, TEXTAREA_HEIGHT);
	fonts.loadFromFile("Fonts\\KaushanScript-Regular.ttf");
	/////////////////////////////////////////////////////////
	// Backgound for Todo
	if (!cover.loadFromFile("./TextureImages/todo_list_back2.png"))
	{
		std::cerr << "error loading texture\n";
	}
	TodoImage.setTexture(cover);

	sampletext.setdata("");
	sampletext.setstatus(false);

	sampletext.setposition(sf::Vector2f(textarea.getbounds().left + 10,
		textarea.getPosition().y + 5.f));
}
void TodoList::LoadTodoList()
{
	//database creating and loading
	udh::createDB("Productivity_companion.db");
	udh::createTaskTable("Productivity_companion.db");
	udh::LoadTaskList("Productivity_companion.db");
	sampletext.setdata("");
	sampletext.setstatus(false);
}

void TodoList::RunTodo(sf::RenderWindow& window, sf::Event event, sf::View& TaskView)
{
	int size = textList.size() * 40;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		
		while (!event.KeyReleased)
		{
			continue;
		}
		if (viewPos < size - 455)
		{
			TaskView.move(0.f, 40.f);
			viewPos += 40;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		while (!event.KeyReleased)
		{
			continue;
		}
		if (viewPos != 0)
		{
			TaskView.move(0.f, -40.f);
			viewPos -= 40;
		}
	}
	else if (event.type == sf::Event::MouseWheelMoved)
	{
		if (event.mouseWheel.delta < 0)
		{
			if (viewPos < size - 455)
			{
				TaskView.move(0.f, 40.f);
				viewPos += 40;
			}
		}
		else if (event.mouseWheel.delta > 0)
		{
			if (viewPos != 0)
			{
				TaskView.move(0.f, -40.f);
				viewPos -= 40;
			}
		}
	}

	//checking of close button is cliked
	if (event.type == sf::Event::Closed)
	{
		udh::deleteData("Productivity_companion.db");
		udh::createTaskTable("Productivity_companion.db");
		std::string sql_data = "INSERT INTO TASKS (Task,Status,Day) VALUES";

		for (std::vector<udh::inputField>::iterator itr = textList.begin(); itr < textList.end(); itr++)
		{
			sql_data += "('" + itr->getdata() + "', '" +
			std::to_string(itr->getstatus()) +"','"+std::to_string(itr->getDay())+ "'),";
		}
		sql_data.pop_back();
		sql_data.push_back(';');

		udh::insertTaskDB("Productivity_companion.db", sql_data);
		window.close();
	}

	//checking if textarea is clicked
	if (textarea.isclicked(event, window))
	{
		if (!textarea.IsEditing())
		{
			udh::addTask(sampletext, a, event, textList, textarea);
		}
		else
		{
			udh::editTask(sampletext, a, event, editTaskItr, textarea);
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		sampletext.setdata("");
		//checking if user marked any task complete
		udh::checkAction(event, textList, &window, editTaskItr, sampletext, textarea);
	}
}

void TodoList::DrawTodoMainWindow(sf::RenderWindow& window)
{
	window.draw(TodoImage);
	textarea.drawTo(window);
	window.draw(c1);
	window.draw(c2);
	sampletext.drawtext(&window);
}

void TodoList::DrawTodoView(sf::RenderWindow& window)
{
	udh::drawlist(textList, &window);
	if (textList.size() > 11)
	{
		int size = textList.size() * 40;
		scrollBar.setSize(sf::Vector2f(18.f, 207025 / size));
		scrollBar.setPosition(sf::Vector2f(741.f, viewPos + viewPos * 455 / size));
		window.draw(scrollBar);
	}
}