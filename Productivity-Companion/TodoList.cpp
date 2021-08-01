#include "TodoList.h"


	TodoList::TodoList() :c1(15.f), c2(15.f),
		textarea("add task", { 580.f,30.f }, { 80.f,180.f }, fonts),
		TaskView({ 0.f,0.f,760.f,675.f })
	{
		//textarea.setbtntext("add task");
		//textarea.setBtnPosition({ 80.f, 180.f });
		//textarea.setbtnRect({ 80.f,180.f,580.f,30.f});
		//textarea.setTextPos();
		scrollBar.setFillColor(sf::Color(100, 100, 100));
		scrollBar.setPosition(741, 169);
		c1.setFillColor(sf::Color(235, 235, 235));
		c2.setFillColor(sf::Color(235, 235, 235));
		c1.setPosition(65.f, 180.f);
		c2.setPosition(645.f, 180.f);
		fonts.loadFromFile("Fonts\\KaushanScript-Regular.ttf");
		/////////////////////////////////////////////////////////
		// Backgound for Todo
		if (!cover.loadFromFile("./TextureImages/TodoTexture1.jpg"))
		{
			std::cerr << "error loading texture\n";
		}
		TodoImage.setTexture(cover);
		int x, y;
		x = cover.getSize().x;
		y = cover.getSize().y;
		TodoImage.setTextureRect({ 0,0,x,y });
		TodoImage.setScale(0.75, 0.39);
		TaskView.setViewport({ 0.f,0.3259,1.f,1.f });
		sampletext.setdata("");
		sampletext.setstatus(false);
		/////////////////////////////////////////////////////////
		TaskView.setViewport({ 0.f,0.3259,1.f,1.f });
		//adjusting position of input text wrt to input text area.
		sampletext.setposition(sf::Vector2f(textarea.getbounds().left + 20,
			textarea.getPosition().y));
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
	void TodoList::RunTodo(sf::RenderWindow& window, sf::Event event)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			int size = textList.size() * 40;
			while (!event.KeyReleased)
			{
				continue;
			}
			if (viewPos < size - 455)
			{
				TaskView.move(0.f, 50.f);
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
				TaskView.move(0.f, -50.f);
				viewPos -= 40;
			}
		}
		//checking of close button is cliked
		if (event.type == sf::Event::Closed)
		{
			udh::deleteData("Productivity_companion.db");
			udh::createTaskTable("Productivity_companion.db");
			for (std::vector<udh::inputField>::iterator itr = textList.begin(); itr < textList.end(); itr++)
			{
				udh::insertTaskData("Productivity_companion.db", *itr);
			}
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
	void TodoList::DrawTodo(sf::RenderWindow& window)
	{
		window.clear(sf::Color(200, 180, 200));
		window.draw(TodoImage);
		textarea.drawTo(window);
		window.draw(c1);
		window.draw(c2);
		sampletext.drawtext(&window);
		window.setView(TaskView);
		udh::drawlist(textList, &window);
		if (textList.size() > 11)
		{
			int size = textList.size() * 40;
			scrollBar.setSize(sf::Vector2f(18.f, 207025 / size));
			scrollBar.setPosition(sf::Vector2f(741.f, viewPos + viewPos * 455 / size));
			window.draw(scrollBar);
		}
		window.setView(window.getDefaultView());
		window.display();
	}