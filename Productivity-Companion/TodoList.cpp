#include "TodoList.h"

TodoList::TodoList() :c1(15.f), c2(15.f),
	textarea("Add Task", { 580.f,30.f }, { 88.f, TEXTAREA_HEIGHT }, fonts)
{
	scrollBar.setFillColor(sf::Color(100, 100, 100));
	scrollBar.setPosition(741, 169);

	c1.setFillColor(sf::Color(235, 235, 235));
	c2.setFillColor(sf::Color(235, 235, 235));
	c1.setPosition(75.f, TEXTAREA_HEIGHT);
	c2.setPosition(655.f, TEXTAREA_HEIGHT);
	fonts.loadFromFile("Fonts/KaushanScript-Regular.ttf");
	
	if (!cover.loadFromFile("./Texture/todo_cover.png"))
	{
		std::cerr << "error loading texture\n";
	}
	TodoImage.setTexture(cover);

	sampletext.setdata("");
	sampletext.setstatus(false);
	sampletext.setposition(sf::Vector2f(textarea.getbounds().left + 10,textarea.getPosition().y + 5.f));

	if (!roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading the font 'Roboto-Medium.ttf'";

	home_back_btn = new Btn("Home", { 55.f, 30.f }, 14, this->roboto_font);
	this->home_back_btn_clicked = false;

	this->home_back_btn_func = [&]()
	{
		home_back_btn_clicked = true;
	};
	this->is_planner_sheet = false;
}


TodoList::TodoList(std::string plan_sheet_name) :c1(15.f), c2(15.f),
textarea("Add Task", { 580.f,30.f }, { 88.f, TEXTAREA_HEIGHT }, fonts)
{
	if(!fonts.loadFromFile("Fonts/KaushanScript-Regular.ttf"))
		throw "Error in loadin the font 'KaushanScript-Regular.ttf'";

	if (!cover.loadFromFile("./Texture/plan_sheet_background2.png"))
		throw "Error in loading the cover image";

	if (!roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading the font 'Roboto-Medium.ttf'";

	scrollBar.setFillColor(sf::Color(100, 100, 100));
	c1.setFillColor(sf::Color(235, 235, 235));
	c2.setFillColor(sf::Color(235, 235, 235));
	TodoImage.setTexture(cover);
	this->Reset_Functions(plan_sheet_name);
	this->is_planner_sheet = true;
}

void TodoList::Reset_Functions(std::string planner_name)
{
	this->plan_sheet_name = planner_name;
	textList.clear();
	scrollBar.setPosition(741, 169);
	c1.setPosition(75.f, TEXTAREA_HEIGHT);
	c2.setPosition(655.f, TEXTAREA_HEIGHT);

	sampletext.setdata("");
	sampletext.setstatus(false);
	sampletext.setposition(sf::Vector2f(textarea.getbounds().left + 10, textarea.getPosition().y + 5.f));
	home_back_btn = new Btn("Back", { 705.f, 30.f }, 14, this->roboto_font);
	this->home_back_btn_clicked = false;
	this->home_back_btn_func = [&]()
	{
		home_back_btn_clicked = true;
	};
	std::cout << plan_sheet_name << std::endl;
	background_text.setFont(fonts);
	background_text.setString(plan_sheet_name);
	background_text.setFillColor(sf::Color::White);
	background_text.setCharacterSize(36);
	background_text.setPosition({380.f - background_text.getGlobalBounds().width/2, 30.f});
	this->LoadDB();
}

void TodoList::LoadDB()
{
	udh::select_plan_sheet_data("Productivity_companion.db", plan_sheet_name);
	sampletext.setdata("");
	sampletext.setstatus(false);
}

void TodoList::LoadTodoList()
{
	textList.clear();
	udh::createDB("Productivity_companion.db");
	udh::createTaskTable("Productivity_companion.db");
	udh::LoadTaskList("Productivity_companion.db");
	sampletext.setdata("");
	sampletext.setstatus(false);
}

void TodoList::RunTodo(sf::RenderWindow& window, sf::Event event, sf::View& TaskView, bool& run_main_window, bool& run_app)
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

	//checking of close button if clicked
	if (event.type == sf::Event::Closed)
	{
		if (!textList.empty())
		{
			this->Update_DB();
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
		udh::checkAction(event, textList, &window, editTaskItr, sampletext, textarea);
	}
	home_back_btn->BtnEvents(window, event, this->home_back_btn_func);
	if (home_back_btn_clicked)
	{
		this->Update_DB();
		home_back_btn_clicked = false;
		run_main_window = true;
		run_app = false;
	}
}

void TodoList::DrawTodoMainWindow(sf::RenderWindow& window)
{
	window.draw(TodoImage);
	window.draw(background_text);
	textarea.drawTo(window);
	window.draw(c1);
	window.draw(c2);
	sampletext.drawtext(&window);
	home_back_btn->DrawTo(window);
	
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

void TodoList::Update_DB()
{
	std::string sql_data;
	if (is_planner_sheet)
	{
		udh::delete_plan_sheet_data("Productivity_companion.db", plan_sheet_name);
		sql_data = "INSERT INTO PLANNER_LIST (Task, Status, Day, plan_sheet_name) VALUES";
		for (std::vector<udh::inputField>::iterator itr = textList.begin(); itr < textList.end(); itr++)
		{
			sql_data += "('" + itr->getdata() + "', '" +
				std::to_string(itr->getstatus()) + "','" + std::to_string(itr->getDay()) + "','" + plan_sheet_name + "'),";
		}
		sql_data.pop_back();
		sql_data.push_back(';');
		if (sql_data.size() > 68)
		{
			udh::insertTaskDB("Productivity_companion.db", sql_data);
		}

	}
	else
	{
		udh::deleteData("Productivity_companion.db");
		udh::createTaskTable("Productivity_companion.db");
		sql_data = "INSERT INTO TASKS (Task,Status,Day) VALUES";

		for (std::vector<udh::inputField>::iterator itr = textList.begin(); itr < textList.end(); itr++)
		{
			sql_data += "('" + itr->getdata() + "', '" +
				std::to_string(itr->getstatus()) + "','" + std::to_string(itr->getDay()) + "'),";
		}
		sql_data.pop_back();
		sql_data.push_back(';');
		udh::insertTaskDB("Productivity_companion.db", sql_data);
	}
}
